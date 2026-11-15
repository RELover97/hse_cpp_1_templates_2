#include <iostream>
#include <type_traits>

/*
1. T&& 
    => reference collapsing applied 
    => save value category (see main)
2. static_cast<T&&>(x)
    T - lvalue reference => return lvalue reference
    T - rvalue => return rvalue reference
    то есть мы можем обращаться к существующему объекту через выражение нужной категории
*/
template<class T>
T&& my_forward(std::remove_reference_t<T>& x) noexcept {
    return static_cast<T&&>(x);
}


template<class T>
T&& wrong_my_forward(T&& x) noexcept {
    return static_cast<T&&>(x);
}

// as in std library

template<class T>
constexpr T&& forward(std::remove_reference_t<T>& x) noexcept;

template<class T>
constexpr T&& forward(std::remove_reference_t<T>&& x) noexcept;

// receivers

void process(int&) {
    std::cout << "lvalue\n";
}

void process(int&&) {
    std::cout << "rvalue\n";
}

template<class T>
void wrapper(T&& x) {
    process(my_forward<T>(x));
}


// Does not work for wrong_wrapper(20);
template<class T>
void wrong_wrapper(T&& x) {
    wrong_my_forward<T>(x);
}

int main() 
{
    int a = 10;

    // 1) T = int&
    // 2) int& x
    // 3) my_forward<int&>(x)
    // 4) static_cast<int&>(x);
    // 5) process(int&)
    wrapper(a);   // lvalue
    // 1) T = int
    // 2) int&& x
    // 3) x - lvalue!
    // 4) my_forward<int>(x)
    // 5) static_cast<int&&>(x)
    // 6) process(int&&)
    wrapper(20);  // rvalue

    // 1. why T&&: restore value category
    my_forward<int&>(a); // return lvalue reference
    my_forward<int>(a); // return rvalue reference

    // CE: int& cannot accept rvalue
    // solution: add overload for
    // std::remove_reference_t<T>&& x
    // my_forward<int>(42); 
    
    // T = int
    // => wrong_my_forward<T>(x) waits for T&&
    // but x is lvalue! => cannot transfer x to
    // function waiting for T&&
    // Correct: use lvalue reference
    // std::remove_reference_t<T>& x:
    // T = int& => std::remove_reference_t<T> is T => T& x => return T& 
    // T = int  => std::remove_reference_t<T> is T => T& x => return T&&
    
    // wrong_wrapper(20);
}