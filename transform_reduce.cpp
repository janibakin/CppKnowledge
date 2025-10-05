#include <vector>
#include <algorithm>
#include <execution>
#include <random>
#include <chrono>
#include <iostream>
#include <numeric>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    // Generate very big vector
    std::vector<int> vec(50'000'000);  // 50 million elements
    std::generate(vec.begin(), vec.end(), [&]() { return dis(gen); });

    std::cout << "Vector size: " << vec.size() << " elements\n\n";

    // Test 1: Sequential transform + reduce
    {
        std::vector<int> transformed(vec.size());

        auto start = std::chrono::high_resolution_clock::now();

        std::transform(vec.begin(), vec.end(), transformed.begin(),
                      [](int x) { return x * x; });

        long long result = std::reduce(transformed.begin(), transformed.end(), 0LL);

        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "Sequential transform + reduce:\n";
        std::cout << "  Result: " << result << "\n";
        std::cout << "  Time: " << time << "ms\n\n";
    }

    // Test 2: Sequential transform_reduce
    {
        auto start = std::chrono::high_resolution_clock::now();

        long long result = std::transform_reduce(vec.begin(), vec.end(), 0LL,
                                                 std::plus<>(),
                                                 [](int x) { return static_cast<long long>(x) * x; });

        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "Sequential transform_reduce:\n";
        std::cout << "  Result: " << result << "\n";
        std::cout << "  Time: " << time << "ms\n\n";
    }

    return 0;
}