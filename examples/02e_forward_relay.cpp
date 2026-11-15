#include "result.hpp"
#include <algorithm>
#include <iostream>
#include <utility>

struct ByPoints {
    bool operator()(const Result& a, const Result& b) const {
        return a.points > b.points;
    }
};

// Эти перегрузки лишь показывают выбор ссылки; ресурс не перемещается.
void receive(ByPoints&) { 
    std::cout << "lvalue\n"; 
}

void receive(const ByPoints&) 
{ 
    std::cout << "const lvalue\n"; 
}

void receive(ByPoints&&) 
{ 
    std::cout << "rvalue\n"; 
}

template<class Compare>
void relay(Compare&& compare) 
{
    // Выведенный Compare хранит сведения о категории исходного аргумента.
    receive(std::forward<Compare>(compare));
}

int main() 
{
    ByPoints comparator;

    const ByPoints const_comparator;

    relay(comparator);
    relay(const_comparator);
    relay(ByPoints{});
}
