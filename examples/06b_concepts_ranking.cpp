#include "result.hpp"
#include "concepts_ranking.hpp"
#include <iostream>

int main() {
    // Ограничение проверяется до компиляции тела print_ranking.
    modern::print_ranking(std::cout, sample_results());
    modern::print_ranking(std::cout, std::vector<int>{3, 8, 1});
    modern::print_ranking(std::cout, std::vector<std::string>{"A", "C", "B"});
}
