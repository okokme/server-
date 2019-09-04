#include <iostream>

//可以把注释去除，看看有没有惊喜
//void Test(int t)
//{
//	std::cout << "call Test" << std::endl;
//}
void Test( int& t)
{
	std::cout << "call Test ref" << std::endl;
}
void Test(const int& t)
{
	std::cout << "call Test const ref" << std::endl;
}

void Test(int&& t)
{
	std::cout << "call right ref" << std::endl;
}

void Test(const int&& t)
{
	std::cout << "call const right ref" << std::endl;;
}

//C++标准里的转发引用
template<class T>
void std_forward(T&& t)
{
	std::cout << "test dispatch!" << std::endl;
	Test(std::forward<T>(t)); //当使用std::forward时候，t为std::move来的将会为右值
	Test(t); //而不使用std::forward直接用move来的， 会是一个左值
}

int Forward()
{
	//注意：如果非类型精确匹配，则注释的重载可以生效
	//但是要注意右值的函数定义注释，否则仍然会有问题
	//double  a = 1.0;
	//Test(a);
	int a = 0;
	std_forward(a);

	const int b = 20;
	std_forward(b);

	std_forward(std::move(a));

	return 0;
}
int main()
{
    Forward();

}
