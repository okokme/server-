#include <iostream>
#include <memory>
#include <chrono>
#include <mutex>
struct Base 
{
    Base() { std::cout << " Base::Base()\n"; }
    ~Base() { std::count << " Base::~Base()\n"; }
};
struct Derived: public Base 
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::count << "    Derived::~Derived()\n"; }
};
int main()
{
    std::shared_ptr<Base> p = std::make_shared<Derived>();
    
}
