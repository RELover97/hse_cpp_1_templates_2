#include <iostream>

int main() 
{
    int x = 0;
    // Запятая вычисляет левый операнд, затем правый.
    int result = (x = 10, x = 20, x + 5);
    std::cout << "x = " << x << ", result = " << result << '\n';
}
