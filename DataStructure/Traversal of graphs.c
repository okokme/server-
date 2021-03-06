/*题目描述
从键盘接收有向图的顶点集，弧集，创建有向图，并完成下列任务：

（1）计算结点的出度、入度以及度;

  (2) 从第一个顶点出发，求一个深度优先遍历序列;

  (3) 从第一个顶点顶点出发，求一个广度优先遍历序列。

 注意：以用户输入各个顶点的顺序为顶点的序号。

          在深度和广度优先遍历中，优先选择序号小的顶点。

输入
第一行输入两个整数，以空格隔开，分别代表图的顶点数n和弧数e。(顶点个数<=20)
第二行依次输入顶点值，类型为字符，中间不用间隔符。
接下去有e行，每行为两个字符 uv（中间没有间隔符），表示一条弧<u,v>。

输出
连续输出n行，依次为各个结点的出度和入度，格式为【顶点w 出度值 入度值 度值】，四者间用空格隔开。
接下去的一行，输出深度优先遍历顶点序列（顶点间无间隔符）。

最后一行，输出广度优先遍历顶点序列（顶点间无间隔符）。


样例输入
5 7
ABCDE
AB
AE
BC
CD
DA
DB
EC
样例输出
A 2 1 3
B 1 2 3
C 1 2 3
D 2 1 3
E 1 1 2
ABCDE
ABECD

*/