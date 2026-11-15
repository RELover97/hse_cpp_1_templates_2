#include <iostream>
#include <string>

// Подходит только для фиксированной строки участника.
void print_row(std::ostream& out, int place, const std::string& name, int points) {
    out << place << " | " << name << " | " << points << '\n';
}

int main() 
{
    print_row(std::cout, 1, "Anna", 82);
    // Заголовок с тремя строками и итог с четырьмя полями не подходят.
}
