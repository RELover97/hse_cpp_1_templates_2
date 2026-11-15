#include "result.hpp"
#include "concepts_ranking.hpp"
#include <iostream>

int main() {
    // requires с && проверяет каждый элемент пакета.
    modern::print_row(std::cout, "Place", "Result");
    modern::print_row(std::cout, 1, Result{"Anna", 82});
    modern::print_row(std::cout);
}
