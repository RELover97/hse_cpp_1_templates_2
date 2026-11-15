#pragma once
#include <ostream>
#include <utility>

namespace detail {
// Each argument has its own deduced type and reference category.
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

} // namespace detail
