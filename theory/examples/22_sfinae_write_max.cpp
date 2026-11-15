#include <iostream>
#include <type_traits>
#include <utility>

// Типы результатов проверяемых выражений.
template<class T>
using compare_result = decltype(
    static_cast<bool>(
        std::declval<const T&>() <
        std::declval<const T&>()));

template<class T>
using output_result = decltype(
    std::declval<std::ostream&>() <<
    std::declval<const T&>());

// Проверяем возможность сравнения.
template<class T, class = void>
struct has_less : std::false_type {};

template<class T>
struct has_less<T, std::void_t<compare_result<T>>>
    : std::true_type {};

// Проверяем возможность вывода и его результат.
template<class T, class = void>
struct is_printable : std::false_type {};

template<class T>
struct is_printable<T, std::void_t<output_result<T>>>
    : std::is_same<output_result<T>,
                   std::ostream&> {};

// Для максимума нужны обе операции.
template<class T>
inline constexpr bool can_write_max_v =
    has_less<T>::value && is_printable<T>::value;

// Если условие ложно, нет возвращаемого типа.
template<class T>
std::enable_if_t<can_write_max_v<T>, void>
write_max(std::ostream& out,
          const T& a, const T& b) {
    out << (static_cast<bool>(a < b) ? b : a)
        << '\n';
}

struct Note {};

int main() {
    static_assert(can_write_max_v<int>);
    static_assert(!can_write_max_v<Note>);
    write_max(std::cout, 3, 7);

    // Нет подходящей перегрузки:
    // write_max(std::cout, Note{}, Note{});
}
