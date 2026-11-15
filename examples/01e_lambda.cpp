#include "result.hpp"
#include <algorithm>
#include <iostream>

// Направление известно только при вызове: это третий аргумент.
bool compare_points(const Result& a, const Result& b, bool descending) {
    return descending ? a.points > b.points : a.points < b.points;
}

int main() {
    auto rows = sample_results();
    bool descending = true;
    // Захват сохраняет копию направления. Два параметра передаст сортировка.
    auto lambda = [descending](const Result& a, const Result& b) {
        return compare_points(a, b, descending);
    };
    // Алгоритм вызывает правило с двумя элементами.
    std::stable_sort(rows.begin(), rows.end(), lambda);
    for (const auto& row : rows) {
        std::cout << row << '\n';
    }
}
