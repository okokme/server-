6-1 从shape类派生出一个直角三角形类RTriangle （10 分)
从shape类派生出一个直角三角形类RTriangle类（regular triangle）。两条直角边长作为RTriangle类的私有成员，类中包含参数为直角边的构造方法。

class shape {// 抽象类

public:

 virtual double getArea()=0;// 求面积

 virtual double getPerimeter()=0; // 求周长
};

直角三角形类名：RTriangle
直角三角形类的构造函数原型如下： RTriangle(double a, double b);

其中 a 和 b 都是直角三角形的两条直角边。

裁判测试程序样例：
#include <iostream>
#include <cmath> 
using namespace std;

class shape {// 抽象类
public:
 virtual double getArea()=0;// 求面积
 virtual double getPerimeter()=0; // 求周长
};
//你提交的代码将嵌入到这里

int main()
{
  double a,b;
  cin>>a>>b;
  RTriangle t(a,b);
  cout<<t.getArea()<<endl;
  cout<<t.getPerimeter()<<endl;	
}
输入样例：
在这里填写一组输入
3  4
输出样例：
在这里填写相应的输出
12
12
class RTriangle:public shape
{
	double a,b;
public:
	RTriangle(double a1,double b1) { a=a1; b=b1; }
	double getArea()
	{
		return a*b/2;
	}
	double getPerimeter()
	{
		return sqrt(pow(a,2)+pow(b,2))+a+b;
	}
};

6-2 从shape类派生出一个圆形类Circle （10 分)
请从下列shape类派生出一个圆形类Circle,这个类圆形的半径radius作为私有成员，类中应包含初始化半径的构造函数。圆周率PI取3.1415926。

class shape {

public：

double getArea(){ return -1； };

double getPerimeter(){ return -1 };

}

圆形类名Circle
裁判测试程序样例：
#include <iostream>
using namespace std;

class shape {
public:
  double getArea(){ return -1 };// 求面积
  double getPerimeter(){ return -1  }; // 求周长
};

/* 你提交的代码将被嵌入到这里 */


int main() {
  double r;
  cin>>r;
  Circle c(r);
  cout<<c.getArea()<<endl;
  cout<<c.getPerimeter()<<endl;
  return 0;
}
/* 请在这里填写答案 */
输入样例：
在这里填写一组输入
2.78
输出样例：
在这里填写相应的输出
24.2795
17.4673
#include<cmath>
const double PI=3.1415926;
class Circle:public shape
{
	double radius;
public:
	Circle(double a) { radius=a; }
	double getArea()
	{
		return PI*pow(radius,2);
	}
	double getPerimeter()
	{
		return 2*PI*radius;
	}
};


6-3 计算圆柱体的表面积（函数名隐藏） （6 分)
Cylinder类是Circle类的派生类，在下面的程序中计算并输出了圆柱体的表面积。请阅读理解下面的程序。将下面的Cylinder类补充完整后提交。

Cylinder类的定义：
class Cylinder :public Circle{
         double height;             
public:
......
};
你提交的Cylinder类的定义将嵌入到下面的程序中：
#include <iostream>
using namespace std;
const double PI=3.1415926;
class Circle{
protected:
   double radius;
public: 
   Circle(double r){
      radius=r;
   }
   double getArea(){
      return PI*radius*radius;
   }
};
// 你提交的代码将嵌入在这里

int main() 
{
   double r,h;
   cin>>r>>h;
   Cylinder Cy1(r,h) ;
   cout<<Cy1.getArea()<<endl;
   return 0;
}
输入样例：
3.5 4.2
输出样例：
106.369
class Cylinder :public Circle{
         double height;             
public:
	Cylinder(double r1,double h1):Circle(radius) { radius=r1; height=h1; }
	double getArea()
	{
		return PI*2*radius*height+2*PI*radius*radius;
	}
};


6-4 狗的继承 （10 分)
完成两个类，一个类Animal，表示动物类，有一个成员表示年龄。一个类Dog，继承自Animal，有一个新的数据成员表示颜色，合理设计这两个类，使得测试程序可以运行并得到正确的结果。

函数接口定义：
按照要求实现类

裁判测试程序样例：
/* 请在这里填写答案 */

int main(){
	Animal ani(5);
	cout<<"age of ani:"<<ani.getAge()<<endl;
	Dog dog(5,"black");
	cout<<"infor of dog:"<<endl;
	dog.showInfor();
}


输入样例：
无

输出样例：
age of ani:5
infor of dog:
age:5
color:black
#include<string>
using namespace std;

class Animal
{
protected:
	int age;
public:
	Animal(int a) { age=a; }
	int getAge() { return age; }
};

class Dog:public Animal
{
	string color;
public:
	Dog(int a,string str):Animal(a)
	{
		age=a;
		color =str;
	}
	void showInfor()
	{
		cout<<"age:"<<age<<endl<<"color:"<<color<<endl;
	}
};
