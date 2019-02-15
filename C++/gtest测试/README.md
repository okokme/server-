## gtest测试

一个link unit的test program拥有一个main函数，main函数的编写：

```c++
int main(int argc, char **argc)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

其中RUN_ALL_TEST()函数将运行一个link unit中全部的tests

需要注意的一点是main函数一定要返回RUN_ALL_TESTS的返回值，否则会出错，即return RUN_ALL_TESTS()，而且RUN_ALL_TESTS()只能被调用1次，否则会引起线程问题。

---



##### 基础的断言

| Fatal assertion          | Nonfatal assertion       | Verifies           |
| ------------------------ | ------------------------ | ------------------ |
| ASSERT_FALSE(condition); | EXPECT_FALSE(condition); | condition is false |
| ASSERT_TRUE(condition);  | EXPECT_TRUE(condition);  | condition is true  |



##### 数值比较

| Fatal assertion：     | Nonfatal assertion    | Verifies     |
| --------------------- | --------------------- | ------------ |
| ASSERT_EQ(val1,val2); | EXPECT_EQ(val1,val2)  | val1 == val2 |
| ASSERT_NE(val1,val2); | EXPECT_NE(val1,val2); | val1 != val2 |
| ASSERT_LT(val1,val2); | EXPECT_LT(val1,val2); | val1 < val2  |
| ASSERT_LE(val1,val2); | EXPECT_LE(val1,val2); | val1 <= val2 |
| ASSERT_GT(val1,val2); | EXPECT_GT(val1,val2); | val1 > val2  |
| ASSERT_GE(val1,val2); | EXPECT_GE(val1,val2); | val1 >= val2 |



##### 字符串比较

| Fatal assertion               | Nonfatal assertion           | Verifies                                                |
| ----------------------------- | ---------------------------- | ------------------------------------------------------- |
| ASSERT_STREQ(str1,str2);      | EXPECT_STREQ(str1,_str_2);   | the two C strings have the same content                 |
| ASSERT_STRNE(str1,str2);      | EXPECT_STRNE(str1,str2);     | the two C strings have different content                |
| ASSERT_STRCASEEQ(str1,str2)； | EXPECT_STRCASEEQ(str1,str2); | the two C strings have the same content, ignoring case  |
| ASSERT_STRCASENE(str1,str2);  | EXPECT_STRCASENE(str1,str2); | the two C strings have different content, ignoring case |



下面看些具体的例子，假设我有四个文件：my_test.cc、my_test1.cc、my_test2.cc、my_class.h

###### my_test.cc

```c++
#include <gtest/gtest.h>
TEST(MyTestCase, FirstTest)
{
    EXPECT_EQ(2,2);
}
TEST(MyTestCase, SecongTest)
{
    EXPECT_EQ(2,2);
}
int main(int argc, char **argv)
{
     ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

###### my_test1.cc

```c++
#include <gtest/gtest.h>
TEST(MyTestCase, ThirdTest)
{
    ASSERT_EQ(3,3) << "3 is not equal to 4";
    char* p = NULL;
    ASSERT_STREQ(NULL, p);
}
TEST(YourTestCase, FirstTest)
{
    EXPECT_EQ(3,3);
}
```

###### my_test2.cc

```c++
#include <gtest/gtest.h>
#include "my_class.h"
class MyClassTest : public ::testing::Test
{
	public:
		virtual void SetUp()
        {
        	my_class_ = new MyClass(10);
        }
        virtual void TearDown()
        {
        	delete my_class_;
        }
        MyClass* my_class_;
};
TEST_F(MyClassTest, FirstTest) {
  EXPECT_EQ(10, my_class_->GetX());
  my_class_->SetX(2);
}

TEST_F(MyClassTest, SecondTest) {
  EXPECT_EQ(10, my_class_->GetX());
  my_class_->SetX(2);
}
```



my_class.h

```c++
#include <stdio.h>
class MyClass
{
    public:
    	MyClass(int x) :x_(x) {}
    	void SetX(int x)
        {
            x_  = x;
        }
		int GetX()const{
			return x_;    
		}
	private:
		int x_;
};
```



编译命令：

`g++ my_test.cc my_test1.cc my_test2.cc -lgtest -lpthread`































