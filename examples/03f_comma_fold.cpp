#include <iostream>
#include <utility>

template<class Field>
void emit(Field&& field) {
    std::cout << std::forward<Field>(field) << '\n';
}
template<class... Fields>
void emit_all(Fields&&... fields) 
{
    // emit возвращает void: используется встроенная запятая.
    // Для трёх полей: emit(f1), (emit(f2), emit(f3)).
    // Это унарная правая свёртка:
    // унарная = имеется только выражение с пакетом, без дополнительного начального операнда
    // правая = вложенность скобок справа
    (emit(std::forward<Fields>(fields)), ...);
}
int main() {
    emit_all(1, "Anna", 82);
    emit_all(); // Пустая свёртка по запятой ничего не делает.
}
