// // (1) 编写一个 C++程序， 在其中创建一个含有 5 个元素的 Student 类的对象数组， 并
// // 给对象数组成员赋值， 然后输出对象数组。 输出对象数组时分别使用点（ .） 运算符和箭
// // 头（ ->）运算符。
// #include <iostream>
// #include <string.h>
// #include <string>
// using namespace std;
// class Student{
// private:
//     int number;
//     char *name;
//     float score;
// public:
//     Student(int number1, char *name1, float score1);
//     ~Student();
//     void print();

// };
// Student::Student(int number1, char *name1, float score1)
// {
//     number = number1;
//     name = new char[strlen(name1)+1];
//     strcpy(name, name1);
//     score = score1;
// }
// Student::~Student()
// {
//     delete []name;
// }
// void Student::print()
// {
//     cout<<"number:"<<number<<"name:"<<this->name<<"score:"<<score<<endl;
// }

// int main(int argc, char const *argv[])
// {
//     Student a[5]={Student(1,"MingMing",98), Student(2,"LiLi",88), Student(3,"keke",66), Student(4,"baibai",99), Student(5,"heihei",53)};
//     Student *sp;
//     sp = a;
//     for(int i=0; i<5; i++,sp++) 
//         sp->print();
//     for(int i=0; i<5; i++)
//         a[i].print();
//     return 0;

// }

// (2) 编译、 运行并调试下列程序， 观察调用函数 sqr_it(a)的前后对象 a 的值是否发
// 生了变化。请问向函数 sqr_it( )传递对象是采用的是哪种传递方式？
// #include <iostream>
// using namespace std;
// class samp {
// int i;
// public:
// samp(int n) { i = n; }
// void set_i(int n) { i = n; }
// int get_i() { return i; }
// };
// void sqr_it(samp &o)
// {

// o.set_i(o.get_i() * o.get_i()); //10*10
// cout << "Copy of a has i value of " << o.get_i();
// cout << "\n";
// }
// int main()
// { samp a(10); //i = 10
// sqr_it(a);
// cout << "Copy of a has i value of " << a.get_i();
// return 0;
// }

// (3) 下列 Circle 类的定义中包含了静态数据成员和静态成员函数。请在主函数 mani( )
// 中创建 Circle 类的 3 个对象，并调用静态成员函数输出对象的个数。
// #include <iostream>
// using namespace std;
// class Circle
// { 
// public:
//     Circle(float r)
//     { 
//         radius=r;
//         ++count;
//     }
//     ~Circle() 
//     {
//         --count; 
//     }
// static int num() { return count; } //静态成员函数
// private:
//     float radius;
//     static int count; //静态数据成员
// };
// int Circle::count = 0;
// int main(int argc, char const *argv[])
// {
//     Circle c1(3), c2(4), c3(5);
//     cout<<"cout: "<<c1.num()<<endl;
//     return 0;
// }

// (4) 下列程序中使用友元函数计算平面上两点之间的距离，删除程序中的关键字
// friend 看看编译时会产生什么问题？
#include <iostream>
#include <math.h>
using namespace std;
class Point
{
public:
    Point(double xi, double yi) {X=xi; Y=yi; }
    double GetX() {return X;}
    double GetY() {return Y;}
//    friend double Distance( Point& a, Point& b);
    double Distance( Point& a, Point& b);

private:
    double X, Y;
};
double Distance( Point& a, Point& b)
{
    double dx=a.X-b.X;
    double dy=a.Y-b.Y;
    return sqrt(dx*dx+dy*dy);
}
int main()
{
    Point p1(3.0, 5.0), p2(4.0, 6.0);
    double d=Distance(p1, p2);
    cout<<"The distance is "<<d<<endl;
    return 0;
}