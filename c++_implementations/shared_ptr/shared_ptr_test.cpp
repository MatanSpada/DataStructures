#include <iostream> // streams
#include <cassert> // assert
#include "shared_ptr.hpp" // shared_ptr API

using namespace ilrd_rd1145;

class Base
{
public:
    Base() {}
    virtual ~Base() {}
    virtual void display() {std::cout << "Base test" << std::endl;}
private:
    int a;
};

class Derived : public Base
{
public:
    Derived() {}
    ~Derived() {}
    void display() {std::cout << "Derived test" << std::endl;}
private:
    int b;
};

void TestingCtors()
{
    int *num = new int;
    *num = 5;
    SharedPtr<int> ptr(num);

    SharedPtr<int> ptr2 = ptr;

    SharedPtr<int> ptr3(ptr);

    assert(&(*ptr) == &(*ptr2));
    assert(&(*ptr3) == &(*ptr2));
}

void TestingAssignment()
{
    Base *base = new Base();
    Base *base2 = new Base();
    Derived *derived = new Derived();
    SharedPtr<Base> ptr(base);
    SharedPtr<Base> ptr2(base2);
    SharedPtr<Derived> ptr3(derived);

    ptr = ptr2;
    assert(&(*ptr) == &(*ptr2));

    ptr = ptr3;
    assert(&(*ptr) == &(*ptr3));
}

void TestingGetters()
{
    Base *base = new Base();
    Derived *derived = new Derived();
    SharedPtr<Base> ptr(base);
    SharedPtr<Derived> ptr2(derived);

    ptr->display();
    ptr2->display();

    ptr = ptr2;

    assert(ptr.Get() == ptr2.Get());
}

int main()
{
    TestingCtors();
    TestingAssignment();
    TestingGetters();

    std::cout << "\n\033[1;35mAll done!\033[0;0m\n" << std::endl;

    return (0);
}