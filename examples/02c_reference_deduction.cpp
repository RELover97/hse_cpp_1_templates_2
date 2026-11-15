#include "result.hpp"
#include <algorithm>
#include <iostream>
#include <type_traits>

struct ByPoints {
    bool operator()(const Result& a, const Result& b) const {
        return a.points > b.points;
    }
};

// Exact deduction can be checked without relying on compiler-specific type names.
template<class T>
void check_lvalue(T&& value) {
    static_assert(std::is_same_v<T, ByPoints&>);
    static_assert(std::is_same_v<decltype(value), ByPoints&>);
    // decltype((value)) means: analyze category of value
    static_assert(std::is_same_v<decltype((value)), ByPoints&>);
}

template<class T>
void check_rvalue(T&& value) {
    static_assert(std::is_same_v<T, ByPoints>);
    static_assert(std::is_same_v<decltype(value), ByPoints&&>);
    // decltype((value)) means: analyze category of value
    static_assert(std::is_same_v<decltype((value)), ByPoints&>);
}

int main() 
{
    ByPoints comparator;

    check_lvalue(comparator);

    check_rvalue(ByPoints{});

    std::cout << "Type checks passed\n";
}
