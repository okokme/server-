// #include <iostream>
// #include <cstring>
// using namespace std;
// class Student {
// private:
//     int number;
//     string name;
//     float score;
//     static int count;
//     static float sum;

// public:
//     Student(int number1, String name1, float score1):number(number1),name(name1),score(score1) { 
//         count++;
//         sum+=score;
//     }
//     static int average()
//     {
//         	cout<<"sum is "<<sum<<endl<<"count is "<<count<<endl<<"average is "<<sum/count;
//     }
//     void print()
//     {
//         cout<<"number: "<<number<<" name: "<<name<<" score: "<<score<<" count: "<<count<<'\n';

//     }
// };
// int Student::count = 0；
// int Student::sum = 0;

// int main( )
// { 
//  //   Student(int number1, String name1, float score1);
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
// #include<string>
// using namespace std;
// class Car {
// public:
    
//     void disp_welcomemsg(){
//         cout<<"Welcome to the car world!"<<endl;
//     }
//     int get_wheels() {
//         return m_nWheels;
//     }
//     void set_wheels(int m) {
//         m_nWheels = m;
//     }
// private:
//     int m_nWheels; //车轮数

// };

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
