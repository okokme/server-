#include<cstdio>
#include<iostream>
#define MAXVEX 20
usiing namespace std;

typedef struct EdgeNode /*边表节点*/
{
    int adjvex; //邻接点域，存储该顶点对应的下标
    int weight; //用于存储权值，对于非网图可以不需要。
    struct EdgeNode *next; //链域。指向下一个邻接点
}EdgeNode;

typedef struct VertexNode //顶点表节点
{
    int data; //顶点域，存储顶点信息
    EdgeNode *firstedge; //边表头指针
}VertexNode,AdjList[MAXVEX];

typedef struct 
{
    AdjList adjList;
    int numVertexes, numEdges; //图中当前顶点数和边数
}GraphAdjList;


//邻接表的创建
void CreateALGrapgh(GraphAdjList *G)
{
    int i, j, k;
    EdgeNode *e;
    printf("输入顶点数和边数：\n");
    cin>>G->numVertexes>>G->numEdges;
    for(i=1; i<=G->numEdges; i++)
    {
        cin>>G->adjList[i].data;
        G->adjList[i].firstedge = NULL; //将边表置为空表
    }
    for(k=1; k<=G->numEdges; k++)
    {
        printf("输入边（vi，vj）上的顶点序号：\n");
        scanf("%d,%d",&i,&j);
        e = (EdgeNode*)maolloc(sizeof(EdgeNode));
        e->adjvex = j; //临接序号为j
        e->next = G->adjList[i].firstedge; //将e指针指向当前顶点指向的结点
        G->adjList[i].firstedge  = e; //将当前顶点的指针指向e
      
        /*若为无向图将注释去掉*/
        // e = (EdgeNode*)malloc(sizeof(EdgeNode)); //向内存申请空间，生成边表节点
        // e->adjvex = i;//临接序号为i
        // e->next = G->adjList[j].firstedge;
        // G->adjList[j].firstedge = e;

    }

}
int main()
{
    GraphAdjList G;
    CreateALGrapgh(&G);

}