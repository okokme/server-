/*问题 A: DS_7.1 有向图的创建、求度、遍历(by Yan)
时间限制: 10 Sec  内存限制: 256 MB
提交: 1419  解决: 429
[提交][状态][讨论版]
题目描述
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
提示
*/


#include<cstdio.h>  
#include<iotreeam>
#include<queue>
using namespace std;
#define MAXVEX 100 //最大顶点数
#define INFINITX 65535 //无穷大
typedef struct 
{
    char vexs[MAXVEX]; //顶点表
    int arc[MAXVEX][MAXVEX]; //邻接矩阵，可看做边表
    int numVertexes,numEdges; //图中当前的顶点数和边数
}MGrap;
int visited[MAXVEX];

int LocateVex(MGrap *G, char v)
{
    for(int i=1; i<= G->numVertexes; i++)
        if(G->vexs[i] == v)
            return i;
    return 1;
}
void CreateMGraph(MGrap *G)
{
    int i,j,k,weight;
    char vex1, vex2;
    printf("输入顶点和边数：");
    scanf("%d %d",&G->numVertexes, &G->numEdges);
    getchar();

    for(i=1; i<=G->numVertexes; i++)//依次输入顶点进顶点表?
        scanf("%c",&G->vexs[i]);
    
    for(i=1; i<=G->numVertexes; i++) //先初始化将邻接矩阵全部先初始化为无穷
        for(j=1; j<=G->numVertexes; j++)
            G->arc[i][j] = 0;

    for(k=1; k<=G->numEdges; k++)
    {
        getchar(); //注意加getchar()过滤回车 底下scanf有%c！！
        scanf("%c%c",&vex1, &vex2); //输入边vex1到vex2，及他们的权值
        i = LocateVex(G,vex1); //找到vex1，vex2对应在顶点表的下标
        j = LocateVex(G,vex2);
     //   printf("i=%d,j=%d\n",i,j);
        G->arc[i][j] = 1; //有这条边，标记为1
    }

  /*   for(i=1; i<=G->numVertexes; i++) 
        
        {for(j=1; j<=G->numVertexes; j++)
            printf("%d ",G->arc[i][j]);
            printf("\n");
            }
*/

}
void dushu(MGrap G)
{
    int dushu[G.numVertexes][4]; //in[20], out[20], all[20];
    int i,j;
    for( i=1; i<=G.numVertexes; i++)
    {
        dushu[i][1] = 0;
        for( j=1; j<=G.numVertexes; j++)
        {
            dushu[i][1] += G.arc[i][j];
        }
    }
    //printf("%d\n\n",G.numVertexes);
  
    for(i=1; i<=G.numVertexes; i++)
    {
        dushu[i][2] = 0;
        for(j=1; j<=G.numVertexes; j++)
        {
            dushu[i][2] += G.arc[j][i];
            dushu[i][3] = dushu[i][1] + dushu[i][2];
        }
    }
        
    for( i=1; i<=G.numVertexes; i++)
    {   
        printf("%c ",64+i);
        for(j = 1; j<=3; j++)
            printf("%d ",dushu[i][j]);
        printf("\n");

    }
  
}
//图创建成功以后
//深度优先遍历
int FirstAdjVex(MGrap G, int v)
{
    int i;
    for(i=1; i<=G.numVertexes; i++)
        if(G.arc[v][i] == 1)
            return i;
    if(i == (G.numVertexes+1))
        return -1;
}
int NextAdjVex(MGrap G, int v, int w)
{
    int i;
    for(i=w+1; i<=G.numVertexes; i++)  //nextadjvex的问题出现在i要从w的下一个邻接点开始找而不是这一个。
        if(G.arc[v][i] == 1)
            return i;
    if(i == (G.numVertexes+1))
        return -1;
}

void DFS(MGrap G, int v)
{
    printf("%c",G.vexs[v]);
    visited[v] = 1;
    int w = FirstAdjVex(G, v); //图G中顶点v的第一个邻接点
    while(w != -1)
    {
        if(!visited[w]) DFS(G, w);
        w = NextAdjVex(G,v,w); //图G中顶点v的下一个邻接点
    }
}
int BFS(MGrap G, int v)
{

}
void TraverseGDFS(MGrap G)
{
    int i;
    for(i=1; i<=G.numVertexes; i++)
        visited[i] = 0;

    for(i=1; i<=G.numVertexes; i++)
    {
        if(!visited[i])
        {
      //      printf("第%d %d\n",i,visited[i]);
             DFS(G,i);
        }
           
    }
        printf("\n");
}
void TraverseGBFS(MGrap G)
{
    int i;
    for(i=1; i<=G.numVertexes; i++)
        visited[i] = 0;
    for(i=1; i<=G.numVertexes; i++)
        if(visited[i] == 0)
        {
            BFS(G,i);
        }
    
}



int main(int argc, char const *argv[])
{
    MGrap G;
    CreateMGraph(&G);
   // dushu(G); (注意！！！等会注释去掉！！！！！！！！！！！！)
    TraverseGDFS(G);
    TraverseGBFS(G);

    return 0;
}
