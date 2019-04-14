// 7-1 字符串替换 （10 分)
// 将文本文件中指定的字符串替换成新字符串。
// 由于目前的OJ系统暂时不能支持用户读入文件，我们编写程序从键盘输入文件中的内容，当输入的一行为end时，表示结束。
// end后面有两个字符串，要求用第二个字符串替换文本中所有的第一个字符串。

// 输入格式:
// Xi’an Institute of Posts and Telecommunications 
// is co-designed and implemented by the People’s Government of Shaanxi Province and 
// the Ministry of Industry and Information Technology. The Institute is located in Xi’an, 
// a historic city in Northwest China, famous for its magnificent ancient culture.

// end （表示结束）

// Institute （第一个字符串，要求用第二个字符串替换）

// University （第二个字符串）

// 输出格式:
// Xi’an University of Posts and Telecommunications 
// is co-designed and implemented by the People’s Government of Shaanxi Province and 
// the Ministry of Industry and Information Technology.The University is located in Xi’an, 
// a historic city in Northwest China, famous for its magnificent ancient culture.

// 输入样例:
// Xi’an Institute of Posts and Telecommunications is co-designed and implemented by the People’s Government of Shaanxi Province and the Ministry of Industry and Information Technology.
// The Institute is located in Xi’an, a historic city in Northwest China, famous for its magnificent ancient culture.
// end
// Institute
// University
// 输出样例:
// Xi’an University of Posts and Telecommunications is co-designed and implemented by the People’s Government of Shaanxi Province and the Ministry of Industry and Information Technology.The University is located in Xi’an, a historic city in Northwest China, famous for its magnificent ancient culture.

// #include <iostream>
// using namespace std;

// int main(int argc, char const *argv[])
// {
//     string a,m,b,c;
//     int found;
//     getline(cin,a); //输入回车结束
//     while(1)
//     {
//         getline(cin, m);
//         int i = m.compare("end");
//         if(i == 0)
//             break;
//         a+='\n';
//         a+= m;
//     }
//     a+='\n';
//     cin>>b;
//     cin>>c;
//     found = a.find(b);
//     while(found != -1)
//     {
//         a.replace(found, b.length(),c);
//         found = a.find(b, found+1);
//     }
//     cout<<a;
//     return 0;
// }
// 7-2 求解给定字符串的前缀 （10 分)
// 求解给定字符串的前缀。
// 输入格式:
// 输入数目不定的多对字符串，每行两个，以空格分开。 例如：
// filename filepat
// Tom Jack
// 输出格式:
// 返回两个字符串的最大前缀，例如：
// The common prefix is file
// No common prefix
// 输入样例:
// filename filepath
// Tom Jack
// 输出样例:
// The common prefix is file
// No common prefix
// #include <iostream>
// #include <string.h>
// using namespace std;
// int main()
// {    
//     char a[100],b[100];
//     int i;    
//     int n,m,t;    
//     n=strlen(a);    
//     m=strlen(b);    
//     if(m>n)
//     {        
//         t=n;        
//         n=m;        
//         m=t;    
//     }    
//     while(scanf("%s",a)!=EOF && scanf("%s",b)!= EOF)
//     {        
//         for(i=0;i<n;i++)
//         {            
//             if(a[i]!=b[i])
//             {                
//                 break;            
//             }        
//         }    
//         if(i==0)        
//         cout<<"No common prefix"<<endl;    
//         else {        
//             cout<<"The common prefix is ";
//                     for(int j=0;j<i;j++)            
//                     cout<<a[j];        
//                     cout<<endl;    
//         }    
                    
//     }
// }
// 7-3 学号解析 （10 分)
// 川师的学号的某些位有特殊的含义，如从2016110101中可以看出该学生为2016级，就读于11系，班级为1班。根据输入的学号，利用程序进行解析，输出对应的信息。
// 输入格式:
// 一个学号
// 输出格式:
// 相关信息
// 输入样例:
// 在这里给出一组输入。例如：
// 2016110101
// 输出样例:
// 在这里给出相应的输出。例如：
// year:2016
// department:11
// class:01
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    string std;
    cin>>std;
    cout<<"year:";
    int i;
    for(i=0; i<4; i++)
        cout<<std[i];
    cout<<'\n';
    cout<<"department:";
    for(i=4; i<6; i++)
        cout<<std[i];
    cout<<'\n';
    cout<<"class:";
    for(i=6; i<8; i++)
        cout<<std[i];    
    cout<<'\n';
            
    return 0;
}

