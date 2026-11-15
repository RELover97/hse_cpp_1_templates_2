#include <type_traits>

int main() {
    int x = 5;
    using A = decltype();
    using B = decltype(x + 1);
    using C = decltype(x < 10);

    static_assert(std::is_same_v<A, int>);
    static_assert(std::is_same_v<B, int>);
    static_assert(std::is_same_v<C, bool>);
}
