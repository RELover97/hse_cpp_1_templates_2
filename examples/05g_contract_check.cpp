#include "result.hpp"
#include "sfinae.hpp"
#include "unconstrained.hpp"
#include <iostream>

// Test the public signature in an unevaluated context, without instantiating its body.
template<class T, class = void>
struct can_rank : std::false_type {};
template<class T>
struct can_rank<T, std::void_t<decltype(sfinae::print_ranking(
    std::declval<std::ostream&>(), std::declval<const std::vector<T>&>()))>>
    : std::true_type {};

template<class T, class = void>
struct unconstrained_can_rank : std::false_type {};
template<class T>
struct unconstrained_can_rank<T, std::void_t<decltype(unconstrained::print_ranking(
    std::declval<std::ostream&>(), std::declval<const std::vector<T>&>()))>>
    : std::true_type {};

static_assert(sfinae::is_comparable<Result>::value);
static_assert(sfinae::is_printable_v<PrintableOnly>);
static_assert(!sfinae::is_comparable<PrintableOnly>::value);
static_assert(sfinae::is_comparable<ComparableOnly>::value);
static_assert(!sfinae::is_printable_v<ComparableOnly>);
static_assert(can_rank<Result>::value && can_rank<int>::value);
static_assert(can_rank<std::string>::value && can_rank<bool>::value);
static_assert(!can_rank<PrintableOnly>::value && !can_rank<ComparableOnly>::value);
static_assert(!can_rank<Neither>::value);
// Signature alone wrongly accepts this type in the unconstrained version.
static_assert(unconstrained_can_rank<Neither>::value);

int main() {
    std::cout << std::boolalpha;
    std::cout << "unconstrained Neither: " << unconstrained_can_rank<Neither>::value << '\n';
    std::cout << "sfinae Neither: " << can_rank<Neither>::value << '\n';
}
