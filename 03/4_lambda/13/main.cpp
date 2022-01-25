#include <iostream>
#include <functional>
#include "lambda.h"

std::function<int(int)> make_twice(int fac) {
    return [=] (int n) {
        return n * fac;
    };
}

int main() {
    auto twice = make_twice(2);
    call_twice(twice);
    return 0;
}
