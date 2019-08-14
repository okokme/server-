#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int m,n,t;
    cin>>m>>n;
    vector<vector<int>> ps(m,vector<int>(n,0));
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
        {
            cin>>t;
           ps[i][j] = t;
        }
        cout<<"输入完毕"<<endl;
    
    int maxn=-9999;
    int num=1;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        { 
            num = 1;
           for(int k=0; k<n; k++)
                num *= ps[i][k];
            for(int l=0; l<m; l++)
                num *= ps[l][j];
            num = num/ps[i][j]/ps[i][j];
            maxn = max(maxn, num);
         //   cout<<"maxn"<<maxn<<endl;
        }
    }
     cout<<maxn<<endl;   
    return 0;
}