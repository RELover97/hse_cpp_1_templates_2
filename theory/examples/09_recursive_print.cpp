#include <iostream>

// Базовый случай: аргументов больше нет.
void print_all() {
    std::cout << '\n';
}

template<class First, class... Rest>
void print_all(const First& first,
               const Rest&... rest) {
    std::cout << first << ' ';

    // Раскрываем только оставшиеся аргументы.
    print_all(rest...);
}

int main() {
    print_all(1, "Anna", 95);
}
