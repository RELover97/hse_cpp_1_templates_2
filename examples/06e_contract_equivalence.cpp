#include "result.hpp"
#include "concepts_ranking.hpp"
#include "sfinae.hpp"
#include <iostream>

template<class T>
concept CanRank = requires(std::ostream& out, const std::vector<T>& rows) {
    modern::print_ranking(out, rows);
};

template<class... Ts>
concept CanPrintRow = requires(std::ostream& out, Ts&&... args) {
    modern::print_row(out, std::forward<Ts>(args)...);
};

// Verify that migration changes syntax and diagnostics, not accepted types.
template<class... Ts>
constexpr bool same_contract = ((modern::Rankable<Ts> == sfinae::is_rankable_v<Ts>) && ...);
static_assert(same_contract<Result, int, std::string, bool, PrintableOnly, ComparableOnly, Neither>);
static_assert(CanRank<Result> && CanRank<int> && CanRank<std::string> && CanRank<bool>);
static_assert(!CanRank<PrintableOnly> && !CanRank<ComparableOnly> && !CanRank<Neither>);
static_assert(CanPrintRow<> && CanPrintRow<int, const std::string&>);
static_assert(!CanPrintRow<int, ComparableOnly>);

int main() {
    std::cout << "SFINAE and concepts accept the same tested types\n";
}
