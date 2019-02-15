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
