//大整数的乘法
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string a,b;
    cin>>a;
    cin>>b;  //a.back()访问最后的字符
    cout<<"a="<<a.back()<<endl;
    cout<<"b="<<b.back()<<endl;
    cout<<(a.back()-'0')*(b.back()-'0')<<endl;
    
    for(int i=b.size()-1; i>=0; i--)
    {
        int p = b[i]-'0';
        cout<<"p="<<p<<endl;
        flag = 0;
        for(int j=a.size()-1; j>=0; j--)
        {
            int q = a[j]-'0';
            
           // cout<<q<<endl;
            r = p*q;
            s = r/10;//进位
            r = r%10;//余数
            if(s>0)
                c[(a.size()-j+flag)] += s;
            else
                c[(a.size()-1-j+flag)] += r;
            

    }
}
