#include <iostream>
#include <memory>
#include <list>
using namespace std;

void useShared_ptr(int *p)
{
    cout<<*p<<endl;
}

void delePointer(int *p)
{
    delete p;
}

int main(int argc, char *argv[])
{
  //  shared_ptr<int> p1 = make_shared<int>(32);
  //  shared_ptr<string> s = make_shared<string>("hhhhhha");
  //  cout<<*(s.get())<<endl;
    //    shared_ptr<int>p2(p1.get());  //!错误的用法：但是p1、p2各自保留了对一段内存的引用计数，其中有一个引用计数耗尽，资源也就释放了。
 //   useShared_ptr(p1.get());
//    delePointer(p1.get());        //!error:
    auto p = make_shared<int>(42);
    cout<<p.use_count()<<endl;
    auto q(p);
    cout<<p.use_count()<<endl;   
      
    auto r = make_shared<int>(56); //指向的对象只有r一个引用者
    cout<<r.use_count()<<endl;
    r = p; //r原来引用的对象经过赋值之后释放掉了，p引用的对象有p、q、r三个引用
    cout<<*p<<"=="<<*q<<"=="<<*r;
    cout<<p.use_count()<<endl;
    cout<<q.use_count()<<endl;
    cout<<r.use_count()<<endl;
    
    list<shared_ptr<string>> pstrList;
    pstrList.push_back(make_shared<string>("11111"));
    pstrList.push_back(make_shared<string>("22222"));
    pstrList.push_back(make_shared<string>("33333"));
    pstrList.push_back(make_shared<string>("44444"));
    for(auto p:pstrList)
    {
        if(*p == "33333");
        {
            cout<<"use 33333"<<endl;
        }
        cout<<*p<<endl;
    }
    /*包含"33333"的数据我们已经使用完了*/
    auto it = pstrList.begin();
    for(; it!=pstrList.end(); ++it)
    {
        if(**it == "33333")
        {
            cout<<**it<<endl;
            pstrList.erase(it);
        }
    }
    cout<<"---------after move------------"<<endl;
    for(auto p:pstrList)
    {
        cout<<*p<<endl;
    }

    return 0;
}
