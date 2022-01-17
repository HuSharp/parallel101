/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-02 23:37:24
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-16 23:52:43
 * @@Email: 8211180515@csu.edu.cn
 */
#include <iostream>
#include <string>

struct Pig {
    std::string m_name;
    int m_weight{0};

    Pig(std::string name, int weight)
        : m_name(name), m_weight(weight)
    {}

    Pig()
    {}

    Pig(Pig const &other)
        : m_name(other.m_name)
        , m_weight(other.m_weight)
    {}

    Pig &operator=(Pig const &other) {
        m_name = other.m_name;
        m_weight = other.m_weight;
        return *this;
    }

    Pig(Pig &&other)
        : m_name(std::move(other.m_name))
        , m_weight(std::move(other.m_weight))
    {}

    Pig &operator=(Pig &&other) {
        m_name = std::move(other.m_name);
        m_weight = std::move(other.m_weight);
        return *this;
    }

    ~Pig() {}
};

void show(Pig pig) {
    std::cout << "name: " << pig.m_name << std::endl;
    std::cout << "weight: " << pig.m_weight << std::endl;
}

int main() {
    Pig pig1 = {"happy", 70};
    Pig pig = pig1;

    show(pig);
    return 0;
}
