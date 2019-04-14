// // 6-1 写出派生类构造方法（C++） （5 分)
// // 裁判测试程序样例中展示的是一段定义基类People、派生类Student以及测试两个类的相关C++代码，其中缺失了部分代码，请补充完整，以保证测试程序正常运行。

// // 函数接口定义：
// // 提示：
// // 观察类的定义和main方法中的测试代码，补全缺失的代码。
// // 裁判测试程序样例：
// // 注意：真正的测试程序中使用的数据可能与样例测试程序中不同，但仅按照样例中的格式调用相关函数。

// #include <iostream>
// using namespace std;
// class People{
// private:
//     string id;
//     string name;
// public:
//     People(string id, string name){
//         this->id = id;
//         this->name = name;
//     }
//     string getId(){
//         return this->id;
//     }
//     string getName(){
//         return name;
//     }
// };
// class Student : public People{
// private:
//     string sid;
//     int score;
// public:
//     Student(string id, string name, string sid, int score):People(id, name),sid(sid),score(score){
		
// 		/** 你提交的代码将被嵌在这里（替换此行） **/
		
//     }
//     friend ostream& operator <<(ostream &o, Student &s);
// };
// ostream& operator <<(ostream &o, Student &s){
//     o << "(Name:" << s.getName() << "; id:"
//       << s.getId() << "; sid:" << s.sid
//       << "; score:" << s.score << ")";
//     return o;
// }
// int main(){
//     Student zs("370202X", "Zhang San", "1052102", 96);
//     cout << zs  << endl;
//     return 0;
//  }
// // 输入样例：
// // （无）
// // 输出样例：
// // (Name:Zhang San; id:370202X; sid:1052102; score:96)


// // 7-1 日程安排（多重继承+重载） （12 分)
// // 已有一个日期类Date，包括三个protected成员数据

// // int year;

// // int month;

// // int day;

// // 另有一个时间类Time，包括三个protected成员数据

// // int hour;

// // int minute;

// // int second;

// // //现需根据输入的日程的日期时间，安排前后顺序，为此以Date类和Time类为基类，建立一个日程类Schedule，包括以下新增成员：

// // int ID；//日程的ID

// // bool operator < (const Schedule & s2);//判断当前日程时间是否早于s2

// // // 生成以上类，并编写主函数，根据输入的各项日程信息，建立日程对象，找出需要最早安排的日程，并输出该日程对象的信息。
// // // 输入格式： 测试输入包含若干日程，每个日程占一行（日程编号ID 日程日期（**//）日程时间（::））。当读入0时输入结束，相应的结果不要输出。
// // // 输入样例：

// // 1 2014/06/27 08:00:01

// // 2 2014/06/28 08:00:01

// // 0

// // 输出样例：

// // The urgent schedule is No.1: 2014/6/27 8:0:1

// #include <iostream>
// #include <cstdlib>
// #include <cstdio>
// using namespace std;

// class Date {
// protected:
//     int year;
//     int month;
//     int day;
// public:
//     Date(int _y, int _m, int _d):year(_y), month(_m), day(_d){}
// };

// class Time {
// protected:
//     int hour;
//     int minute;
//     int second;
// public:
//     Time(int _h, int _m, int _s):hour(_h), minute(_m), second(_s){}
// };

// class Schedule:public Date, public Time {
// private:
//     int ID;
// public:
//     Schedule():Date(0,0,0), Time(0,0,0), ID(0){}
//     Schedule(int _id, int _year, int _month, int _day, int _hour, int _minute, int _second):Date(_year, _month, _day), Time(_hour, _minute, _second), ID(_id){}
//     bool operator < (const Schedule &s) {
//         char timeArr1[15], timeArr2[15];
//         sprintf(timeArr1, "%04d%02d%02d%02d%02d%02d", year, month, day, hour, minute, second);
//         sprintf(timeArr2, "%04d%02d%02d%02d%02d%02d", s.year, s.month, s.day, s.hour, s.minute, s.second);
//         return atof(timeArr1)<atof(timeArr2);
//     }
//     void show() {
//         cout << "The urgent schedule is No."<<ID<<": "<<year<<"/"<<month<<"/"<<day<<" "<<hour<<":"<<minute<<":"<<second<<endl;
//     }
// };

// int main() {
//     int id, rows=0;
//     int y,m,d,h,i,s;
//     Schedule min;
//     while (cin>>id) {
//         if(id==0) break;
//         scanf("%d/%d/%d %d:%d:%d", &y, &m, &d, &h, &i, &s);
//         Schedule cur(id, y, m, d, h, i, s);
//         if(rows++==0) min = cur;
//         if(cur<min) min = cur;
//     }
//     if(rows!=0) min.show();
    
//     return 0;
// }


#include <iostream>
using namespace std;
class Base
{
public:
    virtual void f(){cout<<"Base::f"<<endl;}
    virtual void g(){cout<<"Base::g"<<endl;}
    virtual void p(){cout<<"Base::p"<<endl;}
};
int main(int argc, char const *argv[])
{
    Base b;
    typedef void(*Fun)(void);
    Fun pFun = NULL;
    cout<<"虚函数地址"<<&b<<endl;
    cout << "虚函数表地址：" << (int*)(&b) << endl;
    cout << "虚函数表 — 第一个函数地址：" << (int*)*(int*)(&b) << endl;
    //先强制转换把&b转换成int*，取得虚函数的地址，然后再次取地址就可以得到第一个虚函数的地址了
    cout << "虚函数表 — 第二个函数地址：" << ((int*)*(int*)(&b)+1) << endl;
    cout << "虚函数表 — 第三个函数地址：" << ((int*)*(int*)(&b)+2) << endl;
    
    
    (Fun)*((int*)*(int*)(&b)+0);  // Base::f()
    (Fun)*((int*)*(int*)(&b)+1);  // Base::g()
    (Fun)*((int*)*(int*)(&b)+2);  // Base::h()
   
   pFun = (Fun)*((int*)*(int*)(&b));

            pFun();

    return 0;
}
