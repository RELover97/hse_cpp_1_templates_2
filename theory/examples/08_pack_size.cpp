#include <iostream>

template<class... Ts>
void count(const Ts&... xs) {
    // Число параметров функции.
    std::cout << sizeof...(xs) << '\n';
}

int main() {
    count(1, 2.5, "Anna");
    count(42);
    count();
}
