#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::string> queue;

void enqueue(const std::string& text) {
    // Копируем: источник остаётся прежним.
    queue.push_back(text);
    std::cout << "copy\n";
}

void enqueue(std::string&& text) {
    // text по имени — lvalue.
    // Явно разрешаем move для push_back.
    queue.push_back(std::move(text));
    std::cout << "move\n";
}

int main() {
    std::string message = "Hello";
    enqueue(message);
    enqueue(std::string{"Temporary"});
    enqueue(std::move(message));
}
