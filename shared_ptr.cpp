#include <iostream>

template <typename T>
class shared_ptr {
public:
    // Constructor
    explicit shared_ptr(T* raw_ptr = nullptr) : data(raw_ptr), counter(raw_ptr ? new int(1) : nullptr) {}

    // Copy Constructor
    shared_ptr(const shared_ptr& other) : data(other.data), counter(other.counter) {
        if(counter) (*counter)++;
    }

    // Assignment Operator
    shared_ptr& operator=(const shared_ptr& other) {
        if(this != &other) {
            data = other.data;
            counter = other.counter;
            if(counter) (*counter)++;
        }
        return *this;
    }

    // Move Constructor
    shared_ptr(shared_ptr&& other) : data(other.data), counter(other.counter) {
        other.data = nullptr;
        other.counter = nullptr;
    }
    // move assignment
    shared_ptr& operator=(shared_ptr&& other) {
        if(this != &other) {
            data = other.data;
            counter = other.counter;
            other.data = nullptr;
            other.counter = nullptr;
        }
        return std::move(*this);
    }

    // Destructor
    ~shared_ptr() {
        reset();
    }

    // get(): Returns the raw pointer
    T* get() const {
        return data;
    }

    // use_count(): Returns the reference count
    int use_count() const {
        return counter ? *counter : 0;
    }

    // reset(): Releases ownership of the managed object
    void reset(T* new_ptr = nullptr) {
        if(counter) {
            (*counter)--;
            if(*counter == 0) {
                delete data;
                delete counter;
            }
        }
        data = new_ptr;
        counter = new_ptr ? new int(1) : nullptr;
    }

    // Dereference operator
    T& operator*() const {
        return *data;
    }

    // Member access operator
    T* operator->() const {
        return data;
    }

private:
    T* data {nullptr};
    int* counter {nullptr};
};

int main() {
    // Basic tests
    shared_ptr<int> ptr1(new int(10));
    shared_ptr<int> ptr2(ptr1);
    shared_ptr<int> ptr3 = ptr1;
    shared_ptr<int> ptr4 = std::move(ptr1);
    shared_ptr<int> ptr5;
    ptr5 = std::move(ptr2);
    // std::cout << "ptr1: " << *ptr1 << " use_count: " << ptr1.use_count() << std::endl; // nullptr dereference - will segfault
    // std::cout << "ptr2: " << *ptr2 << " use_count: " << ptr2.use_count() << std::endl; // nullptr dereference - will segfault
    std::cout << "ptr3: " << *ptr3 << " use_count: " << ptr3.use_count() << std::endl;
    std::cout << "ptr4: " << *ptr4 << " use_count: " << ptr4.use_count() << std::endl;
    std::cout << "ptr5: " << *ptr5 << " use_count: " << ptr5.use_count() << std::endl;

    return EXIT_SUCCESS;
}