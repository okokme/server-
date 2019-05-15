#include "BlockJob.h"

//FF算法  
void FF(std::vector<block> &BlockList, std::vector<job> &JobList);

int main(int argc, char const *argv[])
{
    std::vector<block> BlockList;
    std::vector<job> JobList;
    //初始化空闲分区与作业
    init(BlockList, JobList);
    //FF算法
    FF(BlockList, JobList);
    //显示结果
    show(BlockList, JobList);
    //回收分区
    recycle(BlockList, JobList);
    //显示结果
    show(BlockList, JobList);
    init(BlockList, JobList);
    return 0;
}

void FF(std::vector<block> &BlockList, std::vector<job> &JobList)
{
    for (std::vector<job>::iterator ItJob = JobList.begin(); ItJob != JobList.end(); ++ItJob)
	{
		for (std::vector<block>::iterator ItBlock = BlockList.begin(); ItBlock != BlockList.end(); ++ItBlock)
		{
			//分区未被使用且能够装下作业
            if((*ItBlock).state && (*ItBlock).size >= (*ItJob).size)
            {
                if((*ItBlock).size - (*ItJob).size > MAXSIZE) //剩余空间还可以继续分配
                {
                    (*ItBlock).state = false;

                    //修改作业信息，分配空间
                    (*ItJob).start = (*ItBlock).start;
                    (*ItJob).BlockSize = (*ItJob).size;

                    //添加新表项
                    block NewBlock;
                    NewBlock.start = (*ItBlock).start + (*ItBlock).size;
                    NewBlock.size = (*ItBlock).size - (*ItJob).size;
                    NewBlock.state = true;
                    (*ItBlock).size = (*ItJob).size;
                    BlockList.insert(ItBlock + 1, NewBlock);
                }
                else
                {  //剩余空间不可分配 全部分配给作业
                    (*ItBlock).state = false;
                    (*ItJob).start = (*ItBlock).start;
                    (*ItJob).BlockSize = (*ItBlock).size;
                }
                break;
            }
        }
    }
}
