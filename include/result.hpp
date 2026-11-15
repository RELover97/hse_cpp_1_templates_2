#pragma once
#include <ostream>
#include <string>
#include <vector>

// A competition result. Natural ordering means ordering by points, not by name.
struct Result {
    std::string name;
    int points;
};

inline bool operator<(const Result& a, const Result& b) {
    return a.points < b.points;
}

// Returning the same stream makes chaining (out << value << '\n') possible.
inline std::ostream& operator<<(std::ostream& out, const Result& value) {
    return out << value.name << " (" << value.points << ')';
}

inline std::vector<Result> sample_results() {
    return {{"Anna", 82}, {"Boris", 95}, {"Daria", 95}, {"Ivan", 71}};
}

// Three intentionally different capabilities for compile-time examples.

// 1. Printable but not comparable type

struct PrintableOnly { int value; };

inline std::ostream& operator<<(std::ostream& out, const PrintableOnly& x) {
    return out << x.value;
}

// 2. Comparable but not printable type

struct ComparableOnly { int value; };
inline bool operator<(const ComparableOnly& a, const ComparableOnly& b) {
    return a.value < b.value;
}

// 3. Neither comparable nor prinrable type

struct Neither {};
