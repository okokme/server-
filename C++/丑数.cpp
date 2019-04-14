#include <iostream>

int main()
{
 class Solution 
 {
   public:
   int nthUglyNumber(int n) {    
        if (n <= 1)
         {
            return 1;
        }
        int counter = 0;
        for (int i = 1; ; i++)
         {            
                 if (isUgly(i)) 
                 {
                counter++;
                if (counter == n)
                 {
                    return i;
                }
            } 
        }
        public:
           bool isUgly(int num)
           {
           			if(num <= 0)
           			{
           					return false;
           			}
           			while(n%2 == 0)
           			{
           			num / = 2;
           			}
           			   while(n%3 == 0)
           			   {
           			   			num /= 3;
           			   			}
           			   			while(n%5 == 0)
           			   			{
           			   				num/=5;
           			   				}
           			   				if(num == 1)
           			   				{
           			   							return true;
           			   							}
           			   							else
           			   							{
           			   							return false;
           			   							}
           }
    }
    return 0;
}

