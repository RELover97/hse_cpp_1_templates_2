#include "result.hpp"
#include "concepts_ranking.hpp"
#include <iostream>

int main() {
    // Concept — именованное логическое условие, не функция.
    std::cout << std::boolalpha;
    std::cout << "Comparable<ComparableOnly>: " << modern::Comparable<ComparableOnly> << '\n';
    std::cout << "Printable<ComparableOnly>: " << modern::Printable<ComparableOnly> << '\n';
    std::cout << "Rankable<Result>: " << modern::Rankable<Result> << '\n';
}
