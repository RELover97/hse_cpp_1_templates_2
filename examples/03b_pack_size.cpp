#include <cstddef>
#include <iostream>

// class... Fields - пакет типов
// Fields&&... - пакет аргументов
// Каждый аргумент выводится независимо по правилам forwarding reference
template<class... Fields>
constexpr std::size_t field_count(Fields&&...) 
{
    // Число типов, а не размер памяти. У каждого аргумента свой тип.
    return sizeof...(Fields);
}

int main() 
{
    std::cout << field_count(1, "Anna", 82) << '\n';
    std::cout << field_count() << '\n';
}
