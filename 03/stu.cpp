/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-24 10:33:21
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-24 21:36:21
 * @@Email: 8211180515@csu.edu.cn
 */
#include <vector>
#include <iostream>

template <typename T>
void print(std::vector<T> const &a) {
    std::cout << "{" ;
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i];
        if (i != a.size() - 1) 
            std::cout << ",";
    }
    std::cout << "}" << std::endl;
}

template <typename T> 
std::ostream &operator<<(std::ostream &os, std::vector<T> const &a) {
    os << __PRETTY_FUNCTION__ << std::endl;
    os << "{";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i];
        if (i != a.size() - 1) 
            std::cout << ",";
    }
    os << "}";
    return os;
}

#include <iostream>
#include <type_traits>
int main(int argc, char const *argv[]) {
    std::vector<int> a = {1, 2, 3, 4, 6};
    std::cout << a << std::endl;
    std::vector<float> b = {3.12, 4.65, 3.29};
    print(b);

    std::cout << std::is_same<int const, const int>::value << std::endl; 

    return 0;
}
