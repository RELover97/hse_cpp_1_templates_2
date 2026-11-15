#include "result.hpp"
#include <algorithm>
#include <iostream>

struct ByPoints {
    bool operator()(const Result& a, const Result& b) const {
        return a.points > b.points;
    }
};
// Эти перегрузки лишь показывают выбор ссылки; ресурс не перемещается.
void receive(ByPoints&) 
{ 
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

// universal reference
template<class Compare>
void bad_relay(Compare&& compare) 
{
    // Имя параметра compare — lvalue, даже если тип параметра ByPoints&&.
    receive(compare);
}

int main() 
{
    ByPoints comparator;
    const ByPoints const_comparator;

    bad_relay(comparator); // (1)
    bad_relay(const_comparator); // (2)
    // (3)
    bad_relay(ByPoints{}); // Ожидаем rvalue, но получаем lvalue.
}
