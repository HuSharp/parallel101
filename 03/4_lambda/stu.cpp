/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-24 22:26:40
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-25 12:20:14
 * @@Email: 8211180515@csu.edu.cn
 */
#include <cstdio>

template <typename T>
void call_write(T func) {
    func(0);
    func(1);
}

void print_n(int n) {
    printf("Number: %d\n", n);
}

void print_f(float f) {
    printf("Number: %f\n", f);
}

void lambda_recursion() ;

int main(int argc, char const *argv[])
{
    call_write(print_n);
    call_write(print_f);

    auto myfunc = [] (int n) -> int {
        return n * 2;
    };
    call_write(myfunc);

    lambda_recursion();

    return 0;
}


#include <iostream>
#include <vector>

void lambda() {
    std::vector<int> arr = {1, 4, 2, 8, 5, 7};
    int tofind = 4;
    int index = [&] {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == tofind) {
                return i;
            }
        }
        return -1;
    }();

    auto myfunc = [] (int n) {
        printf("lambda %d \n", n);
    };
}

#include <set>
void lambda_recursion() {
    std::vector<int> arr = {1, 4, 2, 8, 3, 7};
    std::set<int> visited;
    auto dfs = [&] (auto const &dfs, int index) -> void {
        if (visited.find(index) == visited.end()) {
            visited.insert(index);
            std::cout << index << std::endl;
            int next = arr[index];
            dfs(dfs, next);
        }
    };
    dfs(dfs, 0);
}