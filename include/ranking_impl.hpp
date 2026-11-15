#pragma once
#include "report_row.hpp"
#include <algorithm>
#include <cstddef>
#include <numeric>
#include <ostream>
#include <vector>

namespace detail {
// The public API checks the type; this helper implements the shared algorithm.
// Sort indices instead of objects: the original vector is never modified or copied.
template<class T>
void print_ranking_impl(std::ostream& out, const std::vector<T>& rows) {
    // Сортируем не объекты, а номера строк: T не обязан копироваться.
    std::vector<std::size_t> order(rows.size());
    // Заполняем индексы: 0, 1, 2, ...
    std::iota(order.begin(), order.end(), std::size_t{0});
    std::stable_sort(order.begin(), order.end(), [&rows](std::size_t a, std::size_t b) {
        // Bind const references explicitly, even for vector<bool>'s value return.
        const T& left = rows[a];
        const T& right = rows[b];
        // Reverse the natural ordering without requiring operator>.
        return static_cast<bool>(right < left);
    });
    // Теперь читаем исходный вектор в порядке отсортированных индексов.
    std::size_t place = 1;
    for (const auto index : order) {
        const T& row = rows[index];
        print_row_impl(out, place, row);
        ++place;
    }
}
} // namespace detail
