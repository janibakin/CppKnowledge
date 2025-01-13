#include <iostream>

template <typename Type>
class shared_ptr {
    void reset() {
        // if counter exists, i.e. is not nullptr
        if(counter) {
            (*counter)--;
            if(*counter == 0) {
                delete obj;
                delete counter;
                obj = nullptr;
                counter = nullptr;
            }
        }
    }
public:
    // default constr
    shared_ptr() : obj(nullptr), counter(nullptr) {}
    // regular constr
    shared_ptr(Type* newObj) {
        obj = newObj;
        counter = new int(1);
    }
    ~shared_ptr() {
        reset();
    }
    // copy constr
    shared_ptr(const shared_ptr& other) {
        if(other.obj) {
            obj = other.obj;
            counter = other.counter;
            (*counter)++;
        }
    }
    // copy assignment
    shared_ptr& operator=(const shared_ptr& other) {
        if(this == &other) {
            return *this;
        }
        reset();
        if(other.obj) {
            obj = other.obj;
            counter = other.counter;
            (*counter)++;
        }
        return *this;
    }
    // move constr
    shared_ptr(shared_ptr&& other) {
        obj = other.obj;
        counter = other.counter;
        other.obj = nullptr;
        other.counter = nullptr;
    }
    // move assignment
    shared_ptr&& operator=(shared_ptr&& other) {
        obj = other.obj;
        counter = other.counter;
        other.obj = nullptr;
        other.counter = nullptr;
        return *this;
    }
    // get method to get the object pointer
    Type* get() const {
        return obj;
    }
    // get the object value
    Type& operator*() const {
        return *obj;
    }

private:
    Type* obj;
    int* counter;
};

int main() {
    shared_ptr<int> ptr1(new int(12));
    std::cout << ptr1.get() << std::endl;
    std::cout << *ptr1 << std::endl;
    shared_ptr<std::string> ptr2(new std::string("Hello World!"));
    shared_ptr<int> ptr3 = std::move(ptr1);
    return EXIT_SUCCESS;
}