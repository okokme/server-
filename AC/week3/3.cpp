#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<int> h;
    vector<int> w;
    int i,j;
    int t;
    cin>>i;
    while(i--)
    {
        cin>>t;
        h.push_back(t);
    }
    cin>>j;
    while(j--)
    {
        cin>>t;
        w.push_back(t);
    }
    sort(h.rbegin(), h.rend());
    sort(w.rbegin(), w.rend());
    // for(auto x:h) cout<<x<<" ";
    // for(auto x:w) cout<<x<<" ";     
    int flag = 0;
    auto itw = w.begin();
    while(itw!= w.end())
        {
            auto ith = h.begin();
            if(*itw >= *ith )
            {
                w.erase(w.begin());
                h.erase(h.begin());
                flag++;
            }
            else
                break;
        }
        cout<<flag<<endl;
}