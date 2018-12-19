#include<stdio.h>
#include<string.h>
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
int map[9][8];
int pre[100];
int visit[9][8];

struct str
{
    int x;
    int y;
}q[3000];
void print(int n);
void bfs()
{
    int i,j;
    int front = 0;
    int rear = 1;
    int vx,vy;
    int a,b;
    for(i=0; i<9; i++)
    for(j=0; j<8; j++)
    visit[i][j] = 0;
    q[0].x = 0;
    q[0].y = 0;
    pre[0] = -1;
    while(front<rear)
    {
        a = q[front].x;
        b = q[front].y;
        if(a == 8 && b == 7)
        {
            print(front);
            return ;
        }

        for(i = 0; i < 4; i++)
        {
            vx = a + dx[i];
            vy = b + dy[i];
            if(visit[vx][vy]==0 && vx>=0 && vx<9 && vy>=0 &&vy<8 && map[vx][vy]==0)
            {
                visit[vx][vy] = 1;
                q[rear].x=vx;
                q[rear].y=vy;
                pre[rear]=front;
                rear++;
            }
        }
        front++;
    }
    return;
}
void print(int n)
{
    int t;
    t=pre[n];
    if(t==0)
    {
        printf("(0, 0)\n");
        printf("(%d, %d)\n",q[n].x,q[n].y);
        return ;
    }
    else
    {
        print(t);
        printf("(%d, %d)\n",q[n].x,q[n].y);
    }
}
int main(void)
{
    int i,j;
    for(i=0; i<9; i++)
    for(j=0; j<8; j++)
    scanf("%d",&map[i][j]);
    bfs();
    return 0;
}
