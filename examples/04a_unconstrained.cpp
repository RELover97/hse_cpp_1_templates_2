#include "../include/result.hpp"

#include <iostream>

template<class... Fields>
void print_row_impl(std::ostream& out, Fields&&... fields) {
    // Состояние одной строки: перед первым полем разделитель не нужен.
    bool first = true;
    // [&] позволяет менять first и писать в тот же поток.
    // generic lambda выводит тип отдельно для каждого поля.
    // При пустом пакете emit не вызывается: maybe_unused убирает предупреждение.
    [[maybe_unused]] auto emit = [&](auto&& field) {
        if (!first) {
            out << " | ";
        }
        // decltype(field) is the declared parameter type, including its reference.
        out << std::forward<decltype(field)>(field);
        first = false;
    };
    // Унарная правая свёртка: emit возвращает void, поэтому запятая встроенная.
    // Для трёх полей: emit(f1), (emit(f2), emit(f3)).
    // Для нуля полей: void(). Перевод строки после свёртки остаётся.
    (emit(std::forward<Fields>(fields)), ...);
    out << '\n';
}


// This helper implements the shared algorithm.
// Sort indices instead of objects: the original vector is never modified or copied.
template<class T>
void print_ranking_impl(std::ostream& out, const std::vector<T>& rows) {
    // Сортируем не объекты, а номера строк: T не обязан копироваться.
    std::vector<std::size_t> order(rows.size());
    // Заполняем индексы: 0, 1, 2, ...
    for (size_t i = 0; i < order.size(); ++i) {
        order[i] = i;
    }

    // сортируем по убыванию
    std::stable_sort(order.begin(), order.end(), [&rows](std::size_t a, std::size_t b) {
        // Bind const references explicitly, even for vector<bool>'s value return.
        const T& left = rows[a];
        const T& right = rows[b];
        // Reverse the natural ordering without requiring operator>.
        return static_cast<bool>(right < left);
    });

    // Теперь читаем исходный вектор в порядке отсортированных индексов.
    std::size_t place = 1;
    for (const auto index : order) {
        const T& row = rows[index];
        print_row_impl(out, place, row);
        ++place;
    }
}


// This public API of printer should check the input type T
template<class T>
void print_ranking(std::ostream& out, const std::vector<T>& rows) {
    print_ranking_impl(out, rows);
    std::cout << "\n";
}

// Three intentionally different capabilities for compile-time examples.

// 1. Printable but not comparable type

struct PrintableOnly { int value; };

inline std::ostream& operator<<(std::ostream& out, const PrintableOnly& x) {
    return out << x.value;
}

// 2. Comparable but not printable type

struct ComparableOnly { int value; };
inline bool operator<(const ComparableOnly& a, const ComparableOnly& b) {
    return a.value < b.value;
}

// 3. Neither comparable nor prinrable type

struct Neither {};

int main() {
    print_ranking(std::cout, sample_results());
    print_ranking(std::cout, std::vector<int>{3, 8, 1});
    print_ranking(std::cout, std::vector<std::string>{"A", "C", "B"});

    // Uncommenting either line fails inside the implementation

    // print_ranking(std::cout, std::vector<PrintableOnly>{{1}});
    // print_ranking(std::cout, std::vector<ComparableOnly>{{1}});
    // print_ranking(std::cout, std::vector<Neither>{});
}