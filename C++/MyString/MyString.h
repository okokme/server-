#pragma
#include <iostream>
#include <string.h>
#include <assert.h>
#include <string>
using namespace std;

class MyString
{
    friend ostream& operator<<(ostream &out, const MyString &s);
    friend istream& operator>>(istream &in, MyString &s);
   // friend MyString operator+(const MyString& s1, const MyString& s2);//s3 = s1 + s2;
    
private: 
    int m_len;
    char *m_p;
public:
    MyString();
    MyString(const char *p);
    MyString(const MyString& s);
    ~MyString();
    int size(); 
    const  char* c_str();//返回c风格字符串指针    
    MyString& operator=(const char* p); //重载=运算符 s1 = "dddd";
    MyString& operator=(const MyString &s); //s2 = s1
    char& operator[](int index); //a[5]
    bool operator==(const char* p); //s1 == "dsdsd"
    bool operator==(const MyString &s);//s1 == s2
    bool operator!=(const char* p);//s1 != "adddd"
    bool operator!=(const MyString &s);//s2 != s1
  //  friend MyString& operator+(const MyString& s1, const MyString& s2);//s3 = s1 + s2;    
    friend MyString operator+(const MyString& s1, const MyString& s2);//s3 = s1 + s2;
    int find(const char *p);
    MyString& erase(int pos, int len);//删除从下标pos开始的len的字符
    
    //char* begin();
    //想写一个begin，end，find就结束，问题在于迭代器
};
int KMP(const char *s, int len, const char *p, int plen);//利用KMP算法匹配
void get_next(int *next, const char *T, int len);