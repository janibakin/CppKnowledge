// Single Producer Single Consumer Queue

#include <cstddef>
#include <iostream>
#include <cassert>


namespace janibakin
{
    template <typename T>
    class SPSCQ
    {
    public:
        SPSCQ(size_t capacity) {
            // Verify capacity is power of 2 and at least 2
            if (capacity < 2 || (capacity & (capacity - 1)) != 0) {
                throw std::runtime_error("capacity must be power of 2 and at least 2");
            }
            capacity_ = capacity;
            data_ = static_cast<T*>(::operator new((capacity_ + 1) * sizeof(T)));
        }
        // copy constructor
        SPSCQ(const SPSCQ& queue) {
            throw std::runtime_error("Can't copy SPSCQ");
        }
        // copy assignment
        SPSCQ& operator=(const SPSCQ& queue) {
            throw std::runtime_error("Can't copy assign SPSCQ");
        }
        // move constructor
        SPSCQ(SPSCQ&& queue) {
            throw std::runtime_error("Can't move SPSCQ");
        }
        // move assign
        SPSCQ& operator=(SPSCQ&& queue) {
            throw std::runtime_error("Can't move assign SPSCQ");
        }

        // destructor
        ~SPSCQ() {
            std::size_t currPop = popIndex_.load(std::memory_order_relaxed);
            std::size_t currPush = pushIndex_.load(std::memory_order_relaxed);

            // Destroy all constructed objects still in the queue
            while (currPop != currPush) {
                data_[to_index(currPop)].~T();
                ++currPop;
            }

            // Deallocate raw memory
            ::operator delete(data_);
        }

        bool push(const T& item)
        {
            std::size_t currPush = pushIndex_.load(std::memory_order_relaxed);
            std::size_t nextPush = currPush + 1;
            std::size_t currPop = popIndex_.load(std::memory_order_acquire);

            // Check if full: we keep one slot reserved, so max items = capacity - 1
            // This reserved slot helps distinguish full from empty
            if (nextPush - currPop >= capacity_) {
                return false;  // Queue is full
            }

            new (&data_[to_index(currPush)]) T(item);

            pushIndex_.store(nextPush, std::memory_order_release);
            return true;
        }

        bool pop(T& item)
        {
            std::size_t currPop = popIndex_.load(std::memory_order_relaxed);
            std::size_t currPush = pushIndex_.load(std::memory_order_acquire);

            // Check if empty: pop index caught up with push index
            if (currPop == currPush) {
                return false;  // Queue is empty
            }

            // Copy/move the item out
            item = data_[to_index(currPop)];

            // Destroy the object since we've moved it out
            data_[to_index(currPop)].~T();

            // Publish the new pop index with release semantics
            popIndex_.store(currPop + 1, std::memory_order_release);
            return true;
        }

        [[nodiscard]] bool full() const
        {
            // Full when size equals capacity - 1 (due to reserved slot)
            return size() >= capacity_ - 1;
        }

        [[nodiscard]] size_t size() const
        {
            // Size is simply the difference between push and pop indices
            // This works even when indices wrap around due to unsigned arithmetic
            std::size_t currPush = pushIndex_.load(std::memory_order_acquire);
            std::size_t currPop = popIndex_.load(std::memory_order_acquire);
            return currPush - currPop;
        }

        [[nodiscard]] bool empty() const
        {
            return size() == 0;
        }

    private:
        inline std::size_t to_index(std::size_t monotonic_index) const {
            // Use modulo (capacity + 1) since we allocated capacity + 1 slots
            return monotonic_index % (capacity_ + 1);
        }

        std::size_t capacity_;
        T* data_;

        std::atomic<std::size_t> pushIndex_ {};
        std::atomic<std::size_t> popIndex_ {};
    };
}

using namespace janibakin;
int main() {
    SPSCQ<int> queue(8);
    for (int i{}; i < 8; ++i) {
        queue.push(i);
    }
    assert(queue.full() == true);

    assert(queue.push(11) == false);

    int temp;
    queue.pop(temp);
    queue.pop(temp);

    assert(queue.size() == 6);

    queue.pop(temp);
    queue.pop(temp);
    queue.pop(temp);

    assert(queue.size() == 3);


    queue.pop(temp);
    queue.pop(temp);
    queue.pop(temp);

    assert(queue.empty() == true);

    assert(queue.pop(temp) == false);

    try {
        auto newQ {queue};
    } catch (...) {
        std::cout << "Caught exception: copy\n";
    }

    try {
        auto newQ = queue;
    } catch (...) {
        std::cout << "Caught exception: copy assign\n";
    }

    try {
        auto newQ {std::move(queue)};
    } catch (...) {
        std::cout << "Caught exception: move\n";
    }

    try {
        auto newQ = std::move(queue);
    } catch (...) {
        std::cout << "Caught exception: move assign\n";
    }
}
