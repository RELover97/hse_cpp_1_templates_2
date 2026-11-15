#include <iostream>
#include <utility>

// Базовый случай: больше нет полей для вывода.
void emit_all() {}

template<class First, class... Rest>
void emit_all(First&& first, Rest&&... rest) 
{
    // Печатаем одно поле и передаём только оставшиеся поля.
    std::cout << std::forward<First>(first) << '\n';
    emit_all(std::forward<Rest>(rest)...);
}

int main() {
    emit_all(1, "Anna", 82);
}
