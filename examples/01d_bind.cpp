#include "result.hpp"
#include <algorithm>
#include <iostream>
#include <functional>

// Направление известно только при вызове: это третий аргумент.
bool compare_points(const Result& a, const Result& b, bool descending) {
    return descending ? a.points > b.points : a.points < b.points;
}

int main() {
    auto rows = sample_results();
    bool descending = true;
    using namespace std::placeholders;
    // _1 и _2 — аргументы будущего вызова; направление сохраняем сейчас.
    auto bound = std::bind(compare_points, _1, _2, descending);
    // Алгоритм вызывает правило с двумя элементами.
    std::stable_sort(rows.begin(), rows.end(), bound);
    for (const auto& row : rows) {
        std::cout << row << '\n';
    }
}
