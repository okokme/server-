7-1 查找成绩并折算后输出 (10 分)
文件：期中考试成绩.txt中有若干学生的姓名和数学期中考试成绩。 
Smith 67 Anderson 75 Lewis 83 Cook 58 David 96 
请你编写一个简单的查询成绩程序，当从键盘输入一个姓名时查找到他的数学期中考试分数并按照21%折算后输出。
如果没找到则显示Not found. 由于目前的OJ系统暂时不能支持用户读入文件，我们编写程序从键盘输入文件中的姓名和成绩，
当输入的名字为noname时，表示结束。noname后面有一个名字，需要查找其成绩。

输入格式:
Smith 67
Anderson 75
Lewis 83
Cook 58
David 96
noname （表示结束）
Bill
输出格式:
Not found.
输入样例:
Smith  67
Anderson  75
Lewis  83
Cook  58
David  96
noname
Lewis
输出样例:
17.43
#include<iostream>
#include<string>
#include<map>
using namespace::std;

int main(int argc, char const *argv[])
{
    double sorce = 0;
    string name;
    map<string, double> dict;
    while(cin>>name)
    {
        if(name != "noname")
        {
            cin>>sorce;
            dict.insert(pair<string,double>(name,sorce));
        }
        else
            break;
    }
    cin >> name;
    auto pos = dict.find(name);
    if(pos != dict.end())
    {
        printf("%.2lf\n",pos->second*0.21);
    }
    else
        printf("not found\n");
    return 0;
}

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    double sorce;
    string name;
    map<string, double> dirt;
    while (cin>>name)
    {
        if(name != "noname")
        {
            cin>>sorce;
            dirt.insert(pair<string, double>(name, sorce));
        }
        else
            break;
    }
    cin>>name;
    auto pos = dirt.find(name);
    if(pos != dirt.end())
    {
        printf("%.2lf\n",pos->second*0.21);
    }
    else
        printf("not find.\n");
    return 0;
}


#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(int argc, char const *argv[])
{
    string name;
    string number;
   // map<string, string> p1;    
   // map<string, string> p2;        
    map<string,string> phonebook;
    while(cin>>name)
    {
        if(name != "end")
        {
            cin>>number;
            phonebook.insert(pair<string,string>(name, number));
        }
        else
            break;
    }
    while(cin>>name)
    {
        if(name != "end")
        {
            cin>>number;
            phonebook.insert(pair<string,string>(name, number));
        }
        else
            break;
    }
    for(auto item=phonebook.begin(); item!=phonebook.end(); item++)
    {
        cout<<item->first<<" "<<item->second<<endl;
    }
    return 0;
}

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
    string name;
    vector<string> dirt;

    while(cin>>name)
    {
        if(name != "end")
        {
            dirt.push_back(name);
        }
        else
            break;
    } 
    sort(dirt.begin(), dirt.end()); //排序
    for(auto it:dirt) //注意这个it操作
        cout<< it.data()<< " "; //注意这里输出的是 it.data()  在map中输出的是 it->first it->second
    cout << endl;
    return 0;
}

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    string name;
    string phone;
    map<string, string> dirt;
    while(cin >> name)
    {
        if(name != "noname")
        {
            cin >> phone;
            dirt.insert(pair<string, string>(name, phone));
        }
        else
            break;
    }
    cin>> name;
    auto pos = dirt.find(name);  //find操作。用一个指针pos接着。然后检查pos，若不为最后 就输出 相应的first或second 否则输出 Notfind
    if(pos != dirt.end())
        cout << pos->second<<endl;
    else
        cout<<"Not Found"<<endl;
    return 0;
}
