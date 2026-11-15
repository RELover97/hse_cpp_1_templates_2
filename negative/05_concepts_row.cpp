#include "result.hpp"
#include "concepts_ranking.hpp"
#include <iostream>
int main() {
    modern::print_row(std::cout, "Result", ComparableOnly{1});
}
