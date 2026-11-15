#include <iostream>
#include <utility>

void receive(int place, const char* name, int points) 
{
    std::cout << place << " | " << name << " | " << points << '\n';
}

template<class... Fields>
void relay(Fields&&... fields) {
    // Раскрываем пакет в список аргументов одного вызова, не в цикл.
    receive(std::forward<Fields>(fields)...);
}

int main() 
{
    relay(1, "Anna", 82);
}
