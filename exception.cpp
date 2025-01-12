#include <iostream>
#include <memory>

class A {
public:
    A() {
        std::cout << "A()" << std::endl;
        ptr = std::make_unique<int>(2);
        throw 1;
    }
    ~A() {
        std::cout << "~A()" << std::endl;
    }
private:
    std::unique_ptr<int> ptr = nullptr;
};
int main() {
    try {
        A* a = new A();
    } catch (int e) {
        std::cout << "Caught exception: " << e << std::endl;
    }
    return 0;
}