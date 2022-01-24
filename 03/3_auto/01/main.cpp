#include <cstdio>
#include <memory>

struct MyClassWithVeryLongName {
};

auto func() {
    return std::make_shared<MyClassWithVeryLongName>();
}

int main() {
    auto p = func();
    auto a_name = std::make_shared<MyClassWithVeryLongName>();
    std::shared_ptr<MyClassWithVeryLongName> long_name = std::make_shared<MyClassWithVeryLongName>();
}
