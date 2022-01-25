/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-22 16:43:35
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-22 20:09:09
 * @@Email: 8211180515@csu.edu.cn
 */

template <typename T> class classA;
template <typename T> class classA {
    T member;
};

template <typename T> class vector {
public:
    void clear();
private:
    T* elements;
};

template <typename T>
void vector<T>::clear() {

}

template <typename T> void foo(T const& v);
template <typename T> T foo();
template <typename T, typename U> U foo(T const&);
template <typename T> void foo() { T var; } 

float a[1024];
template <typename T> T GetVal(int i) {
    return static_cast<T>(a[i]);
}
float i = GetVal<float>(0);
int b = GetVal<int>(1);

template <typename SrcT, typename DscT> DscT c_style_cast(SrcT v) {
    return (DscT)v;
}

#include <stdint.h>
template <int i> class A 
{
public:
    void foo(int)
    {
    }
};
template <uint8_t a, typename b, void* c> class B {};
template <bool, void (*a)()> class C {};
template <void (A<3>::*a)(int)> class D {};

template <int i> int Add(int a)	// 当然也能用于函数模板
{
    return a + i;
}

void foo()
{
    A<5> a;
    B<7, A<5>, nullptr>	b; // 模板参数可以是一个无符号八位整数，可以是模板生成的类；可以是一个指针。
    C<false, &foo> c;      // 模板参数可以是一个bool类型的常量，甚至可以是一个函数指针。
    D<&A<3>::foo> d;       // 丧心病狂啊！它还能是一个成员函数指针！
    int x = Add<3>(5);     // x == 8。因为整型模板参数无法从函数参数获得，所以只能是手工指定啦。
}

template <float a> class E {}; // ERROR: 别闹！早说过只能是整数类型的啦！