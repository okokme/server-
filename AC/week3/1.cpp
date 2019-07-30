/*给定一个无序数组，包含正数、负数和0 要求从中找出三个数的乘积 使得乘积最大
 *要求时间复杂度O(n),空间复杂度O(1)
 * */
//只遍历一遍，找最大的三个数
#include <iostream>
using namespace std;
int main()
{
    int data[4] = {3,4,1,2};
    int a=-99999,b=-99999,c=-99999;
    for(int i=0; i<4; i++)
    {
        if(data[i] > a)
        {
            c=b;
            b=a;
            a=data[i];
        }
        else if(data[i] > b)
        {
            c=b;
            b=data[i];
        }
        else if(data[i] > c)
        {
            c=data[i];
        }
    }
    cout<<a*b*c<<endl;

}
