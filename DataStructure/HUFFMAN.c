/*题目描述
假设某通信报文的字符集由A,B,C,D,E,F这6个字符组成，它们在报文中出现的频度（频度均为整数值）。
(1)构造一棵哈弗曼树，依次给出各字符编码结果。
(2)给字符串进行编码。
(3)给编码串进行译码。
3
规定：
构建哈弗曼树时：左子树根结点权值小于等于右子树根结点权值。
生成编码时：左分支标0，右分支标1。

输入
第一行：依次输入6个整数，依次代表A,B,C,D,E,F的频度，用空格隔开。
第二行：待编码的字符串
第三行：待译码的编码串
输出
前6行依次输出各个字符及其对应编码，格式为【字符:编码】（冒号均为英文符号）
第7行：编码串
第8行：译码串
样例输入
3 4 10 8 6 5
BEE
0010000100111101
样例输出
A:000
B:001
C:10
D:01
E:111
F:110
001111111
BADBED
提示
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//存储结构：静态三叉链表（三个指针）
//哈弗曼树中，没有度为1的节点---正则二叉树#
//性质：n个叶子的哈弗曼树中，有n-1个度为2的节点，所以哈弗曼树中共有2n-1个节点，可以存储在大小为2n-1的一位数组中
#define N 6
#define M 2*N-1
typedef struct node
{
    int weight; //结点的权值
    int parent; //双亲节点在数组中的下标
    int Lchild,Rchild; //左孩子和右孩子在数组红的下标
}HuffmanTree[M+1];
//静态三叉链表中，前n个元素存储叶子节点，后n-1个元素存储分支接点不断生成的新节点，最后一个节点是叶子节点


void select_min(const HuffmanTree ht, int n, int *s1, int *s2)
{//选出权重最小的两个节点的顺序号
    int min = 2147483647;
    int i;
    for(i=1; i<=M; i++)
        if((min > ht[i].weight) && (ht[i].parent == 0) && (ht[i].weight!=0))
        {
             *s1 = i;
             min = ht[i].weight;
        }
           
    min = 2147483647;            
    for(i=1; i<=M; i++)
        if((min > ht[i].weight) && (ht[i].parent == 0) && (i != *s1) && (ht[i].weight!=0))
        {
              *s2 = i;
              min = ht[i].weight;
        }
}

//建立哈弗曼树
void CrtHuffmanTree(HuffmanTree ht, int w[], int n)
{
    int m = 2*n-1;
    int i, j;
    int s1,s2;
    for(i=1; i<=n; i++) ht[i] = (struct node){w[i],0,0,0};

    for(i=n+1; i<=m; i++)   ht[i] = (struct node){0,0,0,0};


    for(i=n+1; i<=m; i++)
    {
        select_min(ht,i-1,&s1,&s2); //查找出select_min函数出错
  //      printf("s1=%d,s2=%d\n",s1,s2);
        ht[i].weight = ht[s1].weight + ht[s2].weight;
        ht[i].Lchild = s1;
        ht[i].Rchild = s2;
        ht[s1].parent = ht[s2].parent = i;
 //       printf("m=%d\n",m);
  /*      
    printf("第i内%d波1-n：\n",i);            
        for(j=1; j<=M; j++)
        printf("%d %d %d %d\n",ht[i].weight,ht[i].parent,ht[i].Lchild,ht[i].Rchild);
        printf("\n");
        printf("m=%d\n",m);*/
    }
 //   printf("i=%d\n",i);

  /*  printf("第end波1-n：\n");        
    for(i=1; i<=M; i++)
        printf("%d %d %d %d\n",ht[i].weight,ht[i].parent,ht[i].Lchild,ht[i].Rchild);*/
}

//哈弗曼编码
//在哈弗曼树上求各 叶子节点 的编码
//由于每个哈弗曼编码的长度不相等，因此可以按照编码的实际长度动态分配空间，但要使用一个指针数组存放每个编码串的头指针
typedef char * Huffmancode[N+1];
//(1)从叶子节点开始，沿着节点的双亲链追溯到根节点，追溯过程中，每上升一层，则经过了一个分支，便可得到一位哈弗曼码值
//(2)从叶子到根得到的码串为哈弗曼编码的逆串，使用临时数组cd每位编码从后往前逐位放入cd中。start指针控制存放的次序
//(3)到达个节点时，一个叶子的编码构造完成，此时将cd数组中start为开始的串复制到动态申请的编码空间即可

void CreHuffmanCode1(HuffmanTree ht,Huffmancode hc, int n )
{
    char *cd;//hj
    int start;
    int c,p;
    int i;
    cd = (char *)malloc(n*sizeof(char));//因为最坏情况下构建一棵一溜到底的二叉树最长也只需要n-1个0，然后最后一位放\0刚好n个空间
    cd[n-1]= '\0';//从后向前逐位求编码，首先放编码结束符
    //从每个叶子开始，求相应的哈弗曼编码
    for(i=1; i<=n; i++)//从每个叶子节点开始，求相应的哈弗曼编码
    {
        start = n-1; //每次初始化到\0指向的地方
        c = i; //c为当前节点
        p = ht[i].parent; //p为双亲
        while(p!=0)//当p不为根节点时。 因为初始化时若一个节点没有父亲节点，就是其初始化的值0.
        {
            --start;
            if(ht[p].Lchild == c)
                cd[start] = '0';
            else
                cd[start] = '1';
            c = p;
            p = ht[p].parent;
        }
        hc[i] = (char*)malloc(sizeof(char)*(n-start));
      
        strcpy(hc[i],&cd[start]);
   //       printf("while内%s\n",hc[i]);
    }
    for(i=1; i<=6; i++)
    {
        printf("%c:%s\n",64+i,hc[i]);
    }
    
}

//译码从哈弗曼树的根出发，根据每一位编码的0或1
//确定进入左子树or右子树，直至到达叶子节点，便识别了一个相应的字符。
void TransHuffmancode(Huffmancode hc, char w[])
{
    int t = 0;
    int p = 0;
    char temp[100];
    int i;
    while(w[p] != '\0')
    {
        temp[t++] = w[p];
        temp[t] = '\0';
        for(i=1; i<=6; i++)
        {
            if(strcmp(temp, hc[i]) == 0)
            {
                printf("%c",64+i);
                t=0;
            }
        }
        p++;
    }

    // int i,j;
    // char temp[];
    // while(s!='\0')
    // {
    //     temp[t++] = w[i];
    // }
    // ht[i]

}
int main(int argc, char const *argv[])
{
    int i,j;
    int w[N+1];
    char crehu[100];
    for(i=1; i<=6; i++)
        scanf("%d",&w[i]);
 //   n = sizeof(w)/sizeof(int);
    HuffmanTree ht;
    Huffmancode hc;
    CrtHuffmanTree(ht, w, N); 
    CreHuffmanCode1(ht,hc,N);
    int num = 0;
    char ch;
    getchar(); //过滤上个\n
    while((ch = getchar()) != '\n')
    {
        crehu[num] = ch;
        num++;
    }
  //  printf("%s\n",crehu);测试存进去了
 //   printf("num = %d\n",num);
    for(i=0; i<num; i++)
        for(j=1; j<=6; j++)
            if((int)crehu[i] == 64+j)
                printf("%s",hc[j]);
                printf("\n"); //这里如果加一个换行符让机器换行的话，手动输入的回车就会一起合并不会到下一个%s or getchar()去
 // getchar();
  char transhu[100];
  scanf("%s",transhu);
  TransHuffmancode( hc, transhu);

    return 0;
}
