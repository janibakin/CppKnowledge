#include <iostream>

/*
    Here we are trying to access private members of some class, by creating a copy of this class,
    having the same layout, but also a public getter to access private member
*/
class Something {
public:
    Something() {
        topSecretValue = 42;
    }
    bool somePublicBool;
    int somePublicInt;
    std::string somePublicString;
private:
    int topSecretValue;
};

class SomethingReplica {
public:
    int getTopSecretValue() { return topSecretValue; }
    bool somePublicBool;
    int somePublicInt;
    std::string somePublicString;
private:
    int topSecretValue;
};

int main(int argc, const char * argv[]) {
    Something a;
    SomethingReplica* b = reinterpret_cast<SomethingReplica*>(&a);
    std::cout << b->getTopSecretValue() << std::endl;
}
