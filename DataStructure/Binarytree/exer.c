typedef struct node
{
    char data;
    struct node *Lchild;
    struct node *Rchild;
}BirootNode,*BiTree;

int leaf(BiTree root)
{
    int l,r;
    if(root == NULL)    return 0;
    else if(!root->Lchild && !root->Rchild)
        return 1;
    l = leaf(root->Lchild);
    r = leaf(root->Rchild);
    return(r+l);
}

int deep(BiTree root)
{
    int hl,hr,h;
    if(root == NULL)    return 0;
    hl = deep(root->Lchild);
    hr = deep(root->Rchild);
    h = hl>hr ? hl:hr +1;
    return h;
}

//非叶子
int Notleaf(BiTree root)
{
    int l,r;
    if(root = NULL) return 0;
    else if(!root->Lchild && !root->Rchild)  return 0;
    else  return(!+Notleaf(root->Lchild)+Notleaf(root->Rchild)); 
}

//算指定的第K层的叶子结点个数。设根结点在第一层
int countleaf(BiTree root, int h, int k)
{
    if(root == NULL) return 0;
    if(h == k)
    {
        if(!root->Lchild && !root->Rchild)
            count++;
    }
    countleaf(root->Lchild,k,h+1);
    countleaf(root->Rchild,k,h+1);
}

//ABC##DE#G##F### 建立二叉链表存储结构
BiTree pretree()
{
    char item;
    BiTree root;
    scanf("%c",&item);
    if(item == 0)
        return NULL;
    if(item == '#')
        return NULL;
    else
    {
        root = (BiTree)malloc(sizeof(BirootNode));
        //先序
        root->data = item;
        root->Lchild = pretree();
        root->Rchild = pretree();
    }
    return root;
}

//桉树状顺序输出
h=1;
void outputtree(Bitree root, int h)
{
    if(root == NULL) return ;
    outputtree(root->Lchild,h+1);
    for(i=0; i<h; i++)
        printf("   ");
    printf("%c",root->data);
    outputtree(root->Rchild,h+1);
}

//二叉树的先序遍历
void printpre(BiTree root)
{
    if(root)
    {
        printf("%c",root->data);
        printpre(root->Lchild);
        printpre(root->Rchild);
    }
}