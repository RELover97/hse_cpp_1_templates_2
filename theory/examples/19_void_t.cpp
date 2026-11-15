#include <type_traits>

template<class... Ts>
using my_void_t = void;

int main() {
    static_assert(std::is_same_v<
        my_void_t<int, double>, void>);
    static_assert(std::is_same_v<
        my_void_t<>, void>);
}
