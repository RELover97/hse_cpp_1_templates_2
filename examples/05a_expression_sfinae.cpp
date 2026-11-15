#include "../include/result.hpp"

#include <iostream>


// Expression SFINAE: invalid dependent return type removes the int overload.
// This small probe checks only whether the insertion expression exists.
template<class T>
auto try_print(std::ostream& out, const T& value, int)
    // trailing return type
    // decltype = проверяем тип выражения, не выполняя вывод
    // static_cast<void> отбрасываем результат вывода
    // если выражение корректно, то void; при ошибке кандидат исчезает.
    -> decltype(static_cast<void>(out << value)) {
    out << value;
}


template<class T>
void try_print(std::ostream& out, const T&, long) {
    out << "[not printable]";
}


int main() {
    //  оба кандидата try_print допустимы, но 0 - int => инстанцируется тело первого кандидата
    try_print(std::cout, Result{"Anna", 82}, 0);
    std::cout << '\n';

    // первый кандидат отбрасывается, но второй уже подходит (int -> long)
    // => инстанцируется тело второго кандидата;
    // без SFINAE инстанцировалось бы тело первого кандидата
    // и уже в самом теле выбранной функции возникла бы ошибка компиляции
    try_print(std::cout, ComparableOnly{1}, 0);
    std::cout << '\n';

    return 0;
}
