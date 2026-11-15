#include "result.hpp"
#include <algorithm>
#include <iostream>

struct ByPoints {
    bool operator()(const Result& a, const Result& b) const {
        return a.points > b.points;
    }
};

// compare — собственный локальный объект функции;
// такая реализация - хороший вариант, если мы хотим
// владеть копией компаратора.
// Но если у нас появляется новое требование - передать
// компаратор дальше в ещё одну функцию, при этом сохранив
// информацию о категории значения (= какой компаратор
// передан: lvalue, rvalue), то нужно модифицировать реализацию
// То есть мы хотели бы:
// 
// template<class Compare>
// void rank_by(std::vector<Result>& rows, Compare compare) {
//      some_fun(rows, compare);
// }
template<class Compare>
void rank_by(std::vector<Result>& rows, Compare compare) {
    std::stable_sort(rows.begin(), rows.end(), compare);
}

int main() 
{
    auto rows = sample_results();

    ByPoints comparator;

    rank_by(rows, comparator);

    for (const auto& row : rows) {
        std::cout << row << '\n';
    }
}
