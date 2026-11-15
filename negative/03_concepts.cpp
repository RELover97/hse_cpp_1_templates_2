#include "result.hpp"
#include "concepts_ranking.hpp"
#include <iostream>
int main() {
    modern::print_ranking(std::cout, std::vector<PrintableOnly>{{1}});
}
