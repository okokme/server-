#include <iostream>
using namespace std;

void stand(int t)
{
    cout<<"stand"<<endl;
}
void RightRef(int&& t)
{
    cout<<"non const RightRef function"<<endl;
}
void RightRef(const int&& t)
{
    cout<<"const RightRef function"<<endl;
}
void LeftRef(int& t)
{
    cout<<"non const LeftRef function"<<endl;
}
void LeftRef(const int& t)
{
    cout<<"const LeftRef function"<<endl;
}
int main(void)
{
    int a = 0;
    stand(a);
    RightRef(std::move(a));
}
