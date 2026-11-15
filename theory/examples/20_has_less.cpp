#include <type_traits>
#include <utility>

// По умолчанию сравнение недоступно.
template<class T, class = void>
struct has_less : std::false_type {};

// Специализация доступна, только если
// можно сформировать второй аргумент.
template<class T>
struct has_less<T, std::void_t<
    decltype(static_cast<bool>(
        std::declval<const T&>() <
        std::declval<const T&>()
    ))
>> : std::true_type {};

struct Note {};

int main() {
    static_assert(has_less<int>::value);
    static_assert(!has_less<Note>::value);
}
