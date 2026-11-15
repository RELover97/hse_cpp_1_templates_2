#include <functional>
#include <iostream>

bool compare_price(int a, int b,
                   bool ascending) {
    return ascending ? a < b : a > b;
}

int main() {
    using namespace std::placeholders;

    auto rule = std::bind(compare_price,
                          _1, _2, true);

    std::cout << rule(100, 300) << '\n';
}
