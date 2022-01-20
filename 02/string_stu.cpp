/*
 * @Descripttion: 
 * @version: 
 * @Author: HuSharp
 * @Date: 2022-01-19 16:57:34
 * @LastEditors: HuSharp
 * @LastEditTime: 2022-01-19 19:54:46
 * @@Email: 8211180515@csu.edu.cn
 */
#include <string.h>
#include <stdlib.h>
class String
{
public:
    String(const char* cstr = 0);
    String& operator=(String const &other);
    ~String();
    
    char* get_c_Str() const { return m_data; }
    int get_c_len() const { return len; }
private:
    char* m_data;
    int len;
};

inline
String::String(const char* cstr) : len(6) {
    if (cstr) {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
        len = strlen(m_data) + 1;
    } else {
        m_data = new char[1];
        *m_data = '\0';
    }
}

// 法一：
inline
String& String::operator=(String const &other) {
    if (this == &other) {
        return *this;
    }

    delete []m_data;
    m_data = new char[strlen(other.m_data) + 1];
    strcpy(m_data, other.m_data);
    return *this;
}

// // 法二：
// inline
// String& String::operator=(String const &other) {
//     int size = other.get_c_len();
//     m_data = (char*)realloc(m_data, size * sizeof(char));
//     memcpy(m_data, other.m_data, size * sizeof(char));
//     return *this;
// }


inline
String::~String() {
    delete []m_data;
}

#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    String s;
    String B("happyaaa");
    String A(B);

    String* p = new String("hello");
    
    cout << A.get_c_Str() << endl;
    cout << A.get_c_len() << endl;

    delete p;
    return 0;
}
