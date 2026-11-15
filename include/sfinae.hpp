#pragma once
#include "ranking_impl.hpp"
#include <type_traits>
#include <utility>

namespace sfinae {
// Expression SFINAE: invalid dependent return type removes the int overload.
// This small probe checks only whether the insertion expression exists.
template<class T>
auto try_print(std::ostream& out, const T& value, int)
    // Проверяем тип выражения, не выполняя вывод; при ошибке кандидат исчезает.
    -> decltype(static_cast<void>(out << value)) {
    out << value;
}
template<class T>
void try_print(std::ostream& out, const T&, long) {
    out << "[not printable]";
}

// Запрос is_comparable<T> означает is_comparable<T, void>.
// Основной шаблон — запасной вариант, value == false.
template<class T, class = void>
struct is_comparable : std::false_type {};
// declval моделирует const lvalue без создания объекта.
// Если сравнение допустимо, decltype даёт bool, void_t превращает его в void.
// Тогда частичная специализация соответствует <T, void>, value == true.
template<class T>
struct is_comparable<T, std::void_t<decltype(static_cast<bool>(
    std::declval<const T&>() < std::declval<const T&>()))>> : std::true_type {};

// Expr сохраняет ссылку и const, чтобы проверять именно будущий вывод.
// При успехе is_same дополнительно проверяет возвращаемый тип потока.
template<class Expr, class = void>
struct is_insertable : std::false_type {};
template<class Expr>
struct is_insertable<Expr, std::void_t<decltype(
    std::declval<std::ostream&>() << std::declval<Expr>())>>
    : std::is_same<decltype(std::declval<std::ostream&>() << std::declval<Expr>()),
                   std::ostream&> {};

template<class T>
inline constexpr bool is_printable_v = is_insertable<const T&>::value;
template<class T>
inline constexpr bool is_rankable_v = is_comparable<T>::value && is_printable_v<T>;

// enable_if_t<true, int> is int; enable_if_t<false, int> has no type.
// This non-type template parameter defaults to 0 and is not a function argument.
template<class T, std::enable_if_t<is_rankable_v<T>, int> = 0>
void print_ranking(std::ostream& out, const std::vector<T>& rows) {
    detail::print_ranking_impl(out, rows);
}

// Проверяем все поля с их фактическими категориями после forward.
// Fold по && для пустого пакета равен true: пустая строка допустима.
template<class... Fields,
         std::enable_if_t<(is_insertable<Fields&&>::value && ...), int> = 0>
void print_row(std::ostream& out, Fields&&... fields) {
    detail::print_row_impl(out, std::forward<Fields>(fields)...);
}
} // namespace sfinae
