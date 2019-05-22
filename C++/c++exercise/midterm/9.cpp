#include <iostream>
using namespace std;
template <typename T> //记着这个模板类的定义
void Swap(T &a, T &b)
{
    T i = a;
    a = b;
    b = i;
}
int main(int argc, char const *argv[])
{
     int i,j;
     char m,n;
     cin>>i>>j;
     cin>>m>>n;
     Swap(i,j);
     Swap(m,n);
     cout<<i<<' '<<j<<endl;
     cout<<m <<' '<<n<<endl;
     
     return 0;
    return 0;
}

#include<iostream>
#include<algorithm>
using namespace std;
//你提交的代码将被嵌入到这里
template < typename T >
void Mysort(T a[], int i)
{
    sort(a,a+i); //记着sort的用法，括号内填的是开始到终点
}
int main()
{
    int m,n,a[20],i,j;
    float b[20];
    cin>>m;         
    for(i=0;i<m;i++)
        cin>>a[i];
    cin>>n;
    for(j=0;j<n;j++)
        cin>>b[j];
    Mysort(a,m); 
    Mysort(b,n);
    for(i=0;i<m;i++)
        cout<<a[i]<<' ';
    cout<<endl;
    for(j=0;j<n;j++)
        cout<<b[j]<<' ';
    cout<<endl;   
    return 0;   
}

#include <iostream>
#include <string>
using namespace std;
// 你提交的代码将嵌入到这里
const int SIZE = 100; 
template <typename T>  //注意
class Queue{
private:
    T q[SIZE];
    int rear;
    int front;
public:
    Queue() { front = rear = 0;}
    T get() {
        if(front == rear)
            return 0;
        front++;
        return q[front];
    }
    void put(T i ) {
        if(front == SIZE)
            exit(0);
        rear++;
        q[rear] = i; 

    }
};
int main()
{
  Queue<int> a; // 创建一个整数队列
  int m,n;
  cin>>m>>n; 
  a.put(m);
  a.put(n);
  cout << a.get() << " ";
  cout << a.get() << endl;

  Queue<double> d; // 创建一个双精度浮点数队列
  double x,y;
  cin>>x>>y;
  d.put(x);
  d.put(y);
  cout << d.get() << " ";
  cout << d.get() << endl;

  Queue<string> qs;// 创建一个字符串队列
  string s1,s2,s3;
  cin>>s1>>s2>>s3;
  qs.put(s1);
  qs.put(s2);
  qs.put(s3);
  cout <<	qs.get() << " ";
  cout <<	qs.get() << " ";
  cout << qs.get() << endl;

  return 0;
}

#include <iostream>
#include <string>
using namespace std;
//你提交的代码将被嵌入到这里
template <typename T>
T Max(T a, T b)
{
    return (a > b ? a : b);
}
 int main( )
{
  int m,n;
  char c,d;
  string s1,s2;
  cin>>m>>n;
  cin>>c>>d;
  cin>>s1>>s2;
  cout<<Max(m,n)<<endl;
  cout<<Max(c,d)<<endl;
  cout<<Max(s1,s2)<<endl;
    return 0 ;
}
