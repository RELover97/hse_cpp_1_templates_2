#include <algorithm>
#include <iostream>
#include <vector>

bool cheaper(int a, int b) {
    // true: a должен стоять раньше b.
    return a < b;
}

int main() {
    std::vector<int> prices{300, 100, 200};

    // Передаём правило, а не результат его вызова.
    std::sort(prices.begin(), prices.end(),
              cheaper);

    for (int price : prices) {
        std::cout << price << ' ';
    }
}
