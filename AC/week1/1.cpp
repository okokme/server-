//后一天要比前一天多，或者相等
//二分查找从1到M查找第一天吃的巧克力数，求得按照要求的最低的标准（不少于前一天的一半）
//暴力循环
//（N<=50000） (N<=M<=100000)
#include <iostream>
using namespace std;

int sum(int s,int day)
{
    int sum=0;
    for(int i=0; i<day; i++)
    {
        sum+=s;
        s=(s+1)/2;
    }
    return sum;
}
int SearchMax(int total, int day)
{
    int low = 1;
    int high = total;
    if(total == day)
        return 1;
    if(day == 1)
        return total;
    while(low < high)
    {
        int mid = (low+high+1)/2; //(low+high)/2为什么不行？
        if(sum(mid,day) == total)
            return mid;
        else if(sum(mid,day) <total )
            low = mid;
        else
            high = mid-1;
    }
    return high;
}
int main()
{
    int M,N;
    cin>>N>>M;
    int one = SearchMax(M,N);
    cout<<one<<endl;
    return 0;
        
}
