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

int main() 
{
    ByPoints comparator;
    const ByPoints const_comparator;

    receive(comparator);       // lvalue
    receive(const_comparator); // const lvalue
    receive(ByPoints{});       // rvalue
}
