#include <iostream>

class myClass {
public:
    void doSmth() const {
        // x = 5; // Error: assignment of member 'myClass::x' in read-only object
        // y = 5; // Error: assignment of member 'myClass::y' in read-only object
    }
private:
    int x;
    int y;
};

class mutableClass {
public:
    void doSmth() const {
        // x = 5; // Error: expression must be a modifiable lvalueC/C++(137)
        y = 5;
    }
private:
    int x {2};
    mutable int y {0}; // mutable keyword allows to modify the variable in a const function
};

int main() {
    myClass obj;

    int i = 3;
    int* const p(&i);
    int k = 4;
    *p = k;
    // p = &k; // Error: assignment of read-only variable 'p'

    mutableClass obj2;
    obj2.doSmth();
    return 0;
}