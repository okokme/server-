#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int n,m,t;
    cin>>n;
    while(n--)
    {
        vector <int> s;
        cin>>m;
        while(m--)
        {
            cin>>t;
            for(int i=0; i<s.size(); i++)
            {
                if(t == s[i])
                    s[i] = 0;
            }    
            s.push_back(t);
        }
       for(int i=s.size()-1; i>=0; i--)
        {
            if(s[i]!=0)
                cout<<s[i]<<" ";
        } 
        cout<<'\n';
    }
    return 0;
}

