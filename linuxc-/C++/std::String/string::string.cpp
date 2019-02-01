#include <iostream>
#include <string>

int main()
{
	std::string s0("inital string"); //根据已有字符串构建新的string实例
	std::string s1; //构造一个默认为空的string
	std::string s2(s0); //通过复制一个string来构建一个新的string
	std::string s3(8,3); //通过复制一个string的一部分来构造一个新的string。8为起始位置，3为偏移
	std::string s4("A character sequence"); //与s0构造方式相同
	std::string s5("Another character sequence", 12); //
	std::string s6a(10,'x'); //指定string长度，与一个元素，默认重复该元素创建string
	std::string s6b(10,42); //通过ASCALL码来代替sd6a中的指定 //42 is the ASCALLLL code for '*'
	std::string s7(s0.begin(), s0.begin()+7); //通过迭代器来指定复制s0的一部分，来创建s7

	std::cout <<"s1:"<<s1<<"\ns2:"<<s2<<"\ns3:"<<s3;
	std::cout <<"\ns4:"<<s4<<"\ns5:"<<s5<<"\ns6a:"<<s6a;
	std::cout <<"\ns6b:"<<s6b<<"\ns7:"<<s7<<'\n';
	return 0;
	
}
