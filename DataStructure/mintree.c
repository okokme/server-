
#include<stdio.h>
struct 
{
    vetexData adjvex; 
    int lowcost; 
}closedge[MAX_VERTEX_NUM];

MiniSpanTree_Prim(AdjMtrix gn, VertexData u)//gn 邻接矩阵存储的那个网 //u选中作为生成树上的根的那个顶点
{
    k = LocateVertex(gn, u); //确定当前这个生成树的根，在网里边的下标值
    closedge[k].lowcost = 0;//说明它已经被选中了
    for(i=0; i<gn.vexnum; i++)
        if(i!=k)
        {
            closedg[i].adjvex = u;
            closedg[i].lowcost = gn.arcs[k][i].agj;
        }//我现在能连接的顶点都是出发点u所对应的那一行
    
    for(e=1; e<gn.vexnum-1; e++)
{
    k0 = Minium(closeedge);
    u0 = closedge[k0].adjvex;
    v0 = gn.vexs[k0];
    printf(u0,v0);
    closedge[k0].lowcost = 0;
    for(i = 0; i<vexnum; i++)
    {
        if(gn.arcs[k0][i].adj < closedge[i].lowcost)
        {
            closedge[i].lowcost = gn.arcs[k0][i].adj;
            closedge[i].adjvex = v0;
        }
    }

}


}