#include "result.hpp"
#include "unconstrained.hpp"
#include <iostream>
int main() {
    unconstrained::print_ranking(std::cout, std::vector<PrintableOnly>{{1}});
}
