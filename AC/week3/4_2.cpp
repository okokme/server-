#include <bits/stdc++.h>
using namespace std;
int x,y;
char a[100][100];
int sx,sy;
int ex,ey;
bool vis[100][100];
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
int M = 0;//门的个数
int Y = 0;//钥匙的个数
struct node 
{
    int x,y,step;
   // int M,Y;
};
void bfs()
{
    struct node p;
    p.x = sx;
    p.y = sy;
    p.step = 0;
    
    //if(M=)
}
int main(int argc, char const *argv[])
{
    int x,y;
    cin >>x>>y;
    char a[100][100];
    for(int i=1; i<=x; i++)
        for(int j=1; j<=y; j++)
            {
                cin>>a[i][j];
                if(a[i][j] == '2')
                {
                    sx = i;
                    sy = j;
                }
                else if(a[i][j] == '3')
                {
                    ex = i;
                    ey = j;
                }
            }
    bfs();
    return 0;
}
