/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-02 23:37:24
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-24 23:43:06
 * @@Email: 8211180515@csu.edu.cn
 */
#include <iostream>
#include <functional>

void call_twice(auto const &func) {
    std::cout << func(3.14f) << std::endl;
    std::cout << func(21) << std::endl;
}

int main() {
    auto twice = [] (auto n) {
        return n * 2;
    };
    call_twice(twice);
    return 0;
}

/* 等价于：
auto twice(auto n) {
    return n * 2;
}
*/
