#include <type_traits>
#include <utility>

template<class T>
void inspect(T&& x) {
    // decltype(x) — объявленный тип x.
    static_assert(
        std::is_same_v<decltype(x), T&&>);

    // (x) — выражение, и оно lvalue.
    static_assert(
        std::is_lvalue_reference_v<
            decltype((x))>);
}

int main() {
    int a = 5;
    const int c = 7;
    inspect(a);
    inspect(c);
    inspect(42);
    inspect(std::move(a));
}
