// #include <iostream>
// #include <string>
// using namespace std;

// void filename(const string & str1)
// {
//     int found = str.find_last_of("/\\");
//     cout<<str.substr(0,found)<<endl;
//     cout<<str.substr(found+1)<<endl;
// }

// int main(int argc, char const *argv[])
// {
//     string str1;
//     getline(cin,str1);
//     filename(str1); 
//     return 0;
// }

#include <iostream>
#include <iostream>
using namespace std;
// //验证手机号码，要求：11位，数字0-9组成， 必须是1开头
//isdight()
int main(int argc, char const *argv[])
{
    string s;
   // getline(cin,s); //注意这个操作cin
   cin>>s;
    int f=0;
    for(int i=0; i<s.length(); i++)
    {
        if(!isdigit(s[i]))
        {
            f=1;
            break;
        }
    }
    if((s.length() == 11) && (s[0] == '1') && (f==0))
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;

    return 0;
}

//substr(0,1); //复制子串长度，从指定位置开始并具有指定的长度
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    string s;
    cin>>s;
    cout<<"year:"<<s.substr(0,4)<<endl;
    cout<<"department:"<<s.substr(4,2)<<endl;
    cout<<"class:"<<s.substr(6,2)<<endl;
    return 0;

//求最长相同开头
//注意使用 max substr()
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    string s1,s2;
   while(cin>>s1>>s2)
   {
        int max =0;
    for(int i=0; s1[i] && s2[i]; i++)
    {
        if(s1.substr(0,i) == s2.substr(0,i))
            max = i;
    }
    if(max)
    {
        cout<<"The common prefix is";
        cout<<s1.substr(0,max)<<endl;
    }
    else
    {
        cout<<"No common prefix"<<endl;
    } 
   }
         
    return 0;
}


//替换全文某个字符串 
//注意使用 getline(), str.find() str.replace() s.compare()
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    string str = "";
    string s = "";
    getline(cin,s);
    str += s;
    while(1)
    {
        getline(cin,s); //  读到直到有回车？
        if(s.compare("end") == 0)
            break;
        else{
            str+='\n'+s;
         // str+=s;
            s="";
        }
    }
    string a,b;
    cin>>a>>b;
    while(str.find(a) != -1) {
        str = str.replace(str.find(a),a.length(),b);
    }
    cout<<str<<endl;
    return 0;
}

