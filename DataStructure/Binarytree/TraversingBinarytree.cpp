/*题目描述
根据先序序列和中序遍历序列，建立二叉树。树状输出这棵二叉树
结点个数<=50
输入
第一行：先序序列
第二行：中序序列
输出
输出样例所示树状结构。

注意：（1）根结点前面无空格；

     （2）其它结点前面的空格数比其父结点前的空格数多2个。

样例输入
ABCDEGF
CBEGDFA
样例输出
A
      F
    D
        G
      E
  B
    C
提示*/
#include<iostream>
#include<tree.h>
class Solution {
public:
    int id=0;
    TreeNode* Creat(vector<int>&pre,vector<int>&vin,int l,int r,vector<int>&vis){
        //cout<<pre[k]<<' '<<l<<' '<<r<<endl;
        if(l>r) return NULL;
        TreeNode*rt=new TreeNode(pre[id]);
        if(l==r) return rt;
        int j;
        for(int i=l;i<=r;++i){
            if(vin[i]==pre[id]){
                j=i;
                break;
            }
        }
        vis[j]=1;
        if(j>l&&vis[j-1]==0){
            ++id;
            rt->left=Creat(pre,vin,l,j-1,vis);
        }
        if(j<r&&vis[j+1]==0){
            ++id;
            rt->right=Creat(pre,vin,j+1,r,vis);
        }
        return rt;
    }
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if(pre.size()!=vin.size()) return NULL;
        if(pre.size()==0) return NULL;
        TreeNode *root=new TreeNode(pre[0]);
        int j,len=pre.size();
        vector<int>vis(len,0);
        for(int i=0;i<vin.size();++i){
            if(pre[0]==vin[i]){
                j=i;
                break;
            }
        }
        vis[j]=1;
        if(j>0&&vis[j-1]==0){
            ++id;
            root->left=Creat(pre,vin,0,j-1,vis);
        }
        if(j+1<pre.size()&&vis[j+1]==0){
            ++id;
            root->right=Creat(pre,vin,j+1,len-1,vis);
        }
        return 
