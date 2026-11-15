#include <vector>
#include <algorithm>
#include <iostream>

// A competition result. Natural ordering means ordering by points, not by name.
struct Result {
    std::string name;
    int points;
};

// Returning the same stream makes chaining (out << value << '\n') possible.
std::ostream& operator<<(std::ostream& out, const Result& value) {
    return out << value.name << " (" << value.points << ')';
}

std::vector<Result> sample_results() {
    return {{"Anna", 82}, {"Boris", 95}, {"Daria", 95}, {"Ivan", 71}};
}

// true: a должно стоять раньше b. Равные баллы не сравниваются строго.
bool higher_score(const Result& a, const Result& b) {
    return a.points > b.points;
}

int main() {
    auto rows = sample_results();
    // Алгоритм вызывает правило с двумя элементами.
    std::stable_sort(rows.begin(), rows.end(), higher_score);
    for (const auto& row : rows) {
        std::cout << row << '\n';
    }
}
