/*最大子序列 
【 题目描述】对于字符串 x 和 y, 如果擦除 x 中的某些字母(有可能全擦掉或者都不擦)能够得到 y,我们就 
称 y 是 x 的子序列。例如.”ncd”是”nowcoder”的子序列,而”xt”不是。 
现在对于给定的一个字符串 s,请计算出字典序最大的 s 的子序列。 
输入描述: : 
输入包括一行,一个字符串 s,字符串 s 长度 length(1 ≤ length ≤ 50). 
s 中每个字符都是小写字母 
输出描述: : 
输出一个字符串,即字典序最大的 s 的子序列。 
输入示例: : 
test 
输出示例: : 
tt

思路：先在字符串中顺序找到值最大的字符，然后擦除这个最大字符之前的所有字符，然后再在除已经找到的字符之后顺序找到值最大的字符，擦出它之前的字符，当找到的字符个数等于字符串的size时，就完成了。
*/
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    string a;
    char c;
    cin>>a;
    int sum = a.size();
    for(int i=sum-1; i>0; i-- )
    {
        c = a[i];
        for(int j=i-1; j>0; j--)
        {
            if(c>a[j])
            {
                auto it = a.begin()+j;
                a.erase(it);
            }
        }
    }
    cout<<a<<endl;
    return 0;
}
