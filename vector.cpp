// Custom vector implementation
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <memory>
namespace janibakin {
    template <typename Element>
    class vector {
    public:
        void push_back(Element element) {
            if (size_ + 1 == capacity_) {
                // triple capacity
                capacity_ *= 3;
                // allocate new chunk of memory to fit the data_ into, with capacity_
                Element* new_mem = static_cast<Element*>(::operator new(capacity_ * sizeof(Element)));
                // move-construct to new memory
                for (std::size_t i{}; i < size_; ++i) {
                    new (&new_mem[i]) Element(std::move(data_[i]));
                    data_[i].~Element();
                }
                // release previously owned memory
                ::operator delete(data_);
                // assign previously push_backed data to data_, but located in a new chunk of memory
                data_ = new_mem;
            }
            // add element
            data_[size_++] = element;
        }
        const Element& at(std::size_t index) const {
            if (index >= size_ || index < 0) {
                throw std::runtime_error("Cannot access element at index: " + std::to_string(index));
            }
            return data_[index];
        }
        std::size_t get_size() const {
            return size_;
        }
        std::size_t get_capacity() const {
            return capacity_;
        }
        void shrink_to_fit() {
            if (size_ < capacity_) {
                // allocate new memory of size_
                Element* new_mem = static_cast<Element*>(::operator new(size_ * sizeof(Element)));
                // move-construct
                for (std::size_t i{}; i < size_; ++i) {
                    new (&new_mem[i]) Element(std::move(data_[i]));
                    data_[i].~Element();
                }
                // delete old elements
                ::operator delete(data_);
                // update data
                data_ = std::move(new_mem);
                // update capacity_
                capacity_ = size_;
            }
        }
        void pop_back() {
            if (size_ == 0) {
                throw std::runtime_error("Vector is empty, nothing to pop.");
            }
            --size_;
            data_[size_].~Element();
        }
    private:
        Element* data_ {nullptr};
        std::size_t size_ {0};
        std::size_t capacity_ {1};
    };
}

using namespace janibakin;

int main() {
    vector<int> ints{};
    // test push_back
    ints.push_back(2);
    ints.push_back(3);
    ints.push_back(3);
    ints.push_back(3);
    ints.push_back(3);
    assert(ints.get_size() == 5);
    assert(ints.get_capacity() == 9);

    ints.pop_back();
    ints.pop_back();
    ints.pop_back();
    assert(ints.get_size() == 2);
    assert(ints.get_capacity() == 9);

    ints.shrink_to_fit();
    assert(ints.get_capacity() == 2);
    assert(ints.get_size() == 2);

    // assert(ints.at(0) == 2);
    // assert(ints.at(1) == 3);
    // try {
    //     int temp = ints.at(2);
    // } catch (const std::runtime_error& e) {
    //     std::cout << "Caught out of bounds access as expected: " << e.what() << std::endl;
    // }

    vector<int> vals;
    vals.push_back(1);
    vals.push_back(2);
    vals.push_back(3);
    vals.pop_back();
    vals.shrink_to_fit();
    assert(vals.get_capacity() == 2);

}