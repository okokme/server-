#include <iostream>

using namespace std;
using std::cin;
{

    int main(int argc, char const *argv[])
    {
        int i;
        cin >> i;
        //count << i; //没有对应的using声明 ，必须使用完整的名字
        std::count << i;
        return 0;
    }
    

}