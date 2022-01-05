/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-05 22:53:47
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-05 23:47:05
 * @@Email: 8211180515@csu.edu.cn
 */
#include <iostream>
using namespace std;

#include "../slib/slib.h"
#include "../dynlib/dynlib.h"

int main(int argc, char const *argv[])
{
    slib::slib_impl();
    dynlib::dynlib_impl();
    cout << "hello!" << endl;
    return 0;
}
