/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-22 20:45:23
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-22 21:27:19
 * @@Email: 8211180515@csu.edu.cn
 */
int data[1024];
template <typename T, int size>
class Stack {
public:
    void push(T v);
    T pop();
    int Find(T x) {
        for (int i = 0; i < size; i++) {
            if (data[i] == x) {
                return i;
            }
        }
        
    } 
};
int len = 1024;
typedef Stack<int, 1024> StackInt;

#include <stdint.h>
struct meta_stu {
    union {
        int x;
        float y;
    }data;
    uint32_t typeId;
};

meta_stu addFloatOrInt(meta_stu const* a, meta_stu const* b) {
    meta_stu ret;
    if (a->typeId == 1) {
        
    }
}

template <typename T> class TypeToID {
public:
    static int const ID = -1;
};

template <> class TypeToID<uint16_t> {
public: 
    static int const ID = 0;
};


template<>
class allocator2<void> {
};