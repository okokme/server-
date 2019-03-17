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
const char* MyString::c_str()
{
    return m_p;
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
istream& operator>>(istream &in, MyString &s)
{
    in>>s.m_p;
    return in;
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
    if(s.m_len == m_len)
    {
        if(s.m_len == 0)
            return true;
        else
            return !strcmp(s.m_p,m_p);
    }
    else
    {
        return false;        
    }

}
bool MyString::operator!=(const char*p)
{
    return !(*this == p);
}
bool MyString::operator!=(const MyString& s)
{
    return !(*this == s);
}
int MyString::size()
{
    return m_len;
}
// 加法为什么不能这么写
// MyString& operator+(const MyString& s1, const MyString& s2)//s3 = s1 + s2;
// {
//     m_len = s1.m_len+s2.m_len;
//     strcpy(m_p, s1.m_p);
//     strcat(m_p, s2.m_p);
//     return *this;
// }

MyString operator+(const MyString& s1, const MyString& s2)//s3 = s1 + s2;
{
    MyString s3;
    s3.m_len = s1.m_len+s2.m_len;
    strcpy(s3.m_p, s1.m_p);
    strcat(s3.m_p, s2.m_p);
    return s3;
}
MyString& MyString::erase(int pos, int len)
{
    assert(pos+len <= m_len); //假设删除到的长度小于等于m_len
    for(int i=pos, j=pos+len; i<=pos+len && j<=m_len; ++i, ++j)
        m_p[i] = m_p[j];
    m_len-=len;
    m_p[m_len] = '\0';
    return *this;
}
int MyString::find(const char *p)
{
   int m = KMP(m_p, m_len, p, strlen(p));//KMP算法
//BF算法
//    if(m_len == 0) return -1;
//     int i=0, j=0;
//     int start = 0;
//     while(i<m_len && j<strlen(p))
//         if(m_p[i] == p[j]) {i++; j++;}
//         else
//         {
//             start++;
//             i=start;
//             j=0;
//         }
//     if(j>=strlen(p)) return start;
//     else return -1;
}
int KMP(const char *s, int len, const char *p, int plen)//利用KMP算法匹配
{
	int *next = new int(plen);
	get_next(next, p, plen);
	int k = -1;
	int i = 0;
	for (; i < len; i++)
	{
 		while (k > -1 && p[k+1]!=s[i])//两串下一个字符不相等，向前回溯（效率高就是在这里，每次匹配失败，k不用直接变为0，从第一个字符开始重新匹配，而是变为最长重复子串的下一个字符，从中间开始匹配即可）。
		{
			k = next[k];
		}
		if(p[k+1] == s[i])//两个串的字符相等，k+1来匹配子串的一个字符
		{
			k++;
		}
		if (k == plen-1)//匹配成功，返回短串在长串的位置。
		{
			return i-plen+1;
		}
	}
	return -1;
}
void get_next(int *next, const char *T, int len)
{
	next[0] = -1;//-1代表没有重复子串
	int k = -1;
	for (int q = 1; q <= len; q++)
	{
		while (k > -1 && T[k+1] != T[q])//下一个元素不相等，把k向前回溯
		{
			k = next[k];
		}
		if (T[k+1] == T[q])//下一个元素相等，所以最长重复子串+1
		{
			k = k+1;
		}
		next[q] = k;//给next数组赋值
	}
}