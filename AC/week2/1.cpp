/*
 1. 牛牛对整除非常感兴趣。牛牛的老师给他布置了一道题：牛牛的
老师给出一个 n,然后牛牛需要回答出能被 1 到 n 之间（包括 1 和 n）
所有整数整除的最小的数。牛牛犯了难，希望你能编程帮他解决这个
问题。（题目来源：京东面试题）
输入描述:
输入包括一个整数 n(1<=n<=100000)
输出描述:
输出一个整数，即满足要求的最小整数。答案可能很大，请输出这个
整数对于 987654321 取模的结果
示例:
输入:
3
输出:
6
 */
#include <bits/stdc++.h>
using namespace std;
//大整数溢出 不对
int min_common(int a, int b)
{
    int min, max;
    int r;
    max = a>b?a:b;
    min = a<b?a:b;
    while(max%min != 0 )
    {
        r = max%min;
        max = min;
        min = r;
    }
    return (a*b/min);
}
main()
{
    int n;
    cin>>n;
    long long min = 0;
    int t = n;
    t--;
    min = min_common(t,t+1);
    while(--t)
    {
        long long a = min_common(t, min); 
        min = (min<a) ? min : a;
    }
    min = min%987654321;
    cout<<"min = "<<min<<endl;
}
