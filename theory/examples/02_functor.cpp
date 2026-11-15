#include <iostream>

struct PriceOrder {
    bool ascending;

    bool operator()(int a, int b) const {
        return ascending ? a < b : a > b;
    }
};

int main() {
    PriceOrder cheap_first{true};
    PriceOrder expensive_first{false};

    std::cout << cheap_first(100, 300)
              << '\n';
    std::cout << expensive_first(100, 300)
              << '\n';
}
