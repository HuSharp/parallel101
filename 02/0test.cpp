/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-16 21:55:03
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-16 22:13:30
 * @@Email: 8211180515@csu.edu.cn
 */
#include <string>
#include <iostream>
using namespace std;

struct foo
{
    string name ;
    int id ;
    foo(string s, int i):name(s), id(i){} ; // 初始化列表
};

struct Test1
{
    Test1() // 无参构造函数
    { 
        cout << "Construct Test1" << endl ;
    }

    Test1(const Test1& t1) // 拷贝构造函数
    {
        cout << "Copy constructor for Test1" << endl ;
        this->a = t1.a ;
    }

    Test1& operator = (const Test1& t1) // 赋值运算符
    {
        cout << "assignment for Test1" << endl ;
        this->a = t1.a ;
        return *this;
    }

    int a ;
};

struct Test2
{
    Test1 test1 ;
    Test2(Test1 &t1)
    {
        test1 = t1 ;
    }
};

struct Test3
{
    Test1 test1 ;
    Test3(Test1 &t1):test1(t1){}
};


int main(int argc, char const *argv[])
{
    Test1 t1 ;
    // Test2 t2(t1) ;
    Test3 t3(t1) ;
    return 0;
}
