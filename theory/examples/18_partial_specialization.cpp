#include <type_traits>

template<class T>
struct is_pointer_like : std::false_type {};

template<class U>
struct is_pointer_like<U*> : std::true_type {};

int main() {
    static_assert(is_pointer_like<int*>::value);
    static_assert(is_pointer_like<double*>::value);
    static_assert(!is_pointer_like<int>::value);
}
