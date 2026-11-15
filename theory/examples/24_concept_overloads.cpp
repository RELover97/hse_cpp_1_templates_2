#include <concepts>
#include <iostream>

template<class T>
concept Printable = requires(std::ostream& out,
                             const T& x) {
    { out << x } -> std::same_as<std::ostream&>;
};

template<class T>
concept Comparable = requires(const T& a,
                              const T& b) {
    static_cast<bool>(a < b);
};

template<class T>
concept Rankable = Printable<T> && Comparable<T>;

template<Printable T>
void inspect(const T&) {
    std::cout << "print only\n";
}

template<Rankable T>
void inspect(const T&) {
    std::cout << "print and compare\n";
}

struct Label {};

std::ostream& operator<<(std::ostream& out,
                         const Label&) {
    return out << "label";
}

int main() {
    inspect(Label{});
    inspect(7);
}
