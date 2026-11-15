#include "result.hpp"
#include "concepts_ranking.hpp"
#include <iostream>

int main() {
    // Rankable включает Printable; для Result выбирается более строгое ограничение.
    std::cout << modern::capability(PrintableOnly{1}) << '\n';
    std::cout << modern::capability(Result{"Anna", 82}) << '\n';
}
