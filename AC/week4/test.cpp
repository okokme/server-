#include <bits/stdc++.h>
using namespace std;
int main()
{
   int n;
   while(cin>>n)
   {
        vector<vector<int>> ps(n,vector<int>(n,0));
        while(n--)
        {
            int i,m;
            cin>>i,m;
            while(m--)
            {
                int k;
                cin>>k;
                ps[i-1][k-1] = k;
            }
        }
        set<int> cs;
        for(int i=0; i<ps.size(); i++)
            for(int j=i+1; j<ps.size(); j++)
            {
                if(ps[i][j] && ps[j][i])
                {
                    cs.insert(i);
                    cs.insert(j);
                }
            }
        bool find = true;
        while(find)
        {
            for(int i=0; i<ps.size(); i++)
            {
                if(cs.count(i)) continue;
                int cc=0;
                for(auto it=cs.begin();it!=cs.end();it++)
                {
                    if(ps[i][*it]==1) cc++;
                    if(cc>=2)
                        break;
                }
                if(cc>=2)
                {
                    cs.insert(i);
                    i=0;
                    find = true;
                    continue;
                }
            }
            find = false;
        }
        cout<<cs.size()<<endl;
        int cc=0;
        for(auto it=cs.begin();it!=cs.end();it++){
            if(++cc == cs.size())
                cout<<*it+1<<endl;
            else cout<<*it+1<<" ";
        }

   }
  
       return 0;
}