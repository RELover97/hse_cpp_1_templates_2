#include <memory>
#include <string>
#include <utility>
#include <vector>

template<class T, class... Args>
std::unique_ptr<T> make_object(Args&&... args) {
    // Каждый аргумент передаём с его типом.
    return std::make_unique<T>(
        std::forward<Args>(args)...);
}

int main() 
{
    auto s = make_object<std::string>(3, 'x');
    auto v = make_object<std::vector<int>>(3, 2);

    return 0;
}
