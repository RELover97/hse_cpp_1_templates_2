#include <type_traits>
#include <utility>

struct Score {
    explicit Score(int n) : points(n) {}
    int points;
};

bool operator<(const Score& a,
               const Score& b) {
    return a.points < b.points;
}

/*
Мы хотим проверить допустимость операции сравнения объектов, не создавая объекты непосредственно.
То есть мы моделируем саму операцию в невычислимом контексте.

Писать T{} < T{} не подходит: это дополнительно требует возможность 
создания временных объектов по умолчанию и проверяет другие категории выражений.

std::declval позволяет сформировать выражение нужного типа в невычисляемом контексте. 

Реальный объект не создаётся, declval нельзя вызывать для выполнения во время работы программы.

1) проверка допустимости операции < для двух типов
2) decltype даёт тип bool
*/

template<class T>
using less_result = decltype(
    std::declval<const T&>() <
    std::declval<const T&>());

int main() {
    static_assert(std::is_same_v<
        less_result<Score>, bool>);
}
