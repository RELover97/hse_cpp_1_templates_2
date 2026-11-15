#include "result.hpp"
#include <iostream>
#include <string_view>
#include <utility>

#include "report_row.hpp"

template<class... Fields>
void print_row(std::ostream& out, Fields&&... fields) 
{
    // Раскрываем пакет в список: forward<F1>(f1), forward<F2>(f2), ...
    // Каждый тип соответствует своему аргументу.
    detail::print_row_impl(out, std::forward<Fields>(fields)...);
}

int main() 
{
    auto rows = sample_results();
    print_row(std::cout, "Place", "Name", "Points");
    std::size_t place = 1;

    for (const auto& row : rows) {
        print_row(std::cout, place, row.name, row.points);
        ++place;
    }

    // Optional extra field; no new overload is necessary.
    print_row(std::cout, "Total", rows.size(), std::string_view{"participants"}, true);
    print_row(std::cout, "End of report");
    print_row(std::cout); // A blank line is defined for the empty pack.
}
