#include <iostream>
#include <string>

template<class T>
void write_max(std::ostream& out,
               const T& a, const T& b) {
    // Выбираем большее, затем выводим.
    out << (a < b ? b : a) << '\n';
}

int main() {
    write_max(std::cout, 3, 7);
    write_max(std::cout, std::string{"A"},
                        std::string{"B"});
}
