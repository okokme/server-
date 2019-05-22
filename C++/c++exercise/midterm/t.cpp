// #include <iostream>
// using namespace std;
// // 你提交的代码将嵌入到这里
// template <typename T>
// T Min(T *p, int len)
// {
//     T t;
//     for(int i=0; i<len; i++)
//         for(int j=0; j<len-i-1; j++)
//         {
//             if(p[j] <p[j+1])
//             {
//                 t=p[j];
//                 p[j] = p[j+1];
//                 p[j+1] = t;
//             }
//         }
//         return p[0];
// }
// int main( )
// {
//     int n,m,*pn,i=0;
//     cin>>n;
//     pn=new int[n];
//     do{
//         cin>>pn[i];
//         i++;
//     }while(i<n);

//     double *pd;
//     i=0;
//     cin>>m;
//     pd=new double[m];
//     do{
//         cin>>pd[i];
//         i++;
//     }while(i<m);

//     cout<<Min(pn,n)<<endl;
//     cout<<Min(pd,m)<<endl;
//     delete [ ] pn;
//     delete [ ] pd;
//     return 0;
// }

// #include <iostream>
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
//     Circle(double m) : r(m) { }
//     double area ( ){ return r*3.14*r; }

// };
// class Rectangle : Shape {
// private:
//     double w;
//     double h;
// public:
//     Rectangle(double m, double n) : w(m), h(n) { }
//     double area ( ){ return w*h; }

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

// #include<iostream>
// using namespace std;

// /* 请在这里填写答案 */
// class Student {
// private:
//     int id;
//     int score;
//     static int count;
// public:
//     Student(int n, int s) {
//         id = n;
//         score = s;
//         count++;
//     }
//     Student(Student &s)
//     {
//         id = s.id+1;
//         score = s.score;
//         count++;
//     }
//     display()
//     {
//         cout<<id;
//         if(score == 0)
//             cout<<"Fail"<<endl;
//         else
//             cout<<"pass"<<endl;
//     }
// };
// int Student::count = 0;
// int main(){
//     const int size=100;
//     int i, N, no, score;
//     Student *st[size];
//     cin>>N;
//     for(i=0; i<N; i++){
//         cin>>no;
//         if(no>0){
//             cin>>score;
//             st[i]=new Student(no, score);
//         }
//         else
//             st[i]=new Student(*st[i-1]);
//     }
//     cout<<Student::count<<" Students"<<endl;
//     for(i=0;i<N;i++) st[i]->display();
//     for(i=0;i<N;i++) delete st[i];
//     return 0;
// }

// #include <iostream>
// using namespace std;
// const double PI=3.1415926;
// class Circle{
// protected:
//    double radius;
// public: 
//    Circle(double r){
//       radius=r;
//    }
//    double getArea(){
//       return PI*radius*radius;
//    }
// };
// //你提交的代码将嵌入在这里
// class Cylinder : public Circle {
//     double height;
// public:
//     Cylinder(double r, double h):Circle(r), height(h) { 
//         this-> radius = r;
//     }
//     double getArea() {
//         return (PI*radius*radius*2 + radius*2*PI*height);
//     }
// };

// int main() 
// {
//    double r,h;
//    cin>>r>>h;
//    Cylinder Cy1(r,h) ;
//    cout<<Cy1.getArea()<<endl;
//    return 0;
// }
// #include <iostream>
// #include <string>
// using namespace std;

// int main(int argc, char const *argv[])
// {
//     string s1, s2;
//     while(cin>>s1>>s2)
//     {
//         int max;
//         for(int i=0; s1[i] && s2[i]; i++)
//         {
//             if(s1.substr(0,i) == s2.substr(0,i))
//             {
//                 max = i;
//             }
//             else 
//                 break;
//         }
//         if(max!=0)
//             cout<<s1.substr(0,max)<<endl;
//         else
//             cout<<"no"<<endl;
//     }
//     return 0;
// }

// #include<iostream>
// #include<string>
// #include <map>
// using namespace std;

// int main(int argc, char const *argv[])
// {
//     //string s[4];
//     map<string,string> foot;
//     foot.insert(pair<string,string>("Australian","Spain"));
//     foot.insert(pair<string,string>("Holland","Chile"));
//     foot.insert(pair<string,string>("Cameroon","Brazil"));
//     foot.insert(pair<string,string>("Croatia","Mexico"));
//     string name;
//     cin>>name;
//     auto pos = foot.find(name);
//     if(pos != foot.end())
//         cout<<pos->second<<endl;
//     else
//         cout<<"not find"<<endl;
    
//     return 0;
// }

//部分排序
// #include <iostream>
// #include <algorithm>
// using namespace std;

// int main(int argc, char const *argv[])
// {
//     int n,r;
//     cin>>n>>r;
//     int i;
//     int a[n];
//     for(i=0; i<n; i++)
//         cin>>a[i];

//     if(r+r>=n)
//     {
//         for(i=0; i<n; i++)
//         {
//             if(i!=0)
//                 cout<<" ";
//             cout<<a[i];
//         }
//     }
//     else
//     {
//         sort(a+r,a+n-r);
//  //       cout<<"n "<<n<<endl;
//  //       cout<<"r "<<r<<endl;        
//         for(int i=0; i<n; i++)
//         {
//              if(i!=0)
//             cout<<" ";
//         cout<<a[i];
//         }
           
//     }
//     cout<<endl;
//     return 0;
// }

// #include <iostream>
// #include <algorithm>
// using namespace std;

// int main(int argc, char const *argv[])
// {
//     int n, r;
//     cin>>n>>r;
//     int a[n];//这里可以直接int a[n]
//     for(int i=0; i<n; i++)
//         cin>>a[i];
//     if(r+r>=n)
//     { 
//         for(int i=0; i<n; i++)
//         {
//             if(i!=0)    
//                 cout<<" ";
//             cout<<a[i];
//         }
//     }    
//     else
//     {
//         sort(a+r, a+n-r);
//         for(int i=0; i<n; i++)
//         {
//             if(i!=0)    
//                 cout<<" ";
//             cout<<a[i];
//         }
//     }
//     cout<<endl;
//     return 0;
// }

// #include <iostream>
// using namespace std;
// const double PI=3.1415926;
// class Circle{
// protected:
//    double radius;
// public: 
//    Circle(double r){
//       radius=r;
//    }
//    double getArea(){
//       return PI*radius*radius;
//    }
// };
// // 你提交的代码将嵌入在这里
// class Cylinder : public Circle {
// private:
//     double height;
// public:
//     Cylinder(double r, double h):Circle(r),height(h) {
//         this->radius = r;
//     }
//     double getArea() {
//         return (PI*radius*radius*2 + 2*PI*radius*height);
//     }
// };
// int main() 
// {
//    double r,h;
//    cin>>r>>h;
//    Cylinder Cy1(r,h) ;
//    cout<<Cy1.getArea()<<endl;
//    return 0;
// }

#include<iostream>
#include <map>
using namespace std;

// /* 请在这里填写答案 */
// class Student {
// public:
//     static int count;
// private:
//     int id;
//     int score;
    
// public:
//     Student(int i, int s) :id(i), score(s) {
//         count++;
//     }
//     Student(Student &s) {
//         id = s.id+1;
//         score = s.score;
//         count++;
//     }
//     void display() {
//         cout<<id<<" ";
//         if(score == 0)
//             cout<<"Fail"<<endl;
//         else
//             cout<<"Pass"<<endl;
//     }
// };
// int Student::count = 0;
// int main(){
//     const int size=100;
//     int i, N, no, score;
//     Student *st[size];
//     cin>>N;
//     for(i=0; i<N; i++){
//         cin>>no;
//         if(no>0){
//             cin>>score;
//             st[i]=new Student(no, score);
//         }
//         else
//             st[i]=new Student(*st[i-1]);
//     }
//     cout<<Student::count<<" Students"<<endl;
//     for(i=0;i<N;i++) st[i]->display();
//     for(i=0;i<N;i++) delete st[i];
//     return 0;
// }

std::map<char *, int> m;
const int MAX_SIZE = 100;
int main() {
    char str[MAX_SIZE];
    for (int i = 0; i < 10; i++) {
        std::cin >> str;
        m[str] = i;
    }
    std::cout << m.size() << std::endl;
}