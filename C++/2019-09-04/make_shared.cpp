#include <bits/stdc++.h>
using namespace std;

int main(void)
{
    shared_ptr<string> p1 = make_shared<string>(10, '9');
    shared_ptr<string> p2 = make_shared<string>("hello");
    shared_ptr<string> p3 = make_shared<string>();
    
    /* template<typename _Tp, typename... _Args>
     * inline shared_ptr<_Tp> make_shared(_Args&&... __args)
     *
     * std::forward<_Args>(__args)...
     *
     * return shared_ptr<_Tp>(_Sp_make_shared_tag(), __a,
     *                          std::forward<_Args>(__args)...);
     *
     *
}
