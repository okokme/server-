#pragma once
#include <vector>
const int MAXSIZE = 10; //最小不可分割分区大小

typedef struct { //内存存储结构体
    int start; //开始地址
    int size; //大小
    bool state; //分区状态 true:空闲 false：占用
}block;

typedef struct { //工作分区结构体
    int start; //分配的分区首址
    int size; //大小
    int BlockSize; //分配空闲分区的大小 （可能大于作业大小）
}job;

//初始化空闲分区与作业
void init(std::vector<block> &BlockList, std::vector<job> &JobList);
//显示结果
void show(std::vector<block> &BlockList, std::vector<job> &JobList);
//回收分区
void recycle(std::vector<block> &BlockList, std::vector<job> &JobList);

