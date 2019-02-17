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
    // MyString& operator=(const char *p);
    // MyString& operator=(const MyString &s);

    //求字符串数组元素  
    s4[1] = '4';
    printf("%c", s4[1]);
    // s4[0];
    // char& operator[] (int index);
    
    cout<<s4<<endl;
    // ostream& operator<<(ostream &out, const MyString &s);
    
    //类与字符串比较
    // bool operator==(const char*p);
    // bool operator==(const MyString& s);
    // bool operator!=(const char*p);
    // bool operator!=(const MyString& s);
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
    return 0;
}
