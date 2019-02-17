#include <iostream>
#include <string.h>
using namespace std;

class MyString
{
    friend ostream& operator<<(ostream &out, const MyString &s);
    
public:
    MyString();
    MyString(const char *p);
    MyString(const MyString& s);
    ~MyString();
private:
    int m_len;
    char *m_p;
public: //重载=操作符
    MyString& operator=(const char *p);
    MyString& operator=(const MyString &s);
    char& operator[] (int index);
    bool operator==(const char*p);
    bool operator==(const MyString& s);
    bool operator!=(const char*p);
    bool operator!=(const MyString& s);
};