#include <iostream>
#include <string>

int main()
{
	std::string str("test string");
	std::cout<<"the size of str is "<< str.size() << "bytes.\n";
	std::cout<<"the size of str is "<< str.length() << "bytes.\n";
	std::cout<<"the size of str is "<< str.capacity() << "bytes.\n";//返回在重新分配内存之前，string所能包含的最大字数
	std::cout<<"the size of str is "<< str.max_size() << "bytes.\n";//返回一个string最多能包含的字符数
	return 0;
}

