namespace 命名空间

##### c中的命名空间

* 在C语言中只有一个全局作用域
* C语言中所有的全局标识符共享一个作用域
* 标识符之间可能会发生冲突

##### C++命名空间

* 命名空间将全局作用域分成不同的部分
* 不同命名空间的标识符可以同名而不会发生冲突
* 命名空间可以相互嵌套
* 全局作用域也可以叫默认命名空间

##### C++命名空间的定义

namespace name {......}

##### C++命名空间的使用

* 使用整个命名空间 using namespace name;
* 使用命名空间中的变量 using namespace::variable;
* 使用默认命名空间的变量 ::variable;
* 默认情况下可以直接使用默认命名空间中的所有标识符

```c++
#include<iostream>

    //定义命名空间
    namespace NameSpaceA
    {
        int a = 0;
    }
    namespace NameSpaceB
    {
        int a = 1;
        namespace NameSpaceC
        {
            struct Teacher
            {
                char name[10];
                int age;
            };
        }
    }
	namespace NameSpaceD
	{
		struct hehe
		{
			char name[20];
			int age;
		};
	}

    //命名空间的使用
    int main()
    {
    	using namespace NameSpaceA;
	using namespace NameSpaceB;
	using  NameSpaceD::hehe;
	hehe t;
	t.age = 10;
	printf("%d\n",t.age);
   //	using NameSpaeB::NameSpaceC::Teacher;
    	
//        printf("a = %d\n",a);
        printf("a = %d\n",NameSpaceA::a);
//	NameSpaceB::NameSpaceC::Teacher;
//        Teacher t1 = ("abc",3);
//        printf("t1.name = %s",t1.name);
//        printf("t1.data = %d",t1.age);
//	printf("a = %d\n",NameSpaceB::a);
	return 0;
        
    }
```

