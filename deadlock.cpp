#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

void calculate(std::mutex& m1, std::mutex& m2, const std::vector<int>& data) {
    std::lock_guard<std::mutex> lock1(m1);
    std::lock_guard<std::mutex> lock2(m2);
}
int main() {
    std::mutex m1;
    std::mutex m2;
    const std::vector<int> arr {1,4,1,5,7,5,3};
    calculate(m1, m2, arr);
}