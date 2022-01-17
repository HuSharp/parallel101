/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-17 23:24:24
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-17 23:58:01
 * @@Email: 8211180515@csu.edu.cn
 */
#include <stdio.h>
#include <stdlib.h>

struct Vector2 {
    size_t m_size;
    int* m_data;

    Vector2(size_t n) {
        m_size = n;
        m_data = (int*)malloc(n * sizeof(int));
    }
    ~Vector2() {
        free(m_data);
    }
    size_t size() {
        return m_size;
    }

    void resize(size_t size) {
        m_size = size;
        m_data = (int*)realloc(m_data, m_size);
    }

    int &operator[](size_t index) {
        return m_data[index];
    }
};


int main(int argc, char const *argv[])
{
    Vector2 v(2);
    v[0] = 1;
    v[1] = 3;

    v.resize(4);
    v[2] = 100;

    int sum = 0;
    for (size_t i = 0; i < v.size(); i++)
    {
        sum += v[i];
    }
    

    return 0;
}

