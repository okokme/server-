// Bfs
//找最短路径
//给定一个大小为N*M 的迷宫，迷宫由通道和墙壁组成 每一步可以向相邻的上下左右四格的通道移动 请求处从起点到终点所需的最小步数 
//如果不能到达 输出 “不能走到那里” （N,M<=50 起点 重点 分别用 S G表示）
//输入样例：
//       #S###
//       ..##.
//       #.###
//       ..###
//       ..G##
#include <bits/stdc++.h>
using namespace std;
int si,sj;
int ei,ej;
int x,y;
char a[50][50];
int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};
bool vis[50][50];
struct node {
    int x,y,step;
};

void bfs() {
    node p;
    p.x = si;
    p.y = sj;
    p.step = 0;
    queue<node> q;
    q.push(p);
    vis[si][sj] = 1;
    
    while(!q.empty())
    {
        node tmp = q.front();
        cout<<"a[][]="<<a[tmp.x][tmp.y]<<endl;
        q.pop();
        if(tmp.x == ei && tmp.y == ej)
        {
            cout<<"最短路径为"<<tmp.step<<endl;
            return ;
        }
        for(int i=0; i<4; i++)
        {
            int xx = tmp.x + dx[i];
            int yy = tmp.y + dy[i];
            if(a[xx][yy] != '#' && xx>0 & yy>0 && xx<=x && yy<=y &&!vis[xx][yy] )
            {
                cout<<"xx="<<xx<<" yy="<<yy<<"a[xx][yy]="<<a[xx][yy];
                node t;
                t.x = xx;
                t.y = yy;
                t.step = tmp.step+1;
                vis[xx][yy] = 1;
                q.push(t);
            }
        }
    }

}
int main(int argc, char const *argv[])
{
    cin>>x>>y;
    for(int i=1; i<=x; i++)
        for(int j=1; j<=y; j++)
        {
            cin>>a[i][j];
            if(a[i][j] == 'S')
            {
                si = i;
                sj = j;
            }
            else if(a[i][j] == 'G')
            {
                ei = i;
                ej = j;
            }
        }

    for(int i=1; i<=x; i++)
        for(int j=1; j<=y; j++)
            cout<<a[i][j];
            cout<<"\n";

    bfs();
    return 0;
}
