//大整数的乘法
//先不着急处理进位 否则会陷入到不停进位的麻烦中
#include <bits/stdc++.h>
using namespace std;
const int L = 10000;
void coculation(string a, string b)
{
    int ca[L],cb[L],cc[L];
    std::fill(cc,cc+L,0);
    int La = a.size();
    int Lb = b.size();
    for(int i=La-1; i>=0; i--) ca[La-i] = a[i]-'0'; 
    for(int j=Lb-1; j>=0; j--) cb[Lb-j] = b[j]-'0';
    for(int i=1; i<=La; i++)
        for(int j=1; j<=Lb; j++) 
            cc[i+j-1] += ca[i]*cb[j]; 
    for(int i=1; i<=La+Lb; i++)
    {
        cc[i+1] += cc[i]/10;
        cc[i] %= 10;
    }
    for(int i=La+Lb; i>0; i--) cout<<cc[i];
    cout<<"\n";
}
int main()
{
    string a,b;
    cin>>a>>b;
    coculation(a,b);;
}
