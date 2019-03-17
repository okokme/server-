#include <iostream>
using namespace std;
#include "MyString.h"

int main(int argc, char const *argv[])
{
    MyString s1;
    MyString s2("s2");
    MyString s2_2 = NULL;
    MyString s3 = s2;
    MyString s4 = "ffffffffffffff";

    //测试运算符重载 和重载[]
    s4 = s2;
    s4 = "s222222";
    //求字符串数组元素  
    s4[1] = '4';
    printf("%c", s4[1]);

    cout<<s4<<endl;
    // ostream& operator<<(ostream &out, const MyString &s);
    cin>>s1;
    cout<<s4<<endl;
    // istream& operator>>(istream &in, const MyString &s);
    //类与字符串比较
    if(s2 == "s222222")
    {
        cout<<"相等"<<endl;
    }
    else
    {
        cout<<"不相等"<<endl;    
    }
    //类与对象比较
    if(s3 == s2)
    {
        cout<<"相等"<<endl;        
    }
    else
    {
        cout<<"不相等"<<endl;        
    }
    s3 = s1 + s2;
    cout<<s3.c_str()<<endl;

     MyString str("Teat string");
    // for(std::string::iterator it=str.begin(); it!=str.end(); ++it)
    //     cout<<*it<<endl;
    // cout<<'\n';
    cout<<str.erase(2,5)<<endl;
    cout<<str.find("er")<<endl;

    for(MyString::iterator t = str.begin(); t!=str.end(); t++)
        cout<<*t;
    cout<<'\n';
  //  t = "aaaaaaaaa";
  //  cout<<t<<endl;
    
    return 0;
}
