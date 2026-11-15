#include "result.hpp"
#include <algorithm>
#include <iostream>
struct ByPoints {
    bool operator()(const Result& a, const Result& b) const {
        return a.points > b.points;
    }
};
#include <utility>

// A wrapper keeps the caller's value category when passing the comparator onward.
// stable_sort itself accepts a comparator by value and may copy it internally.
template<class Compare>
void rank_by(std::vector<Result>& rows, Compare&& compare) {
    std::stable_sort(rows.begin(), rows.end(), std::forward<Compare>(compare));
}

int main() 
{
    auto rows = sample_results();

    ByPoints comparator;
    
    rank_by(rows, comparator); // Именованный функтор.
    
    rank_by(rows, ByPoints{}); // Временный функтор.
    
    rank_by(rows, [](const Result& a, const Result& b) {
        return a.points > b.points;
    }); // Лямбда тоже подходит.
    
    for (const auto& row : rows) {
        std::cout << row << '\n';
    }
}
