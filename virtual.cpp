#include <iostream>
class Base {
public:
    Base() { print(); }
    virtual void print() { std::cout << "Calling print from Base" << std::endl; }
    virtual ~Base() { std::cout << "Calling destructor of Base" << std::endl; }
};

class Derived : public Base {
public:
    Derived() { print(); throw "error"; }
    void print() { std::cout << "Calling print from Derived" << std::endl; }
    virtual ~Derived() { std::cout << "Calling destructor of Derived" << std::endl; }
};

int main() {
    try {
        Base* obj = new Derived();
        obj->print();
        delete obj;
    } catch (...) {

    }
}