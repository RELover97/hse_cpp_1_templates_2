#include "result.hpp"
#include "sfinae.hpp"
#include <iostream>

/*

template<class T>
inline constexpr bool is_rankable_v = is_comparable<T>::value && is_printable_v<T>;

// enable_if_t<true, int> is int; enable_if_t<false, int> has no type.
// This non-type template parameter defaults to 0 and is not a function argument.

template<class T, std::enable_if_t<is_rankable_v<T>, int> = 0>
void print_ranking(std::ostream& out, const std::vector<T>& rows) {
    detail::print_ranking_impl(out, rows);
}

*/

int main() {
    // enable_if допускает только типы, удовлетворяющие обоим требованиям.
    sfinae::print_ranking(std::cout, sample_results());
    sfinae::print_ranking(std::cout, std::vector<int>{3, 8, 1});
}
