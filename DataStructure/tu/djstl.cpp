
#define MAXVEX 100 //最大顶点数
#define INFINITX 65535 //无穷大
typedef struct 
{
    char vexs[MAXVEX]; //顶点表
    int arc[MAXVEX][MAXVEX]; //邻接矩阵，可看做边表
    int numVertexes,numEdges; //图中当前的顶点数和边数
}MGrap;
int visited[MAXVEX];