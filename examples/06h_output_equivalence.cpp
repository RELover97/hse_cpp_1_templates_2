#include "result.hpp"
#include "concepts_ranking.hpp"
#include <iostream>

#include "sfinae.hpp"
#include <sstream>
#include <stdexcept>

int main() {
    std::ostringstream old_out, new_out;
    sfinae::print_ranking(old_out, sample_results());
    modern::print_ranking(new_out, sample_results());
    if (old_out.str() != new_out.str()) {
        throw std::runtime_error("migration changed output");
    }
}
