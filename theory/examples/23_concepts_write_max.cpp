#include <concepts>
#include <iostream>

template<class T>
concept Comparable = requires(const T& a,
                              const T& b) {
    static_cast<bool>(a < b);
};

template<class T>
concept Printable = requires(std::ostream& out,
                             const T& value) {
    { out << value }
        -> std::same_as<std::ostream&>;
};

template<class T>
concept CanWriteMax = Comparable<T> && Printable<T>;

// Требование читается прямо из объявления.
template<CanWriteMax T>
void write_max(std::ostream& out,
               const T& a, const T& b) {
    out << (static_cast<bool>(a < b) ? b : a)
        << '\n';
}

struct Note {};

int main() {
    static_assert(CanWriteMax<int>);
    static_assert(!CanWriteMax<Note>);
    write_max(std::cout, 3, 7);

    // Ограничение не выполнено:
    // write_max(std::cout, Note{}, Note{});
}
