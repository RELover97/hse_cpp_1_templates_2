#include "result.hpp"
#include <iostream>

// Направление известно только при вызове: это третий аргумент.
bool compare_points(const Result& a, const Result& b, bool descending) {
    return descending ? a.points > b.points : a.points < b.points;
}
int main() {
    auto rows = sample_results();
    const bool descending = true;
    std::cout << std::boolalpha;
    // Boris (95) должен стоять раньше Anna (82).
    std::cout << compare_points(rows[1], rows[0], descending) << '\n';
    // При обратном направлении та же пара даёт false.
    std::cout << compare_points(rows[1], rows[0], false) << '\n';
    // stable_sort(rows.begin(), rows.end(), compare_points) не скомпилируется:
    // алгоритм передаёт два аргумента, а compare_points требует три.
}
