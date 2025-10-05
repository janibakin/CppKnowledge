#include <vector>
#include <algorithm>
#include <execution>
#include <random>
#include <chrono>
#include <iostream>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    
    long long totalSeqTime = 0;
    long long totalParTime = 0;
    
    for (int i = 0; i < 5; ++i) {
        // generate very big vector
        std::vector<int> vec(10000000);  // 10 million elements
        std::generate(vec.begin(), vec.end(), [&]() { return dis(gen); });
        
        // Copy vector for fair comparison
        std::vector<int> vec_copy = vec;
        
        // Measure sequential sort
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(vec.begin(), vec.end());
        auto end = std::chrono::high_resolution_clock::now();
        auto seqTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        totalSeqTime += seqTime;
        
        // Measure parallel sort
        start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, vec_copy.begin(), vec_copy.end());
        end = std::chrono::high_resolution_clock::now();
        auto parTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        totalParTime += parTime;
        
        std::cout << "Iteration " << (i + 1) << ": Sequential = " << seqTime 
                  << "ms, Parallel = " << parTime << "ms" << std::endl;
    }
    
    std::cout << "\n=== Results ===" << std::endl;
    std::cout << "Total Sequential Time: " << totalSeqTime << "ms" << std::endl;
    std::cout << "Total Parallel Time: " << totalParTime << "ms" << std::endl;
    std::cout << "Average Sequential Time: " << (totalSeqTime / 1000.0) << "ms" << std::endl;
    std::cout << "Average Parallel Time: " << (totalParTime / 1000.0) << "ms" << std::endl;
    std::cout << "Speedup: " << (static_cast<double>(totalSeqTime) / totalParTime) << "x" << std::endl;
    
    return 0;
}