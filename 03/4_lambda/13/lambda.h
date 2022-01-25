/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-24 23:36:46
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-24 23:36:46
 * @@Email: 8211180515@csu.edu.cn
 */
void call_twice(std::function<int(int)> const &func) {
    std::cout << func(0) << std::endl;
    std::cout << func(1) << std::endl;
    std::cout << "Func 大小: " << sizeof(func) << std::endl;
}