#include <iostream>

template <typename T>
class NonCopiable {
public:
    // constructor
    NonCopiable(T val) {
        std::cout << "Constructor called" << std::endl;
        m_val = new T(val);
    }
    // copy constructor
    NonCopiable(const NonCopiable& other) {
        std::cout << "Copy constructor called" << std::endl;
    }
    // delete move constructor
    NonCopiable(NonCopiable&& other) = delete;
    // delete move assignment operator
    NonCopiable& operator=(const NonCopiable&& other) = delete;

    ~NonCopiable() {
        std::cout << "Destructor called" << std::endl;
        delete m_val;
    }

    const T* getVal() const {
        return m_val;
    }

    void setVal(T* val) {
        m_val = val;
    }
private:
    NonCopiable& operator=(const NonCopiable& other) {
        std::cout << "Assignment operator called" << std::endl;
    }

private:
    T* m_val = nullptr;
};


int main() {
    NonCopiable<int> obj(234);
    NonCopiable<int> obj2(obj);
    // obj2 = obj; // Not allowed to assign by copying

    NonCopiable<char>* elements0 = new NonCopiable('0');
    NonCopiable<char>* elements = new NonCopiable('2');
    NonCopiable<char>* elements2 = nullptr;
    elements2 = std::move(elements);
    auto val = elements->getVal();
    return 0;
}