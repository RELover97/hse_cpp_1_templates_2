#include <type_traits>

template<bool B, class T = void>
struct my_enable_if {};

template<class T>
struct my_enable_if<true, T> {
    using type = T;
};

int main() {
    using A = my_enable_if<true, int>::type;
    static_assert(std::is_same_v<A, int>);

    // Ошибка, если раскомментировать:
    // using B = my_enable_if<false, int>::type;
}
