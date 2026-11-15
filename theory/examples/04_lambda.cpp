#include <iostream>

bool compare_price(int a, int b,
                   bool ascending) {
    return ascending ? a < b : a > b;
}

int main() {
    bool ascending = true;

    auto rule = [ascending](int a, int b) {
        return compare_price(a, b, ascending);
    };

    ascending = false;

    // Внутри rule сохранена копия true.
    std::cout << rule(100, 300) << '\n';
}
