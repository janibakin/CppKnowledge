#include <thread>
#include <iostream>
#include <vector>

void hello() {
    std::cout << "Hello, World!\n";
}
int main() {
    std::vector<std::thread*> threads;
    for (int i = 0; i < 10; ++i) {
        std::thread* t = new std::thread(hello);
        threads.push_back(t);
    }

    for(int i = 0; i < 10; ++i) {
        threads[i]->join();
    }
    return EXIT_SUCCESS;
}