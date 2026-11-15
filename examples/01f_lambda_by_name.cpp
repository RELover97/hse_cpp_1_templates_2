#include "result.hpp"
#include <algorithm>
#include <iostream>


int main() {
    auto rows = sample_results();
    // Алгоритм вызывает правило с двумя элементами.
    std::stable_sort(rows.begin(), rows.end(), [](const Result& a, const Result& b) {
        return a.name < b.name;
    });
    for (const auto& row : rows) {
        std::cout << row << '\n';
    }
}
