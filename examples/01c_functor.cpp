#include "result.hpp"
#include <algorithm>
#include <iostream>

// Состояние хранится в объекте, а не в глобальной переменной.
struct ByPoints {
    bool descending;

    bool operator()(const Result& a, const Result& b) const {
        return descending ? a.points > b.points : a.points < b.points;
    }
};

int main() {
    auto rows = sample_results();
    bool descending = true;
    // Алгоритм вызывает правило с двумя элементами.
    std::stable_sort(rows.begin(), rows.end(), ByPoints{descending});
    ByPoints points{true};
    points(rows[0], rows[1]);
    points.operator()(rows[0], rows[1]);
    for (const auto& row : rows) {
        std::cout << row << '\n';
    }
}
