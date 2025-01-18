#include <iostream>
class Base {
public:
    Base() { print(); }
    virtual void print() { std::cout << "Calling print from Base" << std::endl; }
    virtual ~Base() { print(); }
};

class Derived : public Base {
public:
    Derived() { print(); }
    void print() { std::cout << "Calling print from Derived" << std::endl; }
    virtual ~Derived() { print(); }
};

int main() {
    Base* obj = new Derived();
    obj->print();
    delete obj;
    return 0;
}