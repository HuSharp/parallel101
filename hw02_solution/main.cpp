/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-21 09:58:35
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-21 11:19:52
 * @@Email: 8211180515@csu.edu.cn
 */
/* 基于智能指针实现双向链表 */
#include <cstdio>
#include "List.hpp"

void print(List const &lst) {  // 有什么值得改进的？   -> 避免深拷贝 采用引用传递
    printf("[");
    for (auto curr = lst.front(); curr; curr = curr->next.get()) {
        printf(" %d", curr->value);
    }
    printf(" ]\n");
}

int main() {
    List a;

    a.push_front(7);
    a.push_front(5);
    a.push_front(8);
    a.push_front(2);
    a.push_front(9);
    a.push_front(4);
    a.push_front(1);

    print(a);   // [ 1 4 9 2 8 5 7 ]

    a.at(2)->erase();

    print(a);   // [ 1 4 2 8 5 7 ]

    List b = a;

    a.at(3)->erase();

    print(a);   // [ 1 4 2 5 7 ]
    print(b);   // [ 1 4 2 8 5 7 ]

    b = {};
    a = {};

    return 0;
}
