#include "result.hpp"
#include "sfinae.hpp"
#include <iostream>
int main() {
    sfinae::print_ranking(std::cout, std::vector<PrintableOnly>{{1}});
}
