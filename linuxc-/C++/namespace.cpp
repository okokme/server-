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



