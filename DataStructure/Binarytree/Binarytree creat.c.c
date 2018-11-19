/*一、二叉树的建立、遍历及应用：
 （1）输入二叉树的扩展先序遍历序列，建立二叉树的二叉链表存储，并按教材P135图6.16所示树状输出二叉树；
 （2）输出二叉树的先序遍历序列、中序遍历序列、后序遍历序列；
 （3）输出二叉树中非叶子结点的个数、二叉树第K层上叶子结点的个数、二叉树的高度。*/

 /*(1)题目描述
从键盘接收扩展先序序列，以二叉链表作为存储结构，建立二叉树。树状输出该二叉树。
输入
输入扩展先序序列。二叉树结点的data是字符类型数据, 其中#表示空格字符。
输出
输出样例所示树状结构。

注意：（1）根结点前面无空格；

          （2）其它结点前面的空格数比其父结点前的空格数多2个。

样例输入
ABC##DE#G##F###
样例输出
A
      F
    D
        G
      E
  B
    C
提示
*/
/*
(2)题目描述
从键盘接收扩展先序序列，以二叉链表作为存储结构，建立二叉树。输出这棵二叉树的先序、中序和后序遍历序列。
输入
输入扩展先序序列。二叉树结点的data是字符类型数据, 其中#表示空格字符。
输出
三行依次输出先序、中序、后序遍历序列。
样例输入
ABC##DE#G##F###
样例输出
ABCDEGF
CBEGDFA
CGEFDBA
*/

/*
(3)题目描述
从键盘接收扩展先序序列，以二叉链表作为存储结构，建立二叉树。统计二叉树中非叶子结点的个数，并输出。
样例输入
ABC##DE#G##F###
样例输出
4
*/

/*
(4)题目描述
从键盘接收扩展先序序列，以二叉链表作为存储结构，建立二叉树。并计算指定的第K层的叶子结点个数。设根结点在第一层。
第一行：扩展先序序列
第二行：k的值
样例输入
ABC##DE#G##F### 
3
样例输出
1
*/
/*
(5)题目描述
从键盘接收扩展先序序列，以二叉链表作为存储结构，建立二叉树。计算二叉树的高度，并输出。
样例输入
ABC##DE#G##F###
样例输出
5
*/
 #include<stdio.h>
 #include<stdlib.h>
#define MAX 100
typedef struct node
{
    char data;
    struct node *Lchild;
    struct node *Rchild;
}BirootNode,*BiTree;
int count = 0;
BiTree PreOrder()
{
    char item;
    BiTree root;
    scanf("%c",&item);
    if( item == 0 )             
	    root = NULL;          
    if(item == '#')   //叶节点数据标志：其后根两个#
        root = NULL;  //若某一节点为叶子结点，则其左右子树均为NULL，#表示建空树
    else
    {
        root = (BiTree)malloc(sizeof(BirootNode));
        root->data = item;
        root->Lchild = PreOrder();
        root->Rchild = PreOrder();
    }
    return root;
}

//按树状输出
void OutOrder(BiTree root,int h)
{
    int i;
    if(root == NULL ) return;
    if(root->data != '#')
    {
        OutOrder(root->Rchild,h+1);
        for(i=1; i<h; i++)
            printf("    ");
        printf("%c\n",root->data);
        OutOrder(root->Lchild,h+1);
    }
}

//输出二叉树的先序中序后续遍历序列
void PrintPre(BiTree root)
{
    if(root)//root!=NULL
    {
        printf("%c",root->data);
        PrintPre(root->Lchild);
        PrintPre(root->Rchild);
    }
}
void PrintIn(BiTree root)
{
    if(root)
    {
        PrintIn(root->Lchild);
        printf("%c",root->data);
        PrintIn(root->Rchild);
    }
}
void PrintPost(BiTree root)
{
    if(root)
    {
        PrintPost(root->Lchild);
        PrintPost(root->Rchild);
        printf("%c",root->data);
    }
}

//统计二叉树中非叶子节点的个数并输出
int NotLeaf(BiTree root)
{
    int lenL,lenR; 
    if(root == NULL) 
        return 0;
    else if( !root->Lchild && !root->Rchild )
        return 0;   
    else
        return (1+NotLeaf(root->Lchild)+NotLeaf(root->Rchild));
}

//统计叶子结点
int Leaf(BiTree root)
{
   
        int lenL,lenR;
        if(root == NULL) return 0; //注意这句话必须有
        else if(!root->Lchild  && !root->Rchild)
            return 1;
        lenL = Leaf(root->Lchild);
        lenR = Leaf(root->Rchild);
        return (lenL+lenR);   
}

//算指定的第K层的叶子结点个数。设根结点在第一层
void CengLeaf(BiTree root, int k, int h)
{
    if(root == NULL) return;
    if(h==k)
    {
        //int lenL,lenR;
//if(root == NULL)
        //    return 0;
      if(!root->Lchild && !root->Rchild)
            count++;
     //   lenL = CengLeaf(root->)

    }
    CengLeaf(root->Lchild,k,h+1);
    CengLeaf(root->Rchild,k,h+1);

}
//二叉树的高度
int depthTree(BiTree root)
{
    int hl,hr,h;
    if(root == NULL) return 0;
    //分解成每一个子树看
    hl = depthTree(root->Lchild);
    hr = depthTree(root->Rchild);
   // hl>hr ? hl:hr;//只这样是不行滴,根本没有深度加1途径。
    h = 1+(hl>hr ? hl:hr);
    return h;
}
// 释放空间
BiTree FreeTree(BiTree T)
{
    if(T)
    {
        FreeTree(T->Lchild);
        FreeTree(T->Rchild);
        free(T);
        T = NULL; //释放指向根节点的指针
    }
    return T;
}
 int main()
 {
    int h = 1;
    BiTree root;
    root = PreOrder();  //创建二叉树
    OutOrder(root,h); //按树状打印
    PrintPre(root); //先序遍历
    printf("\n");
    PrintIn(root); //中序遍历
    printf("\n");
    PrintPost(root); //后序遍历
    printf("\n");
    int len = NotLeaf(root); //非叶子节点的个数
    printf("非叶子节点的个数为%d\n",len);
    int k;
    printf("请输入你想查询的层数：");
    scanf("%d",&k);
    CengLeaf(root,k,h); //k层的叶子节点个数
    printf("%d层叶子结点的个数为：%d\n",count);
    int depth = depthTree(root); //二叉树的深度
    printf("二叉树的深度为：%d\n",depth);
 }

