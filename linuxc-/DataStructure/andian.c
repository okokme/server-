/*鞍点是指矩阵中的某元素A[i][j]是第i行中值最小的元素，同时又是第j列中值最大的元素。试设计一个算法求矩阵A中的所有鞍点。
*/
#include <stdio.h>
#define MAXSIZE 100
void andian(int a[MAXSIZE][MAXSIZE], int m, int n)
{
    int i,j,k;
    int min;
    int hrow=0,hcol=0;
    for(i = 0; i < m; i++)
    {
         min = a[i][0];
         for(j =0; j<n; j++)
        {
            if(a[i][j] < min)
            {
                min = a[i][j];
                hrow = i;
                hcol = j;
            }
         
        }
      
        for(k = 0; k<m; k++ )
        {
            if(a[k][hcol] > min)
            {
                 break; 
            }     
        }
        if(k == m)
            printf("鞍点为a[%d][%d]=%d\n",i,j,min);
        else
        {
            printf("k=%d\n",k);
        }
    } 
       
}


int main(int argc, char const *argv[])
{
    int a[MAXSIZE][MAXSIZE];
    int m,n,i,j;
    scanf("%d %d",&m,&n);
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            scanf("%d", &a[i][j]);
    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
            printf("%d ",a[i][j]);
            printf("\n");
    }
        
    andian(a,m,n);
    return 0;
}
