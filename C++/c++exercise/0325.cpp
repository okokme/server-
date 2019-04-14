// // 6-1 对象指针与对象数组（拉丁舞） （7 分)
// // 对象指针与对象数组（拉丁舞）
// // 怡山小学毕业文艺晚会上，拉丁舞是最受欢迎的节目。不过，每年为了排练这个节目，舞蹈组都会出现一些纠纷。有些同学特别受欢迎，有些却少人问津，因此安排舞伴成为舞蹈组陈老师最头疼的问题。
// // 为了解决这一问题，今年陈老师决定让按先男生后女生，先低号后高号的顺序，
// //每个人先报上自己期待的舞伴，每人报两位，先报最期待的舞伴。接下来按先男生后女生，先低号后高号的顺序，
// //依次按以下规则匹配舞伴：
// // （１）每个人均按志愿顺序从前到后确定舞伴。如果第一志愿匹配不成功，则考虑第二志愿。
// // （２）如果Ａ的当前志愿为Ｂ，则如果Ｂ未匹配舞伴，且有以下情形之一者，Ａ和Ｂ匹配成功：
// // 2a) B的期待名单中Ａ。
// // 2b) Ｂ的期待名单中没有Ａ，但Ｂ期待的两位舞伴均已匹配成功，所以Ｂ只能与Ａ凑合。
// // 输入时先输入男生数m, 接下来m行，第一项为学生的姓名，后两项为期待舞伴的编号，编号从０开始，最大为女生数减１。
// // 接下来输入女生数f，接下来f行，第一项为学生的姓名，后两项为期待舞伴的编号，编号从0开始，最大为男生数减１。
// // 输出时按男生的编号顺序输出　　姓名:舞伴姓名
// // 注意两个姓名间有冒号隔开
// // 函数接口定义：
// // Student的两个成员函数：裁判测试程序样例：
// void printPair();
// void addPair();	
// // 裁判测试程序样例：
// #include <iostream>
// #include <string>
// using namespace std;
// const int K=2;
// const int N=20;
// class Student{
//   string name;
//   Student *welcome[K];
//   Student *pair;
//   public:
//       void init(string &name, Student *a, Student *b) {
//         this->name=name; 
//         welcome[0]=a;
//         welcome[1]=b;
//         pair=NULL;
//       }
//      void printPair();
//      void addPair();		
//  };

// /* 请在这里填写答案 */
// void Student::addPair()
// {
// 	if(pair == NULL)
// 	{
// 		if(welcome[0]->pair==NULL && (welcome[0]->welcome[0]->name == name || welcome[0]->welcome[1]->name == name))
// 		{
// 			pair=new Student;
// 			pair->name=welcome[0]->name;
// 			welcome[0]->pair=new Student;
// 			welcome[0]->pair->name=name;
// 		}
// 		else if(welcome[0]->pair==NULL && welcome[0]->welcome[0]->pair != NULL && welcome[0]->welcome[1]->pair != NULL)
// 		{
// 			pair=new Student;
// 			pair->name=welcome[0]->name;
// 			welcome[0]->pair=new Student;
// 			welcome[0]->pair->name=name;
// 		}
// 		else if(welcome[1]->pair==NULL && (welcome[1]->welcome[0]->name == name || welcome[1]->welcome[1]->name == name))
// 		{
// 			pair=new Student;
// 			pair->name=welcome[1]->name;
// 			welcome[1]->pair=new Student;
// 			welcome[1]->pair->name=name;
// 		}
// 		else if(welcome[1]->pair==NULL && welcome[1]->welcome[0]->pair != NULL && welcome[1]->welcome[1]->pair != NULL)
// 		{
// 			pair=new Student;
// 			pair->name=welcome[1]->name;
// 			welcome[1]->pair=new Student;
// 			welcome[1]->pair->name=name;
// 		}
// 	}
// }

// void Student::printPair()
// {
// 	if(this->pair)
// 		cout<<this->name<<":"<<this->pair->name<<endl;
// }

// int main(){
//     Student male[N], female[N];
//     int m, f, i, j, a, b;
//     string name;
//     cin>>m;
//     for(i=0;i<m;i++){
//       cin>>name>>a>>b;
//       male[i].init(name, &female[a], &female[b]);
//     }
//     cin>>f;
//     for(i=0;i<f;i++){
//       cin>>name>>a>>b;
//       female[i].init(name, &male[a], &male[b]);
//     }
//     for(i=0;i<m;i++) male[i].addPair();
//     for(i=0;i<f;i++) female[i].addPair();
//     for(i=0;i<m;i++) male[i].printPair();
//     return 0;
// }
// // 输入样例：
// // 5
// // M0 3 1
// // M1 1 3
// // M2 1 4
// // M3 3 1
// // M4 0 3
// // 5
// // F0 0 2
// // F1 2 0
// // F2 2 1
// // F3 2 4
// // F4 3 2
// // 输出样例：
// // M0:F1
// // M2:F4
// // M4:F0
// // 说明：匹配过程如下：
// // （１）M0先选择F3, 但F3并未期待M0；接下来M0选择F1, F1也期待M0，故匹配成功。
// // （２）Ｍ１选择F1, 但F1已匹配，故,不成功；Ｍ１选择Ｆ３，但Ｆ３未期待M1，仍然不成功。
// // （３）Ｍ２选择Ｆ１，Ｆ１已匹配；Ｍ２选择Ｆ４，　Ｆ４未匹配且也期待Ｍ２，故匹配成功。
// // （４）Ｍ３选择Ｆ３，但Ｆ３未期待他，不成功；Ｍ３选择Ｆ１，Ｆ１已匹配，不成功。
// // （５）Ｍ４选择Ｆ０，　Ｆ０不期待Ｍ４，但是Ｆ０期待的Ｍ０和Ｍ２已分配，所以凑合，匹配成功。
// // （６）Ｆ０已匹配，　Ｆ１已匹配。
// // （７）Ｆ２选择Ｍ２，　Ｍ２已匹配，不成功；　Ｆ２选择Ｍ１，　Ｍ１未匹配，但期待表中没有Ｆ２，且Ｆ３也未分配，故不成功。
// // （８）Ｆ３选择Ｍ２，　Ｍ２已匹配，不成功；Ｆ３选择Ｍ４，　Ｍ４已匹配，不成功。
// // （９）Ｆ４已匹配。


// 6-2 类的声明和成员函数的实现--this指针 （10 分)
// 本题要求声明和实现一个Car类，包括实现其成员函数。
// 要求如下：

// 类和函数接口定义：
// 1. 声明一个Car类;
// 2. 三个public成员函数:
// (1) disp_welcomemsg()，无返回类型;
// (2) get_wheels()，返回一个Car类的数据成员m_nWheels的值；
// (3) set_wheels(int)，用指定的形参初始化数据成员m_nWheels的值；
// 3. 一个私有数据成员m_nWheels，整数类型，代表汽车的车轮数量。

// 其中，成员函数disp_welcomemsg()显示一条欢迎信息“Welcome to the car world!”。 成员函数get_wheels()返回Car类的私有数据成员m_nWheels。 成员函数set_wheels(int)用指定的形参初始化数据成员m_nWheels。

// 裁判测试程序样例：
// #include <iostream>
// using namespace std;
// class Car
// {
// private:
//     int m_nWheels;
// public:
//     void disp_welcomemsg()//显示欢迎信息
//     {
//         cout<<"Welcome to the car world!"<<endl;
//     }
//     int get_wheels()
//     {
//         return this->m_nWheels;
//     }
//     void set_wheels(int n)
//     {
//         this->m_nWheels = n;
//     }
// };
// /* 请在这里填写答案 */

// int main()
// {
//     int n;
//     cin >> n;
//     Car myfstcar, myseccar;    //定义类对象
//     myfstcar.disp_welcomemsg();//访问成员函数，显示欢迎信息
//     myfstcar.set_wheels(n);    //访问成员函数，设置车轮数量
//     myseccar.set_wheels(n+4);  //访问成员函数，设置车轮数量
//     //访问成员函数，显示车轮数量
//     cout << "my first car wheels num = " << myfstcar.get_wheels() << endl;
//     cout << "my second car wheels num = " << myseccar.get_wheels() << endl;

//     return 0;
// }

// 输入样例：
// 4
// 输出样例：
// Welcome to the car world!
// my first car wheels num = 4
// my second car wheels num = 8



#include <iostream>
#include <string>
using namespace std;
// class Screen
// {
// public:
// //根据对象是否是const重载了display函数
// //当函数返回引用类型时，没有复制返回值，相反，返回的是对象本身
// //如果直接返回一个对象而不是引用的话，返回值是*this的副本，而不能改变值
//     Screen &display(std::ostream &os)
//     {
//         do_display(os); return *this;
//     }
//     const Screen &display(std::ostream &os) const
//     {
//         do_display(os); return *this;        
//     } 
// private:
//     void do_display(std::ostream &os) const{cout<<"hello";}// const {os << contents;}
// };

// int main(int argc, char const *argv[])
// {
//     cout<<"hello";
//     return 0;
// }
// 6-1 定义有静态成员的C++学生类Student（10分） （10 分)
// 本程序中学生Student类中有学号 number，姓名 name，成绩 score 等数据成员，
//另外有静态变量：学生对象个数 count 和总分sum。静态成员函数average( )用来计算学生的平均分。

// Student类构造函数的原型如下：

// class Student{
// private:
//     int number;
//     String name;
//     float score;
//     static int count;
//     static float sum;
// public:
//     Student(int number1, String name1, float score1);
//     ~Student();
//     void print();
//     void average();
// };
// Student(int number1, String name1, float score1)
// {

// }

// Student::~Student()
// {
//     delete []name;
//     count--;
// }
// void Student::print()
// {
//     cout<<"number: "<<number<<" name: "<<name<<" score: "<<score<<" count: "<<count<<'\n';
// }

// int Student::count = 0;
// float Student::sum = 0;
// int main( )
// { 
// //	Student::init( );
// 	Student stu1(1,"Bill",87); 
// 	stu1.print( );

// 	Student stu2(2,"Adam",91);
// 	stu2.print( );

// 	Student stu3(3,"David",96);
// 	stu3.print( );

// 	Student::average( ); //静态成员函数的调用	
	
// 	return 0;
// }

// #include<iostream>
// #include<cstring>
// using namespace std;
// class Student{
// private:
// 	int number;
// 	char *name;
// 	float score;
// 	static int count;
// 	static float sum;
// public:static int average();
// 	Student(int number1,char *name1,float score1); //构造函数的声明
// 	~Student( ); //析构函数的声明
// 	void modify(float score1)
// 	{ score=score1;  }
// 	void print();
// };

// Student::Student (int number1,char *name1,float score1)
// {
// 	number=number1;
// 	name=new char[strlen(name1)+1]; //申请动态内存单元
// 	strcpy(name,name1);
// 	score=score1;
// 	count++;
// 	sum=sum+score;
// }
// //析构函数的定义
// Student::~Student( )
// { 
// 	delete [ ] name;  //释放动态内存单元
// 	count--;
// }  
// void Student::print( )
// {
// 	cout<<"number: "<<number<<" name: "<<name
// 		<<" score: "<<score<<" count: "<<count<<'\n';
// }
// int Student::average()

// {
// 	cout<<"sum is "<<sum<<endl<<"count is "<<count<<endl<<"average is "<<sum/count;
// 	return 1;
// }
// int Student::count=0;
// float Student::sum =0;


// 输出样例：
// 在这里给出相应的输出。例如：

// number: 1 name: Bill score: 87 count: 1
// number: 2 name: Adam score: 91 count: 2
// number: 3 name: David score: 96 count: 3
// sum is 274
// count is 3
// average is 91.3333

// 7-1 求两点之间距离 （10 分)
// 定义一个Point类，有两个数据成员：x和y, 分别代表x坐标和y坐标，并有若干成员函数。 定义一个函数Distance(), 用于求两点之间的距离。

// 输入格式:
// 输入有两行： 第一行是第一个点的x坐标和y坐标； 第二行是第二个点的x坐标和y坐标。

// 输出格式:
// 输出两个点之间的距离，保留两位小数。

// 输入样例:
// 0 9 3 -4

// 输出样例:
// 13.34
// 6-2 2017final友元函数之全班同学的平均绩点 （10 分)
// 一个学生类，有三个私有成员：名字name、课程学分指针score、课程成绩指针grade。定义一个友元函数，求全班同学的平均绩点。单门课程的学分绩点=学分*绩点=学分*(成绩/10-5) ; 全班同学的平均绩点是 所有同学的全部课程的学分绩点之和/所有同学学分数之和。单个同学的课程数不超过100门。全班同学人数不超过100名。
// #include<iostream>  
// #include<cmath>  
// #include<stdio.h>
// using namespace std;  
  
// class Point{  
// private:  
//     double x,y;  
// public:  
//     Point(double x,double y)  
//     {  
//         this->x = x;  
//         this->y = y;  
//     }  
//     double Getx()  
//     {  
//         return x;  
//     }  
//     double Gety()  
//     {  
//         return y;  
//     }  
      
//     double Distance(const Point &p)  //定义拷贝构造函数  
//     {  
//         x -= p.x;  
//         y -= p.y;  
//         return sqrt(x*x+y*y);  
//     }  
//     void ShowPoint()  
//     {  
//         cout << "<" << Getx() << "," << Gety() << ">" << endl;  
//     }  
// };  
  
// int main()  
// {  
//     double x1,y1,x2,y2;  
//     double x;

//     cin >> x1 >> y1 >> x2 >> y2;  
//     Point P1(x1,y1);  
//     Point P2(x2,y2);  

//       x=P1.Distance(P2);
//       cout.precision(2);
//       cout.setf(ios::fixed);
//     cout << x << endl;  
    
//     return 0;  
// }
// 输入说明：

// 输入若干行。

// 每行一个学生的信息：第一个输入是学生的名字，第二个输入是第一门课程的学分，
//第三个输入是第一门课程的成绩，第四个输入是第二门课程的学分，
//第五个输入是第二门课程的成绩，以此类推，最后以-1表示该行输入结束。每个学生的课程数不超过100门。

// 最后以 no 表示输入结束。

// 输出一行，即该全班同学的平均绩点。

// 函数接口定义：
// 这是求全部同学平均绩点的友元函数的声明：
// friend double averagegrade(student *stu, int count)
// 其中 *stu 和 count 都是用户传入的参数。 *stu 是传入的学生对象数组的首指针，count是全班学生数量。

// 裁判测试程序样例：

#include<iostream>
#include<string>
using namespace std;
class student{
   private:
      double *grade;
      double *score;
      string name;
public:
      student( )
     {
      grade=NULL;
      score=NULL;
      }
      student(string n, double *g, double *s)
      {
            name=n;
            grade=g;
            score=s;
       }
     friend double averagegrade(student *stu, int count);
};
/* 请在这里填写答案 */
    double averagegrade(student *stu, int count)
    {
        double sum,grade_sum;//
        
        for(i=0; i<count; i++)
            if(stu[i]->grade != NULL)
            {
                grade_sum = 0;
                stu[i]->grade[]
            }
    }


int main()
{
   student stu[100];
   double s[100][100], g[100][100];
   int count=0;
   string n;
   for(int i=0;i<100;i++)
   {
         cin>>n;
         if(n=="no") break;
         count++;
         for(int j=0;j<100;j++)
        {
            cin>>s[i][j];//学分
            if(s[i][j]==-1) break;
            cin>>g[i][j];//成绩
        }
       stu[i]=student(n, g[i], s[i]);
   }
   cout<<averagegrade(stu, count);
   return 0;
}

// 输入样例：
// bob 3 90 2 68.5 2.5 50 -1
// andy 3 80 2 77 -1
// no
// 输出样例：
// 2.408