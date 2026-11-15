#include "result.hpp"
#include "concepts_ranking.hpp"
#include <iostream>

int main() {
    // const vector<bool> возвращает bool по значению, а не const bool&.
    modern::print_ranking(std::cout, std::vector<bool>{false, true});
}
