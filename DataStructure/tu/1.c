/*已知图以邻接矩阵作为存储结构，编写算法判断两个指定顶点之间是否存在路径。*/

#define MAXVEX 100 //最大顶点数
#define INFINITX 65535 //无穷大
typedef struct 
{
    char vexs[MAXVEX]; //顶点表
    int arc[MAXVEX][MAXVEX]; //邻接矩阵，可看做边表
    int numVertexes,numEdges; //图中当前的顶点数和边数
}MGrap;

void CreateMGraph(MGraph *G)
{
    int i,j,k,w;
    printf("输入顶点和边数：");
    scanf("%d %d",&G->numVertexes, &G->numEdges);
    for(i=0; i<G->numEdges; i++)
        scanf("%c",&G->vexs[i]);
    for(i=0; i<G->numVertexes; i++) //先初始化
        for(j=0; j<G->numVertexes; j++)
            G->arc[i][j] = INFINITX;
    for(k=0; k<G->numEdges; k++)
        scanf("%d %d %d",&i,&j,&w); //输入边（vi,vj）上的上下标


}