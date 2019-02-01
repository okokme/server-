/*建立二叉树排序树，并实现查找，插入等操作*/
#include <iostream>

using namespace std;

typedef struct node
{
    int key;
    struct node *Lchild, *Rchild;
}BSTNode,*BSTree;
void CreateBST(BSTree *bst) //bst建立好后代表整个二叉排序树
{
    int key;
    scanf("%d",&key);
    *bst = NULL;
    while(key != ENDKEY)
    {
        InsertBST(bst, key);
        scanf("%d",&key);
    }
}
void InsertBST(BSTree *bst, int key)
{
    BSTree s;
    if(*bst == NULL)
    {
        s = (BSTree)malloc(sizeof(BSTNode));
        s->key = key;
        s->Lchild = NULL;
        s->Rchild = NULL;
        *bst = s;
    }
    else if(key < (*bst)->key) InsertBST((&(*bst)->Lchild), key);
    else if(key > (*bst)->key) InsertBST((&(*bst)->Rchild), key);
}

BSTree SearchBST(BSTree bst, int key)
{
    if(!bst)    return NULL;
    else if(bst->key == key)    return bst;
    else if(bst->key > key)     return SearchBST(bst->Rchild, key);
    else if(bst->key < key)     return SearchBST(bst->Lchild, key);
}