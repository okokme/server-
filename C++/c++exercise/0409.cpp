6-1 从shape类派生出一个正六边形类RHexagon （10 分)
从下列的抽象类shape类派生出一个正六边形（regular hexagon）RHexagon类。RHexagon类将正六边形的边长作为私有成员，类中包含初始化这个值的构造函数。

class shape {// 抽象类

public:

 virtual double getArea()=0;// 求面积

 virtual double getPerimeter()=0; // 求周长
};

正六边形类名：
RHexagon
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
  double s;
  cin>>s;
  RHexagon p(s);
  cout<<p.getArea()<<endl;
  cout<<p.getPerimeter()<<endl;	
}
