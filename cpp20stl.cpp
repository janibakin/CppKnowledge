#include <iostream>
#include <vector>
#include <ranges>
#include <format>
#include <string>
#include <map>
#include <algorithm>

void ranges() {
    std::vector<std::string> words = {
        "apple", "apricot", "banana", "blueberry", "avocado", "blackberry"
    };

    // Group by first letter
    std::map<char, std::vector<std::string>> groups;
    for (const auto& word : words) {
        if (!word.empty()) {
            groups[word[0]].push_back(word);
        }
    }
    // Sort each group
    for (auto &word: groups | std::views::values) {
        std::ranges::sort(word);
    }
    // Print output
    for (const auto& [letter, group] : groups) {
        std::cout << letter << ": ";
        for (const auto& word : group) {
            std::cout << word << " ";
        }
        std::cout << "\n";
    }
}

void views() {
    std::vector<int> nums = {1,2,3,4,5,6,7,8,9,10};

    auto even = nums | std::views::filter([](int n) { return n % 2 == 0; });
    auto even_squared = even | std::views::transform([](int n) { return n * n;});

    for (auto val : even_squared) {
        std::cout << std::format("{}\n", val);
    }
}

int main() {
    views();
    ranges();
}

