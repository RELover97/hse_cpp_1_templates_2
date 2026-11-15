#include "../include/result.hpp"
#include <iostream>

// Expr сохраняет ссылку и const, чтобы проверять именно будущий вывод.
// При успехе is_same дополнительно проверяет возвращаемый тип потока.
template<class Expr, class = void>
struct is_insertable : std::false_type {};

/*
 Важно отбросить такой вариант:
 
 struct Person {};

  // Оператор ничего не возвращает.
  void operator<<(std::ostream& out,
                const Person&) {
      out << "Person";
  }

  std::cout << person << '\n';  // не скомпилируется

Для этого мы наследуемся от std::is_same, который раскроется либо в std::true_type.
либо в std::false_type
*/
template<class Expr>
struct is_insertable<
    Expr, 
    std::void_t<decltype(
                std::declval<std::ostream&>() << std::declval<Expr>())
                >
    >
    : std::is_same<
        decltype(std::declval<std::ostream&>() << std::declval<Expr>()),
        std::ostream&
    > {};


/*
 Мы хотим проверить:
 1) оператор << вывода в поток определён для типа
 2) он возвращает объект типа std::ostream&
 3) каким образом передаётся объект: как lvalue ссылка, const lvalue ссылка, rvalue ссылка
*/
template<class T>
inline constexpr bool is_printable_v = is_insertable<const T&>::value;


int main() 
{
    // Печатаемость не требует, чтобы тип поддерживал сравнение.
    std::cout << std::boolalpha;

    std::cout << is_printable_v<Result> << '\n';
    std::cout << is_printable_v<PrintableOnly> << '\n';
    std::cout << is_printable_v<ComparableOnly> << '\n';
}
