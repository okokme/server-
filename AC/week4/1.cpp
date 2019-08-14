#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    int h,l,nid;
    map<int, int> cheat;
    cin>>n;
 
    int a[1000][1000];
    for(int i=0; i<n; i++)
    {
        cin>>h;
        cin>>nid;
        a[i][0] = h;
        a[i][1] = nid;
        for(int j=2; j<nid+2; j++)
        {
            cin>>l;
            a[i][j] = l;
        }
    }
    cout<<"输入完毕"<<endl;
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<a[i][1]+2; j++)
        {
            cout<<a[i][j];
        }
        cout<<endl;
    }
    
}