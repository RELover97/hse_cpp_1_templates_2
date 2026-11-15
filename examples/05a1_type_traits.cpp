#include <type_traits>

// Как проверить свойство конкретного типа
template <class T>
struct is_int : std::false_type
{
};

template <>
struct is_int<int> : std::true_type
{
};

// Как проверить свойство семейства типа

template <class T>
struct is_pointer_like : std::false_type
{
};

template <class U>
struct is_pointer_like<U *> : std::true_type
{
};

int main()
{
    static_assert(is_int<int>::value);
    static_assert(!is_int<double>::value);

    static_assert(is_pointer_like<int *>::value);
    static_assert(is_pointer_like<double *>::value);
    static_assert(!is_pointer_like<int>::value);
}
