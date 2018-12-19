/*三元组表矩阵的运算：
 已知两个稀疏矩阵A和B以三元组顺序表进行存储，编写算法实现A+B，A-B，所得结果存入新三元组表，并分析算法的时间复杂度。
 实现要求：算法的时间复杂度要尽量的低。
 可选作A*B，结果存入二维数组。*/

 #include <stdio.h>
 
 #define MAXSIZE 1000
 #define MAX 10
 //#define N 4
 typedef struct 
 {
     int row,col;
     int valude;
 }Triple;

 typedef struct
 {
     Triple data[MAXSIZE+1];
     int rows,cols,nums;
 }TSMatrix;
 int m,n;

 /*将系数矩阵转为三元组顺序表*/
void Triple_turn(TSMatrix *Ta, int A[MAX][MAX])
{
    int i,j;
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
        {
            if(A[i][j]!= 0)
            {
                Ta->data[Ta->nums].row = i;
                Ta->data[Ta->nums].col = j;
                Ta->data[Ta->nums].valude = A[i][j]; 
                Ta->cols++;
                Ta->rows++;
                Ta->nums++;
            }
        }
}

TSMatrix Triple_subtract(TSMatrix Ta, TSMatrix Tb)
{
    TSMatrix Tc;
    int i = 0, j = 0, k = 0;
    while(i < Ta.nums && j < Tb.nums )
    {
        if(Ta.data[i].row < Tb.data[j].row)
        {
            Tc.data[k] = Ta.data[i];
            k++;
            i++;
        }

        else if(Ta.data[i].row == Tb.data[j].row)
        {
            if(Ta.data[i].col == Tb.data[j].col)
            {
                Tc.data[k] = Ta.data[i];
                Tc.data[k].valude = Ta.data[i].valude - Tb.data[j].valude;
                i++;
                j++;
                k++;
            }
            else if(Ta.data[i].col > Tb.data[j].col)
            {
                Tc.data[k] = Tb.data[j];
                Tc.data[k].valude = -Tb.data[j].valude;
                j++;
                k++;
               
            }
            else 
            {
                Tc.data[k] = Ta.data[i];
                i++;
                k++;
               
            }

        }
        else
        {
            Tc.data[k] = Tb.data[j];
            Tc.data[k].valude = -Tb.data[j].valude;            
            j++;
            k++;
        }
    }
    
    while(i < Ta.nums)
    {
        Tc.data[k] = Ta.data[i];
        i++;
        k++;
    }

    while( j < Tb.nums)
    {
        Tc.data[k] = Tb.data[j];
        Tc.data[k].valude = -Tb.data[j].valude;        
        j++;
        k++;
    }
    Tc.nums = k;
//    Tc.rows = ;
//    Tc.cols = Ta.cols;
    return Tc;           

}

TSMatrix Triple_add(TSMatrix Ta, TSMatrix Tb)
{
    TSMatrix Tc;
    int i = 0, j = 0, k = 0;
    while(i < Ta.nums && j < Tb.nums )
    {
        if(Ta.data[i].row < Tb.data[j].row)
        {
            Tc.data[k] = Ta.data[i];
            k++;
            i++;
        }

        else if(Ta.data[i].row == Tb.data[j].row)
        {
            if(Ta.data[i].col == Tb.data[j].col)
            {
                Tc.data[k] = Ta.data[i];
                Tc.data[k].valude = Ta.data[i].valude + Tb.data[j].valude;
                i++;
                j++;
                k++;
            }
            else if(Ta.data[i].col > Tb.data[j].col)
            {
                Tc.data[k] = Tb.data[j];
                j++;
                k++;
               
            }
            else 
            {
                Tc.data[k] = Ta.data[i];
                i++;
                k++;
               
            }

        }
        else
        {
            Tc.data[k] = Tb.data[j];
            j++;
            k++;
        }
    }
    
    while(i < Ta.nums)
    {
        Tc.data[k] = Ta.data[i];
        i++;
        k++;
    }

    while( j < Tb.nums)
    {
        Tc.data[k] = Tb.data[j];
        j++;
        k++;
    }
    Tc.nums = k;
//    Tc.rows = ;
//    Tc.cols = Ta.cols;
    return Tc;           



}
 int main(int argc, char const *argv[])
 {
     TSMatrix Ta,Tb,Tc;
     int A[MAX][MAX], B[MAX][MAX];
     int i, j;
     printf("请输入矩阵的行数和列数：\n");
     scanf("%d %d",&m,&n);
     printf("请输入第一个%d*%d的矩阵：\n",m,n);
     for(i=0; i<m; i++)
        for(j=0; j<n; j++)
        {
            scanf("%d", &A[i][j]);
        }
     printf("请输入第二个%d*%d的矩阵：\n",m,n);
     for(i=0; i<m; i++)
        for(j=0; j<n; j++)
        {
            scanf("%d", &B[i][j]);
        }

    Tb.cols = Ta.cols = 0;
    Tb.nums = Ta.nums = 0;
    Tb.rows = Ta.rows = 0;

     Triple_turn(&Ta,A);
     Triple_turn(&Tb,B);
printf("矩阵相加后为：\n");
    Tc = Triple_add(Ta,Tb);
    for(i=0; i<Tc.nums; i++)
        printf("%d\n",Tc.data[i].valude);

    Tc = Triple_subtract(Ta,Tb);
printf("矩阵相减后为：\n");
    for(i=0;i<Tc.nums; i++)
        printf("%d\n",Tc.data[i].valude);        

     return 0;
 }
 
