#include "result.hpp"
#include "concepts_ranking.hpp"
#include <iostream>

// This type cannot be copied or moved; sorting indices is still possible.
struct FixedResult {
    int points = 0;
    FixedResult() = default;
    FixedResult(const FixedResult&) = delete;
    FixedResult(FixedResult&&) = delete;
    friend bool operator<(const FixedResult& a, const FixedResult& b) {
        return a.points < b.points;
    }
    friend std::ostream& operator<<(std::ostream& out, const FixedResult& value) {
        return out << value.points;
    }
};
static_assert(modern::Rankable<FixedResult>);

int main() {
    // Сразу создаём вектор нужного размера: объекты не перемещаются.
    std::vector<FixedResult> fixed(2);
    fixed[0].points = 3;
    fixed[1].points = 7;
    modern::print_ranking(std::cout, fixed);
}
