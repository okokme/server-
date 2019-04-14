// 7-2 验证手机号码（C++ Java） （10 分)
// 某系统在新用户注册时必须输入手机号，为了提高系统效率，防止输错手机号，需要对手机号进行验证。 
//验证规则为： （1）长度为11位 （2）由数字0~9组成 （3）必须是1开头 以上3个条件同时满足，则验证通过，否则为不通过。
// 输入格式:
// 在一行中一个字符串，长度不超过50个字符。例如： 13802988920
// 输出格式:
// 如果验证通过则输出Yes，否则输出No。
// 输入样例:
// 13812345678
// 输出样例:
// Yes

// #include <iostream>
// #include <string>
// using namespace std;

// int main(int argc, char const *argv[])
// {
//     string phone;
//     cin>>phone;
//     int i;
//     if((phone.length() == 11) && (phone[0] == '1') )
//     {
//         for(string::iterator it = phone.begin(); it!=phone.end(); it++)
//         {
//             for(i=0; i<=9; i++)
//             {
//                 if(*it == i)
//                     continue;
//                 else
//                 {
//                      printf("No");
//                      break;
//                 }      
//             }
//         }
//         if(i == 9)
//             printf("Yes");

//     }
//     else
//         printf("No");
//     return 0;
// }

#include<iostream>
#include<string>
using namespace std;

int main()
{
	string s;
	getline(cin,s);
	int f=0;
	for(int i=0;i!=s.length();i++)
	{
		if(!isdigit(s[i]))
		{
			f=1;
			break;
		}
	}
	if(s.length()==11 && s.substr(0,1)=="1" && f==0)
		cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}

// 7-1 分离目录路径和文件名 （10 分)
// 输入文件目录路径和文件名，要求分离成目录路径和文件名分别输出

// 输入格式:
// 例如：输入

// c:\windows\winhelp.exe

// 输出格式:
// c:\windows （目录路径）

// winhelp.exe （文件名）

// 输入样例:
// /usr/bin/man
// 输出样例:
// /usr/bin
// man
#include <iostream>
#include<string>
using namespace std;


void filename(const string & str)
{
  int found=str.find_last_of("/\\");
	cout<<str.substr(0,found)<<endl;
	cout<<str.substr(found+1)<<endl;
}
int main()
{
	string str1;
	getline(cin,str1);
	filename(str1);
	return 0;
}
