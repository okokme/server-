/*
2. 牛牛有两个字符串 A 和 B,其中 A 串是一个 01 串,B 串中除了可能
有 0 和 1,还可能有'?',B 中的'?'可以确定为 0 或者 1。 寻找一个字
符串 T 是否在字符串 S 中出现的过程,称为字符串匹配。牛牛现在考
虑所有可能的字符串 B,有多少种可以在字符串 A 中完成匹配。
例如:A = "00010001", B = "??" 字符串 B 可能的字符串是"00","01","10","11",只有"11"没有出现
在字符串 A 中,所以输出 3（题目来源：百度面试题）
输入描述:
输入包括两行,第一行一个字符串 A,字符串 A 长度 length(1 ≤
length ≤ 50),A 中每个字符都是'0'或者'1'。第二行一个字符串 B, 字符串 B 长度 length(1 ≤ length ≤ 50),B 中的字符包括'0','1' 和'?'。
输出描述:
输出一个整数, 表示能匹配的字符串种数。
示例:
输入:
00010001
??
输出:
3
*/
#include <bits/stdc++.h>
using namespace std;
int match(string& a, string& b)
{
    std::set<string> node;
    int flag = 0;
    if(b.size() > a.size() )
        return 0;
    for(int i=0; i<(a.size()-b.size()+1); i++)
    { 
        flag=0;
        for(int j=0; j<b.size(); j++)
        {
            if(a[i+j] == b[j])
                flag++;
            else if(b[j] == '?')
                flag++;
            else
                break;
            if(flag == b.size())
            {
                node.insert(a.substr(i,b.size()));
            }
        }
    }
    return node.size();
}
int main(int argc, char const *argv[])
{
    string a,b;
    cin>>a>>b;
    int sum = match(a,b);
    cout<<sum<<endl;
    return 0;
}
