#include "MyString.h"

//没有参数传进来，做一个空串
MyString::MyString()
{
    m_len = 0;
    m_p = new char[m_len+1];
    strcpy(m_p,"");
}
//字符串和空指针传进来
MyString::MyString(const char *p)
{
    if(p == NULL)
    {
        m_len = 0;
        m_p = new char[m_len+1];
        strcpy(m_p,"");
    }
    else
    {
        m_len = strlen(p);
        m_p = new char[m_len+1];
        strcpy(m_p,p); 
    }
}
//拷贝构造函数
//如MyString s3 = s2
//根据s2分配内存，把数据拷贝到s2中
MyString::MyString(const MyString& s)
{
    m_len = s.m_len;
    m_p = new char[m_len+1];
    strcpy(m_p, s.m_p);
}
MyString::~MyString()
{
    if(m_p != NULL)
    {
        delete [] m_p;
        m_p = NULL;
        m_len = 0;
    }
}
//重载等号操作符
//    s4 = "s222222";
//s4已经分配内存空间了，应该先把旧的空间释放掉
MyString& MyString::operator=(const char *p)
{
    //1把旧的内存释放掉
    if(m_p != NULL)
    {
        delete [] m_p;
        m_len = 0;
    }
    //2根据p分配内存
    if(p == NULL)
    {
        m_len = 0;
        m_p = new char[m_len+1];
        strcpy(m_p,"");
    }
    else
    {
        m_len = strlen(p);
        m_p = new char[m_len+1];
        strcpy(m_p, p);
    }
    return *this;
}
MyString& MyString::operator=(const MyString &s)
{
    if(m_p != NULL)
    {
        m_len = 0;
        delete [] m_p;
    }
    //2根据s分配内存 s至少是个空串，所以不用做是否为NULL处理
    m_len = s.m_len;
    m_p = new char[m_len+1];
    strcpy(m_p,s.m_p);
    return *this;
}
//返回一个元素，所以是char的引用
//s4[0]
char& MyString::operator[](int index)
{
    return m_p[index];
}
ostream& operator<<(ostream &out, const MyString &s)
{
    out<<s.m_p;
    return out;
}
//if (s2 == "s222222")
bool MyString::operator==(const char*p)
{
    if(p == NULL)
    {
        if(m_len == 0)
        {
            return true;
        }
        else
        {
            return false;   
        }
    }
    else
    {
        if(m_len == strlen(p))
        {
            return !strcmp(m_p,p);
        }
        else
        {
            return false;
        }
    }
}
bool MyString::operator==(const MyString& s)
{
    return true;
}
bool MyString::operator!=(const char*p)
{
    return !(*this == p);
}
bool MyString::operator!=(const MyString& s)
{
    return true;
}
