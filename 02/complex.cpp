/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-18 17:04:12
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-19 17:25:37
 * @@Email: 8211180515@csu.edu.cn
 */
#ifndef __COMPLEX__
#define __COMPLEX__

#include <cmath>

class ostream;
class complex;

class complex
{
private:
    double re, im;
    
public:
    double X;
    complex(double r = 0, double i = 0)
        : re(r), im(i) {}
    
    double real() const {
        return re;
    }
    friend complex& __doapl(complex*, const complex&);
};

inline complex& __doapl(complex* ths, const complex& other) {
    ths->re += other.re;
    return *ths;
}

inline double image(const complex& x) {
    return x.X;
}

int main(int argc, char const *argv[])
{
    int a = 0;
    int *pa = &a;   // -16(%rbp)
    int &ra = a;    // -24(%rbp)
    ++(*pa);
    ++ra;
}

#endif