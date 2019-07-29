//没有不能被4整除的偶数，4的倍数数目>=奇数数目-1
//有不能被4整除的偶数，4的倍数数目>=奇书数目
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    int a=0,b=0,c=0;
    int n,sum;
    cin>>sum;
    int t;
    while(sum--)
    {
        cin>>n;
        while(n--)
        {
            cin>>t;
            if(t%4 == 0)
                a++;
            else if( t%2 == 0)
                b++;
            else
                c++;
        }
        if(b!=0) //有偶数
        {
            cout<<"a="<<a<<"b="<<b<<"c="<<c<<endl;
            if(a>=c)
                cout<<"Yes"<<endl;
            else
                cout<<"No"<<endl;
        }
        else //没有偶数
        {
            cout<<"a="<<a<<"b="<<b<<"c="<<c;
            
            if(a>=c-1)
                cout<<"Yes"<<endl;
            else
                cout<<"No"<<endl;
        }
    }
    return 0;
}
