//多态性：运算符重载
//(1) 掌握运算符重载的基本方法。
//(2) 学习重载运算符为成员函数的方法。
//(3) 学习重载运算符为友元函数的方法
//1) 将运算符+和-重载为 complex 类的成员函数。
// #include<iostream>
// using namespace std;
// class complex //复数类声明
// {
// private: //私有数据成员
//     double real; //复数实部
//     double imag; //复数虚部
// public: //外部接口
//     complex(double r=0.0,double i=0.0) //构造函数
//     {real=r;imag=i;}
//     complex operator + (complex c2) //+重载为成员函数
//     {
//         complex tmp;
//         tmp.real = this->real + c2.real;
//         tmp.imag = this->imag + c2.imag;
//         return tmp;
//     }
//     complex operator - (complex c2) //-重载为成员函数
//     {
//         complex tmp;
//         tmp.real = this->real - c2.real;
//         tmp.imag = this->imag - c2.imag;
//         return tmp;
//     }
//     void display( ) //输出复数
//     {
//         cout<<this->real<<"+"<<this->imag<<"i"<<endl;
//     }
// };

// int main(int argc, char const *argv[])
// {
//     complex p(5,2);
//     complex q(1,7);
//     complex r,s;
//     r = p+q;
//     s = p-q;
//     r.display();
//     s.display();
//     return 0;
// }

//(2) 将运算符+和-重载为 complex 类的友元函数。
// #include<iostream>
// using namespace std;
// class complex
// {
// public:
// complex(double r=0.0,double i=0.0)
// { real=r; imag=i; } //构造函数
// friend complex operator + (complex c1,complex c2);
// //重载运算符+为友元函数
// friend complex operator - (complex c1,complex c2);
// //重载运算符-为友元函数
// void display(); //显示复数的值
// private: //私有成员
// double real;
// double imag;
// };
// complex operator + (complex c1, complex c2)
// {
//     complex tmp;
//     tmp.real = c1.real + c2.real;
//     tmp.imag = c1.imag + c2.imag;
//     return tmp;
// }
// complex operator - (complex c1, complex c2)
// {
//     complex tmp;
//     tmp.real = c1.real - c2.real;
//     tmp.imag = c1.imag - c2.imag;
//     return tmp;
// }
// void complex::display()
// {
//     cout<<this->real<<"+"<<this->imag<<"i"<<endl;
    
// }
// int main(int argc, char const *argv[])
// {
//     complex c1(3,5);
//     complex c2(4,9); 
//     complex c3, c4;
//     c3 = c1+c2;
//     c4 = c1-c2;
//     c3.display();
//     c4.display();
//     return 0;
// }

//(3) 完成下列的 String 类，并在主函数 main( )中测试它。
#include <cstdio>
#include <string>
#include <iostream>
#include <string.h>
using namespace std;
class String
{
public:
String(const char *str = NULL); // constructor
String(const String &other); // copy constructor
~String(void); // destructor
String & operate =(char *str);
String & operate =(const String &other);// 重载=运算符
int operator==(String &other); // 重载==运算符
int operator==(char *str);
private:
char *m_data; // used for storing the string
int length;
};
String::String(const String &other)
{
    this->length = other.length;
    this->m_data = new char[length];
    strcpy(this->m_data, other.m_data);
}
String::~String(void)
{
    if(m_data != NULL)
    delete [] m_data;
    length = 0;
}
String& String::operate=(char *)
{

}cd
int main(int argc, char const *argv[])
{
    String s1("aaaaa");
    String s2("bbbbbb");
    return 0;
}

