//正六边形
// #include <iostream>
// #include <cmath> 
// using namespace std;

// class shape {// 抽象类
// public:
//  virtual double getArea()=0;// 求面积
//  virtual double getPerimeter()=0; // 求周长
// };
// //你提交的代码将嵌入到这里
// class RHexagon : shape {
// private:
//     double length;
// public:
//     RHexagon(double s):length(s) { }
//     double getArea() {
//         double d,e;
//         e = sqrt(3);
//         d = 1.5*e*length*length;
//         return d;
//     }
//     double getPerimeter() {
//         double c;
//         c = length*6;
//         return c;
//     }
// };
// int main()
// {
//   double s;
//   cin>>s;
//   RHexagon p(s);
//   cout<<p.getArea()<<endl;
//   cout<<p.getPerimeter()<<endl;	
// }

// #include <iostream>
// #include <algorithm>
// using namespace std;
// class Shape{
// public:
//     double area ( ){ return -1; }
// };
// //你提交的代码将嵌入到这里。 
// class Circle : Shape {
// private:
//     double r;
// public:
//     Circle(double _r): r(_r) { }
//     double area() {
//         return 3.14*r*r;
//     }
// };
// class Rectangle : Shape {
// private:
//     double height;
//     double weight;
// public:
//     Rectangle(double h, double w) : height(h), weight(w) { }
//     double area() {
//         return height*weight;
//     }
// };
// int main()
// { 
//     double r,h,w;
//     cin>>r>>h>>w;
//     Circle c(r); Rectangle rect(h,w);

//     cout<<"The area of the Circle is "<<c.area( )<<endl;
//     cout<<"The area of the Rectangle is "<<rect.area( )<<endl;

//     return 0;
// }

#include <iostream>
#include <string>
using namespace std;
class Person {
protected:
    string name;
    int age;
public:
    Person();
    Person(string p_name, int p_age);
    void display() { cout<<name<<":"<<age<<endl;}
};
class Student : public Person{
private:
    int ID;
    float cpp_score;
    float cpp_count;
    float cpp_grade;
public:
    Student() { }
    Student(string n, int i, int a, float s, float c ):Person(n,a),ID(i),cpp_score(s),cpp_count(c) {
        cpp_grade = cpp_score * 0.9 + cpp_count * 2;
     }
    void print() { 
        cout<<ID<<" "<<name<<" "<<cpp_grade<<endl;
    }
  
};
int main()
{  int a,i;string n;float p,q;
while(1)
{   cin>>n;
    if(n=="0") return 0;
    else{
    cin>>i;
    cin>>a;
    cin>>p;
    cin>>q;
   Student s(n,i,a,p,q); 
   s.print();
    }
}
 return 0;  
}
