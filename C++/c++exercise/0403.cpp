// comparing size, length, capacity and max_size
// #include <iostream>
// #include <string>
// using namespace std;
// int main ()
// {
//   string str ("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
//   cout << "size: " << str.size() << "\n";
//   cout << "length: " << str.length() << "\n";
//   cout << "capacity: " << str.capacity() << "\n";
//   cout << "max_size: " << str.max_size() << "\n";
//   return 0;
// }
/*通过阅读C++标准库中的string两者的源码发现size（） 和length() 的源代码是没有区别的 
 *所以str.length()和str.size()输出结果是相等的原理也没有什么区别。
 *返回的是字节数
 
 max_size()返回的是一个string最多能包含的字符数。一个string通常包含一块单独内存区块的所有字符。
 所以可能跟pc机器本身的限制有关。返回值一般是索引值的最大值减1。
 减-的原理有：
 （1）最大值本身是npos;
 （2）在具体实现中可因此在内部缓冲区之后添加一个’\0‘,以便这个string当做C-string使用（例如c_str()）.
 一旦某个操作函数使用一个长度大于max_size()的string，length_err异常就会被抛出。

 capacity()返回已分配存储的大小
 返回当前为字符串分配的存储空间的大小，以字节为单位表示。
 此容量不一定等于字符串长度。它可以相等或更大，当容量耗尽且需要更多容量时，将由对象自动扩展（重新分配存储空间），字符串长度的理论限制由成员max_size给出
 比如测试 string str("aaa"); str.capacity()=15; string str("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") str.capacity()=43
 
 string类中字符串存储的是一个指针指向堆中new的一个位置。 使用sizeof(string)不论是多长的字符串得到的值都为4，因为它存储的是一个指针。
 在对string类用字符串赋值的时候，会隐式使用动态内存分配；先检查指针是否为NULL，如果为NULL，则分配足够的动态内存；
 如果指针不为NULL，那么检查已有的动态内存的长度是否可以放下该字符串，如果不可以，重新分配内存。
 
 */


//(2) 下面的程序演示了string类对象的插入insert方法，编译、运行该程序。想一想如果要你实现字符串的插入，需要完成哪些操作步骤？ 

//  Demonstrate insert().
// #include <iostream>
// #include <string>
// using namespace std;

// int main()
// {
//   string str1("The website address of our university is:");
//   string str2("www.xupt.edu.cn");

//   cout << "Initial strings:\n";
//   cout << "str1: " << str1 << endl;
//   cout << "str2: " << str2 << "\n\n";  
// // demonstrate insert()
//   cout << "Insert str1 into str2:\n";
//   str2.insert(0,str1);/*将str1插入str2的最开始*/
//   cout << str2 << "\n\n";
// }
// /*如果我实现字符串的插入，我会衡量插入字符串的长度，找到被插入的位置，给被插入字符串增加内存空间。将被插入位置及以后的向后字符串向后挪插入字符串个位，再把插入的字符串放进来*/

//(3) 下面的程序演示了string类对象的删除erase方法，编译、运行该程序。想一想如果要你实现字符串中的子串的删除，需要完成哪些操作步骤？
// string::erase
// #include <iostream>
// #include <string>
// using namespace std;
// int main ()
// {
//   std::string str ("This is an example sentence.");
//   std::cout << str << '\n';
//                                            // "This is an example sentence."
//   str.erase (10,8);                        //            ^^^^^^^^
//   std::cout << str << '\n';
//                                            // "This is an sentence."
//   str.erase (str.begin()+9);               //        ^
//   std::cout << str << '\n';
//                                            // "This is a sentence."
//   str.erase (str.begin()+5, str.end()-9);  // ^^^^^
//   std::cout << str << '\n';
//                                            // "This sentence."
//   return 0;
// }
// /*如果是我实现子串的删除，需要先衡量子串长度是否够删
//   再根据指针去把相应指向的位置向前覆盖，并且重新衡量该字符串长度并存储
// */


//(4) 下面的程序演示了string类对象的查找find方法，阅读并编译、运行该程序，观察输出结果。利用你在数据结构课程中学习过的字符串查找算法完成本题类似的查找操作。
// string::find
#include <iostream> 
#include <string> 
using namespace std;

int main ()
{
  string str ("There are two needles in this haystack with needles.");
  string str2 ("needle");

  // different member versions of find in the same order as above:
  int found = str.find(str2);
  if (found!=-1)
    cout << "first 'needle' found at: " << found << '\n';

  found=str.find("needles are small",found+1,6);
  if (found!=-1)
    cout << "second 'needle' found at: " << found << '\n';

  found=str.find("haystack");
  if (found!=-1)
    cout << "'haystack' also found at: " << found << '\n';

  found=str.find('.');
  if (found!=-1)
    cout << "Period found at: " << found << '\n';

  // let's replace the first needle:
  str.replace(str.find(str2),str2.length(),"preposition");
  cout << str << '\n';

  return 0;
}
/*查找可以使用数据结构课中的字符串匹配，BF算法或者KMP算法
int MyString::find(const char *p)
{
   if(m_len == 0) return -1;
    int i=0, j=0;
    int start = 0;
    while(i<m_len && j<strlen(p))
        if(m_p[i] == p[j]) {i++; j++;}
        else
        {
            start++;
            i=start;
            j=0;
        }
    if(j>=strlen(p)) return start;
    else return -1;
}
*/

// 编程实现一个简单的计算器，实现两个整数的加、减、乘、除。
// 当运算符为+、-、*、/、%时，在一行输出相应的运算结果。若输入是非法符号（即除了加、减、乘、除和求余五种运算符以外的其他符号）则输出ERROR。
// 例如：
// 输入样例1：
// -7 / 2
// 输出样例1：
// -3
// 输入样例2：
// 3 & 6
// 输出样例2：
// ERROR
#include<iostream>
#include<string>
using namespace std;
class solution
{
public:
    int calculate(string s)
    {
        int result = 0;

    }
};

int main(int argc, char const *argv[])
{
    solution so;
    string std;
    cin>>std;
    int result = so.calculate(std);
    //int found=std.find('+')
    cout<< result <<endl;
    return 0;
}
