---
title: MVCC机制实现原理
date: 2020-06-28 18:57:21
categories: mysql
tags:mysql
---

# MVCC

多版本控制：指一种提高并发的技术。<br />最早的数据库系统，只有读读之间可以并发。读写，写读，写写都要阻塞。<br />
<br />引入多版本后，只有写写之间相互阻塞，其他三种操作都可以并行。这样大幅度提升了 InnoDB 的并发度。<br />
<br />在内部实现中，InnoDB 通过 undo log 保存每条数据的多个版本，并且能够找回数据历史提供给用户读。(回滚日志)，**每个事务读到的数据版本可能是不一样的**。在同一个事务中，用户只能看到该事物创建快照之前已经提交的修改和该事务本身做的修改。<br />
<br />MVCC 只在 **读提交和可重复读** 两个隔离级别下工作。其他两个隔离级别和 MVCC 不兼容。<br />读未提交 总是读取最新的记录行，不需要 MVCC 的支持； 串行 则会对所有读取的记录行都加锁，单靠 MVCC 无法完成。<br />
<br />MySQL 的 InnoDB 存储引擎默认事务隔离级别是 RR（可重复读），是通过 “行级别锁+MVCC” 一起实现的，正常读的时候不加锁，写的时候加锁。而 **MVCC 的实现依赖：隐藏字段、Read View、Undo log**
<a name="tLfS8"></a>

## 简述 MySQL 的 MVCC 多版本并发控制

![隔离级别.PNG](/images/隔离级别.png)

 MVCC 是对于事物隔离级别的读已提交RC和可重复读RR，基于乐观锁的实现。在 LBCC（基于锁的并发控制）RC、RR、和串行化分别是通过加行锁，间隙锁和表锁来基于悲观锁的实现。 

而乐观锁的原理就是在特定的时间点（RC是每次读时，RR是事物开始时）生成一个当前快照，读数据读取快照，只在提交时判断是否有冲突，类似于 git 的 branch 和 commit。

MVCC会在新开启一个事物时，给事物包含的每行记录添加一个当前事物的ID 和 回滚指针。并包含一个 Read View，Read View 里保存了当前活跃的事物列表，小于这些列表的最近的事物ID 才是可见的。这样保证了读到的都是已提交的事物。

## 1.1、隐藏字段

InnoDB 存储引擎在每行数据的后面加了三个隐藏字段：

1. DB_TRX_ID(6字节)：表示最近一次对本记录行作修改（INSERT | UPDATE）（至于 delete，InnoDB 认为是一个 update 操作，不过会更新另外的删除位）
2. DB_ROW_PTR(7字节)：回滚指针，指向当前记录行的 undo log
3. DB_ROW_ID(6字节)：随着新行插入而单调递增
   1. 理解：当表没有主键或唯一非空索引时，InnoDB 就会使用这个行ID自动产生聚簇索引。如果表有主键或唯一非空索引，聚簇索引就不会包含这个行 ID 了。这个 DB_ROW_ID 和 MVCC 关系不大。



<a name="SxmK9"></a>

## 1.2、Read View 结构（快照）

Read View 主要是用来做可见性判断的，里面保存了”对事物不可见的其他活跃事物“。<br />![readview.png](/images/快照结构.png)<br />low_limit_id：目前出现过的最大的事物 ID+1，即下一个将被分配的事物 ID<br />up_limit_id：活跃事物表 trx_ids 中最小的事物 ID，如果 trx_ids 为空，则 up_limit_id 为 low_limit_id<br />trx_ids：Read View 创建时其他未提交的活跃事物的 ID 列表（不包括当前事物和已提交的事物）<br />creator_trx_id：当前创建事物的 ID，是一个递增的编号
<a name="jJfND"></a>

## 1.3、undo log

Undo log中存储的是老版本数据，当一个事务需要读取记录行时，如果当前记录行不可见，可以顺着 undo log 链找到满足其可见性条件的记录行版本<br /> 大多数对数据的变更操作包括 insert/update/delete，在InnoDB里，undo log分为如下两类：<br />       ①insert undo log : 事务对insert新记录时产生的undo log, 只在事务回滚时需要, 并且在事务提交后就可以立即丢弃。<br />       ②update undo log : 事务对记录进行delete和update操作时产生的undo log，不仅在事务回滚时需要，快照读也需要，只有当数据库所使用的快照中不涉及该日志记录，对应的回滚日志才会被purge线程删除。
<a name="hmN9v"></a>

## 2、记录行修改的具体流程

假设有一条记录行如下，字段有Name和Honor，值分别为"Curry"和"MVP"，行ID是1，最新修改这条记录的事务ID为1。<br />![image.png](/images/mvcc1.png)<br />（1）现在事物A（事物ID为2）对该记录做出了修改，将Honor改为”FMVP“：

1. 事物A先对该行加排它锁
2. 然后把该行数据拷贝到 undo log 中，作为旧版本
3. 拷贝完毕后，修改该行的 Honor 为 "FMVP"，并且修改 DB_TRX_ID 为 2，回滚指针指向拷贝到 undo log 的旧版本（然后还会将修改后的最新数据写入 redo log）
4. 事务提交，释放排它锁

![mvcc.png](/images/mvcc2.png)（2）接着事物B（事物ID为3）修改同一个记录行，将 Name 修改为 ”Iguodala“：

1. 事物B先对该行加排它锁
2. 然后把该行数据拷贝到 undo log，作为旧版本
3. 拷贝完毕后，修改该行 Name 为 ”Iguodala“，并且修改 DB_TRX_ID 为 3（事物B的ID），回滚指针指向拷贝到 undo log 的新版本
4. 事务提交，释放排它锁

![mvcc.png](/images/mvcc3.png)<br />由此可以看出，不同事物或者相同事物对同一记录行的修改，会使该行的 undo log 成为一条链表，undo log 的链首就是最新的旧记录，链尾就是最早的旧记录。
<a name="Q7p6T"></a>

## 3、可见性比较算法

在 InnoDB 中，创建一个新事物后，**执行第一个 select 语句会创建一个快照（read view）**，快照中会保存系统当前不应该被本事物看到的其他活跃事物 id 列表（即 trx_ids）。<br />
<br />假设当前事务要读取某一个记录行，该记录行的DB_TRX_ID（即最新修改该行的事务ID）为trx_id，Read View的活跃事务列表trx_ids中最早的事务ID为up_limit_id，将在生成这个Read Vew时系统出现过的最大的事务ID+1记为low_limit_id（即还未分配的事务ID）。<br />
<br />具体的比较算法如下（可以照着后面的 例子 ，看这段）:<br />
<br />1. 如果 trx_id < up_limit_id, 那么表明“最新修改该行的事务”在“当前事务”创建快照之前就提交了，所以该记录行的值对当前事务是可见的。跳到步骤5。<br />
<br />2. 如果 trx_id >= low_limit_id, 那么表明“最新修改该行的事务”在“当前事务”创建快照之后才修改该行，所以该记录行的值对当前事务不可见。跳到步骤4。<br />
<br />3. 如果 up_limit_id <= trx_id < low_limit_id, 表明“最新修改该行的事务”在“当前事务”创建快照的时候可能处于“活动状态”或者“已提交状态”；所以就要对活跃事务列表trx_ids进行查找（源码中是用的二分查找，因为是有序的）：<br />
<br />(1) 如果在活跃事务列表trx_ids中能找到 id 为 trx_id 的事务，表明在“当前事务”创建快照前，“该记录行的值”被“id为trx_id的事务”修改了，但没有提交；或者在“当前事务”创建快照后，“该记录行的值”被“id为trx_id的事务”修改了（不管有无提交）；这些情况下，这个记录行的值对当前事务都是不可见的，跳到步骤4；<br />
<br />(2)在活跃事务列表中找不到，则表明“id为trx_id的事务”在修改“该记录行的值”后，在“当前事务”创建快照前就已经提交了，所以记录行对当前事务可见，跳到步骤5。<br />
<br />4. 在该记录行的 DB_ROLL_PTR 指针所指向的undo log回滚段中，取出最新的的旧事务号DB_TRX_ID, 将它赋给trx_id，然后跳到步骤1重新开始判断。<br />![image.png](/images/mvcc例子.png)
<a name="4q6Rp"></a>

## 当前读和快照度

快照读：普通的 select 语句（不包括 select ... lock in share mode, select ... for update）<br />当前读：insert，update，select ... lock in share mode, select ... for update 等等需要获取数据库最新信息<br />只靠 MVCC 实现 RR 隔离级别，保证可重复读，还能防止部分幻读，但并不能完全防止<br />如果 事物A 是**快照读**，即 **普通select语句** 创建了快照；之后 事物B 执行 insert 语句；然后 事物A 再执行普通 select 语句，得到的还是之前 B 没有 insert 过的数据，这样就**防止了部分幻读**。<br />但是如果 事物A 执行的不是普通 select 语句，而是 select ... for updated 等语句，这时候，事物A 是**当前读**，每次语句执行时获取都是最新的数据。这样会产生幻读。

因此，InnoDB在实现RR隔离级别时，不仅使用了MVCC，还会对“当前读语句”读取的记录行加记录锁（record lock）和间隙锁（gap lock），禁止其他事务在间隙间插入记录行，来防止幻读。也就是前文说的"行级锁+MVCC"。 这个另开一篇博客分析。
<a name="h5C6f"></a>

## 参考

深度参考：[https://blog.csdn.net/Waves___/article/details/105295060](https://blog.csdn.net/Waves___/article/details/105295060)<br />

