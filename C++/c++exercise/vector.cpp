#include <iostream>

void printV(vector<int>& v)
{

}

int main()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    vector<int> v2 = v1;
    vector<int> v3(v1.begin(), v1.begin()+2);//使用迭代器对象初始化
    vector<int> v4(3,-1);
    //通过数组的方式访问vector，vector的遍历 v[1]
    //vector用等号操作符往里写数字时，需要先把内存准备好
    vector<int> v5(10);
    for(int i =0; i<10; i++)
    {
        v[i] = i+1;
    }
    //通过迭代器的方式遍历数组
    for(vector<int>::iterator it=v1.begin(); it != v1.end(); it++ )
    {
        cout<<*it<<endl;
    }
    
    std::cout << "Hello world" << std::endl;
    return 0;
}

