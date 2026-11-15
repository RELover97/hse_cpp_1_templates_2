#pragma once
#include "ranking_impl.hpp"

namespace unconstrained {
// Nothing in the declaration tells overload resolution which T is supported.
template<class T>
void print_ranking(std::ostream& out, const std::vector<T>& rows) {
    detail::print_ranking_impl(out, rows);
}

}
