#include <iostream>

template <typename Type>
class shared_ptr {
public:
    // default constr
    shared_ptr() : obj(nullptr), counter(nullptr) {}
    // regular constr
    shared_ptr(Type* newObj) {
        obj = newObj;
        counter = new int(1);
    }
    ~shared_ptr() {
        // if counter exists, i.e. is not nullptr
        if(counter) {
            (*counter)--;
            if(*counter == 0) {
                delete obj;
                delete counter;
            }
        }
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
        if(other.obj) {
            obj = other.obj;
            counter = other.counter;
            (*counter)++;
        }
        return *this;
    }
    // move constr
    shared_ptr(shared_ptr&& other);
    // move assignment
    shared_ptr&& operator=(shared_ptr&& other);

private:
    Type* obj;
    int* counter;
};

int main() {
    shared_ptr<int> ptr1(new int(12));
    shared_ptr<int> ptr2;
    ptr2 = ptr1;
    return EXIT_SUCCESS;
}