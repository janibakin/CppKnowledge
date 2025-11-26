#include <string>
#include <cassert>

namespace janibakin
{
    template <typename T>
    struct custom_deleter
    {
        void operator()(T* pointer) const
        {
            delete pointer;
        }
    };

    template <typename T, typename custom_deleter = custom_deleter<T>>
    class unique_ptr
    {
    public:
        // default constructor
        unique_ptr() : data(nullptr)
        {
            reset(nullptr);
        }
        // converting constructor
        unique_ptr(T* pointer)
        {
            data = pointer;
        }
        // copy constructor
        unique_ptr(const unique_ptr&) { throw std::runtime_error("Can't copy unique_ptr"); };
        // copy assignment
        unique_ptr& operator=(const unique_ptr&) { throw std::runtime_error("Can't copy assign unique_ptr"); };

        // move constructor
        unique_ptr(unique_ptr&& other) noexcept : data(other.data)
        {
            other.data = nullptr;
        }
        // move
        unique_ptr& operator=(unique_ptr&& other) noexcept
        {
            if (this != &other) {
                custom_deleter{}(data);
                data = other.data;
                other.data = nullptr;
            }
            return *this;
        }

        ~unique_ptr()
        {
            reset(nullptr);
        }

        T* release()
        {
            T* raw_ptr = data;
            data = nullptr;
            return raw_ptr;
        }

        void reset(T* pointer)
        {
            custom_deleter{}(data);
            data = pointer;
        }

        bool is_owning() const { return data != nullptr; }


        T& operator*() const { return *data; }
        T* operator->() const { return data; }
        operator bool() const { return data != nullptr; }

    private:
        T* data;
    };
}

struct SomeStruct
{
    int value {};
};

using namespace janibakin;



int main() {

    // Construct (calls reset with nullptr)
    unique_ptr<SomeStruct> structPtr(new SomeStruct());
    assert(structPtr->value == 0);

    //Release ownership
    SomeStruct* rawStructPtr = structPtr.release();
    assert(structPtr.is_owning() == false);
    assert(rawStructPtr->value == 0);
    delete rawStructPtr;


    // Move construction/assignment (the object your unique_ptr is moved to goes out of scope immediately, hence delete will be called.)
    unique_ptr<SomeStruct> structPtr2(new SomeStruct());
    structPtr2->value = 10;
    unique_ptr<SomeStruct> structPtr3 = std::move(structPtr2);
    assert(structPtr2.is_owning() == false);
    assert(structPtr3->value == 10);


    // Copy construction/assignment (should throw)
    bool copyThrown = false;
    try {
        unique_ptr<SomeStruct> structPtr4(structPtr3);
    } catch (const std::runtime_error&) {
        copyThrown = true;
    }
    assert(copyThrown == true);

    // operator bool()
    unique_ptr<SomeStruct> structPtr5(new SomeStruct());
    assert(static_cast<bool>(structPtr5) == true);
    structPtr5.reset(nullptr);
    assert(static_cast<bool>(structPtr5) == false);

    // is_owning()
    unique_ptr<SomeStruct> structPtr6(new SomeStruct());
    assert(structPtr6.is_owning() == true);
    structPtr6.reset(nullptr);
    assert(structPtr6.is_owning() == false);

}