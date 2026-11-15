#include <iostream>

// Унарная правая свёртка: начального операнда нет.
// Для пустого пакета стандарт задаёт true.
// Представьте проверку: все ли задания студента выполнены? 
// Если хотя бы одно не выполнено, ответ «нет». 
// Если заданий вообще нет, нет ни одного нарушения условия.
template<class... Args>
bool all(Args... args) {
    return (args && ...);
}

// Теперь вопрос иной: выполнил ли студент хотя бы одно задание? 
// Если заданий нет, найти выполненное невозможно.
template<class... Args>
bool any(Args... args) {
    return (args || ...);
}

// static_cast<void> означает: выполнить вывод, но отбросить значение выражения. 
// Здесь это ещё и гарантирует использование встроенной запятой: её операнды имеют тип void.
template<class... Args>
void print_all(Args... args) {
    (static_cast<void>(std::cout << args << ' '), ...);
}

// Бинарная свёртка: начальный операнд остаётся даже без полей.
template<class... Args>
auto sum(Args... args) {
    return (0 + ... + args);
}

// Унарная правая свёртка
// Нет начального операнда => не работает при выхове wrong_sum()
// Почему нет нейтрального элемента 0 по сложению?
// У каждого типа свой нейтральный элемент: int - 0, std::string - std::string{};
// также оператор сложения может быть перегружен
template<class... Args>
auto wrong_sum(Args... args) {
    return (args + ...);
}

template<class... Args>
auto product(Args... args) {
    return (1 * ... * args);
}

int main() 
{
    std::cout << std::boolalpha;

    std::cout << all(true, false) << '\n';
    std::cout << all() << '\n';

    std::cout << any(false, true) << '\n';
    std::cout << any() << '\n';

    std::cout << '[';

    print_all(10, "Hello", 3.14);
    std::cout << "]\n[";
    print_all(); // просто выражение void(), которое корректно и ничего не делает
    std::cout << "]\n";

    std::cout << sum(1, 2, 3) << '\n';
    std::cout << sum() << '\n';

    // std::cout << wrong_sum() << "\n";

    std::cout << product(2, 3, 4) << '\n';
    std::cout << product() << '\n';

    return 0;
}
