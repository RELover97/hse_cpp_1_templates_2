#include <iostream>

struct Note {};

// Основная перегрузка: сравнение доступно.
template<class T>
auto inspect(const T& a, const T& b, int)
    -> decltype(static_cast<bool>(a < b), void()) {
    std::cout << (static_cast<bool>(a < b)
                  ? "a is less" : "not less")
              << '\n';
}

// Запасная перегрузка.
template<class T>
void inspect(const T&, const T&, long) {
    std::cout << "not comparable\n";
}

int main() {
    inspect(3, 7, 0);
    inspect(Note{}, Note{}, 0);
}
