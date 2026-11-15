#include "result.hpp"
#include "sfinae.hpp"
#include <iostream>

/*

// Проверяем все поля с их фактическими категориями после forward.
// Fold по && для пустого пакета равен true: пустая строка допустима.
template<class... Fields,
         std::enable_if_t<(is_insertable<Fields&&>::value && ...), int> = 0>
void print_row(std::ostream& out, Fields&&... fields) {
    detail::print_row_impl(out, std::forward<Fields>(fields)...);
}

*/

int main() {
    // Условие свёртки проверяет печатаемость каждого поля.
    sfinae::print_row(std::cout, "Place", "Result");
    sfinae::print_row(std::cout, 1, Result{"Anna", 82});
    sfinae::print_row(std::cout); // Пустой пакет: && даёт true.
}
