#include "result.hpp"
#include "sfinae.hpp"
#include <iostream>

#include <sstream>
#include <stdexcept>

int main() {
    std::ostringstream out;
    sfinae::print_ranking(out, sample_results());
    if (out.str() != "1 | Boris (95)\n2 | Daria (95)\n3 | Anna (82)\n4 | Ivan (71)\n") {
        throw std::runtime_error("unexpected ranking");
    }
}
