/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-02 23:37:24
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-16 23:24:23
 * @@Email: 8211180515@csu.edu.cn
 */
#include <iostream>
#include <string>

struct Pig {
    std::string m_name;
    int m_weight = 0;
};

void show(Pig pig) {
    std::cout << "name: " << pig.m_name << std::endl;
    std::cout << "weight: " << pig.m_weight << std::endl;
}

int main() {
    Pig pig = {"aaa", 100};
    Pig pig2 = {"aaa", 100};

    show(pig);
    return 0;
}
