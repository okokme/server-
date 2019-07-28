#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    string a,b;
    cin>>a>>b;
    for(int i=0; i<b.size(); i++)
    {
        for(int j=0; j<a.size(); j++)
        {
            if(a[j]>=b[i])
                continue;
            else 
            {
                a[j] = b[i];
                break;
            }
        }
    }
    cout<<a<<endl;
    return 0;
}
