#include "result.hpp"

// Check: https://cppinsights.io

class CompilerGeneratedLambda {
private:
    int a;

public:

    explicit CompilerGeneratedLambda(bool _a)
        : a(_a) {}

    bool operator()(int b, int c) const {
        return a * (b + c);
    }
};


int main()
{
    int a = 1;

    auto lambda = [a](int b, int c) {
        return a * (b + c);
    };
}