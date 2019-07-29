/*小猫跑数轴*/
//关键在于化解 i+1 因为在推演时已知到dp[i] dp[i+1]是未知的

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int x;
    cin>>x;
    x=abs(x);
    vector<int> dp(x+1);
    dp[0] = 0;
    dp[1] = 1;
       
    if(x>=0 && x<2)
    {
         cout<<dp[x]<<endl;
    }
        
    for(int i=2; i<=x; ++i)
    {
        if(i%2 == 0)
            dp[i] = min(dp[i-1],dp[i/2])+1;
        else
        {
            dp[i] = 1+min(dp[i-1],(dp[(i+1)/2]+1));
        }//i-1是从（i-1）/2处跳过来的 i+1是从（i+1）/2处跳过来的
    }
    cout<<dp[x]<<endl;
    return 0;
}
