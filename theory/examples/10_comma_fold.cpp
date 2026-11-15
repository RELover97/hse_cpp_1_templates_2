#include <iostream>

template<class... Ts>
void print_all(const Ts&... xs) {
    // Одна операция вывода для каждого xs.
    ((std::cout << xs << ' '), ...);
    std::cout << '\n';
}

int main() {
    print_all(1, "Anna", 95);
    print_all();
}
