#include <iostream>
#include <string>
#include <utility>

void receive(const std::string&) {
    std::cout << "read/copy\n";
}

void receive(std::string&&) {
    std::cout << "can move\n";
}

template<class T>
void bad_relay(T&& x) {
    // Ошибка: x всегда lvalue-выражение.
    receive(x);
}

template<class T>
void relay(T&& x) {
    // Восстанавливаем категорию по T.
    receive(std::forward<T>(x));
}

int main() {
    std::string s = "hello";
    bad_relay(std::string{"temp"});
    relay(s);
    relay(std::string{"temp"});
}
