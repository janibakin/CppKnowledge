#include <thread>
#include <chrono>
#include <iostream>

int main() {
    // start timer
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 100000000; i++) {
        // do nothing
    }
    // end timer
    auto end = std::chrono::high_resolution_clock::now();
    // calculate time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // print time
    std::cout << "Time: " << duration.count() << " microseconds" << std::endl;
}