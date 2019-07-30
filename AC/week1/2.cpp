#include <iostream>
#include <vector>
#include <algorithm>
int main()
{
    std::vector<int> obj;
    int n;
    int p;
    int nn=0; //牛牛的分
    int yy=0; //羊羊的分
    std::cin>>n;
    for(int i=0; i<n; i++)
    {
        std::cin>>p;
        obj.push_back(p);
    }    
    sort(obj.begin(), obj.end());
    reverse(obj.begin(), obj.end());
    int flag = 1;
    while(n--)
    {
        if(flag == 1)
        {
            nn+= obj[0];
            //移动
            obj.erase(obj.begin());
            flag = 0;
        }
        else
        {
            yy+=obj[0];
            obj.erase(obj.begin());//移动
            flag = 1;
        }
    }
    std::cout<<nn-yy<<std::endl;

}
