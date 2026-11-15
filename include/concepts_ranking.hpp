#pragma once
#include "ranking_impl.hpp"
#include <concepts>
#include <utility>

namespace modern {
// Проверяем ровно те же операции, что в C++17: алгоритм не меняется.
// Параметры requires — обозначения для выражений, не реальные объекты.
template<class T>
concept Comparable = requires(const T& a, const T& b) {
    // Скобки и стрелка: выражение допустимо, его тип — точно bool.
    // После static_cast проверка типа избыточна, но показывает синтаксис.
    { static_cast<bool>(a < b) } -> std::same_as<bool>;
};

template<class Expr>
concept Insertable = requires(std::ostream& out, Expr&& value) {
    // Имя value — lvalue, даже если его тип Expr&&.
    // forward моделирует ту категорию, с которой поле реально выводится.
    { out << std::forward<Expr>(value) } -> std::same_as<std::ostream&>;
};

template<class T>
concept Printable = Insertable<const T&>;

template<class T>
concept Rankable = Comparable<T> && Printable<T>;

// A constrained type parameter abbreviates template<class T> requires Rankable<T>.
template<Rankable T>
void print_ranking(std::ostream& out, const std::vector<T>& rows) {
    detail::print_ranking_impl(out, rows);
}

template<class... Fields>
    // Каждый элемент должен быть печатаем; пустой пакет даёт true.
    requires (Insertable<Fields&&> && ...)
void print_row(std::ostream& out, Fields&&... fields) {
    detail::print_row_impl(out, std::forward<Fields>(fields)...);
}

// Optional diagnostics illustrate constraint-based overload ordering.
// Rankable explicitly includes Printable, so the second overload is more constrained.
template<Printable T>
constexpr const char* capability(const T&) { return "printable"; }
template<Rankable T>
constexpr const char* capability(const T&) { return "rankable"; }
} // namespace modern
