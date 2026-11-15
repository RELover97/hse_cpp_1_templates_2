#include "../include/result.hpp"
#include <iostream>

// Запрос is_comparable<T> означает is_comparable<T, void>.
// void - обычный параметр без имени с умолчанием void
// он играет вспомогательную роль, чтобы компилятор с помощью него
// проверил допустимые операции над основным параметром T
// То есть все типы по умолчанию несравнимы
template<class T, class = void>
struct is_comparable : std::false_type {};

// Нужен специальный вариант для сравнимых типов
// Этот вариант должен походить к форме <T, void> выше,
// только когда проверка сравнения выполнена успешно
// decltype с выражением проверки сравнения как в try_print
// вернёт bool, а запрашиваемый у нас аргумент - void
// То есть нужен переход от успешно сформированного типа
// к типу void; это делает std::void_t (C++17)

// template<class... Ts>
// using void_t = void;

// void_t<int, double> -> void
// void_t<int> -> void
// void_t<> -> void
// void_t<несуществующий тип> нельзя сформировать; тут
// несуществующий тип будет означать невозможность выполнить
// операцию сравнения для несравнимых типов

// можно использовать и другой тип: class = int
// написать для этого
// template<class...>
// using to_int<T> = int;
// просто std::void_t уже поставляется стандартной библиотекой

// Частичную специализацию мы хотим применять только для сравнимых типов
// declval моделирует const lvalue без создания объекта.
// Если сравнение допустимо, decltype даёт bool, void_t превращает его в void.
// Тогда частичная специализация соответствует <T, void>, value == true.
template<class T>
struct is_comparable<T, std::void_t<
    decltype(static_cast<bool>(
        std::declval<const T&>() < std::declval<const T&>()))
    >> : std::true_type {};


int main() {
    // Проверяем именно наличие сравнения, а не потокового вывода.
    std::cout << std::boolalpha;

    /*
        <Result, void> 
        -> try operator< (ok!)
        -> decltype gives bool
        -> void_t<bool> gives void
        -> partial specialization is taken
        -> value is true
    */
    std::cout << is_comparable<Result>::value << '\n';
    
    /*
        <PrintableOnly, void>
        -> try operator< (fail!)
        -> not choose partial specialization
        -> value is false
    */
    std::cout << is_comparable<PrintableOnly>::value << '\n';
    std::cout << is_comparable<ComparableOnly>::value << '\n';
}
