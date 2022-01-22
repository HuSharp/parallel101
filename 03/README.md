## 模板函数

一些资料

[C++ Template 进阶指南](https://github.com/wuye9036/CppTemplateTutorial)



### 模板泛化

分为 类模板, 函数模板, 成员模板

### template Class

我们把通过类型绑定将模板类变成“普通的类”的过程，称之为模板实例化（Template Instantiate）。实例化的语法是：

```
模板名 < 模板实参1 [，模板实参2，...] >
```



#### 特化 Specialization

> 也称为 Full Specialization

```cpp
template<>
class allocator<void> {
public:
  typedef size_t      size_type;
  typedef ptrdiff_t   difference_type;
  typedef void*       pointer;
  typedef const void* const_pointer;
  typedef void        value_type;

  template <class _Tp1> struct rebind {
    typedef allocator<_Tp1> other;
  };
};

// Specialization
template<>
class allocator<int> {
	...
}
```

如果现在使用 `allocator<Foo>` 那么会进入到泛化模板中，void 和 int 都是会进入到特化中。 

**即：当模板实例化时提供的模板参数不能匹配到任何的特化形式的时候，它就会去匹配类模板的“原型”形式。**

> 出现 **此处的 `template<>`**这种格式的解释如下：
>
> ```cpp
> 
> // 我们这个模板的基本形式是什么？
> template <typename T> class allocator;
> 
> // 但是这个类，是给T是Int的时候用的，于是我们写作
> class allocator<int>;
> // 当然，这里编译是通不过的。
> 
> // 但是它又不是个普通类，而是类模板的一个特化（特例）。
> // 所以前面要加模板关键字template，
> // 以及模板参数列表
> template </* 这里要填什么？ */> class AddFloatOrMulInt<int>;
> 
> // 最后，模板参数列表里面填什么？因为原型的T已经被int取代了。所以这里就不能也不需要放任何额外的参数了。
> // 所以这里放空。
> template <> class AddFloatOrMulInt<int>
> {
>     // ... 针对Int的实现 ... 
> };
> 
> // Bingo!
> ```
>
> 注：STL 中的 `__STL_TEMPLATE_NULL` 类似 `template<>` 表示要开始特化了.



并且由于可以使用 T* 作为特化，因此是以下写法：

```cpp
template <typename T>
class RemovePointer
{
public:
    typedef T Result;  // 如果放进来的不是一个指针，那么它就是我们要的结果。
};

template <typename T>	// 此处需要 T
class RemovePointer<T*>	// 祖传牛皮藓，专治各类指针
{
public:
    typedef T Result;  // 去掉一层指针，把 T* 这里的 T 取出来。
};

void Foo()
{
    RemovePointer<float*>::Result x = 5.0f; // 喏，用RemovePointer后，那个Result就是把float*的指针处理掉以后的结果：float啦。
    std::cout << x << std::endl;
}
```

因此利用这个特性，可以：把指针类型的那个指针给“干掉”：

再进一步：如果传进来的是类似 `RemovePointer<int**>` 这样的东西呢？是的没错，去掉一层之后还是一个指针，因此继续向下取就行。

```cpp
template <typename T>
class RemovePointer<T*>
{
public:
    // 如果是传进来的是一个指针，我们就剥夺一层，直到指针形式不存在为止。
    // 例如 RemovePointer<int**>，Result 是 RemovePointer<int*>::Result，
    // 而 RemovePointer<int*>::Result 又是 int，最终就变成了我们想要的 int，其它也是类似。
    typedef typename RemovePointer<T>::Result Result;
};
```





#### 还存在 偏特化 Partial Specialization

泛化

```cpp
template <class T, class Alloc = alloc>  // 缺省使用 
class vector {
	...
};
```

偏特化_1(此偏特化指的是泛化变量的局部特化)

```cpp
template <class Alloc> 
class vector<bool, Alloc> {
	...
};
```

泛化

```cpp
template <class T> 
class vector {
	T ...
};
```

偏特化_2(此偏特化指的是泛化变量为指针, 缩小了泛化变量的范围, 因此也是一种偏特化)

```cpp
template <class T> 
class vector<T*> {
	T ...
};
```





### template Function

模板函数的语法与模板类基本相同，也是以关键字`template`和模板参数列表作为声明与定义的开始。

```cpp
template <typename T> void foo(T const& v);
template <typename T> T foo();
template <typename T, typename U> U foo(T const&);
template <typename T> void foo() { T var; } 
```

C++ 支持推导一部分模板参数，**但需要先写指定的模板参数，再把能推导出来的模板参数放在后面**。

其中有一点需要注意，因为模板的匹配是在编译的时候完成的，所以实例化模板的时候所使用的参数，也必须要在编译期就能确定。例如以下的例子编译器就会报错：

```cpp
template <int i> class A {};

void foo()
{
    int x = 3;
    A<5> a; // 正确！
    A<x> b; // error C2971: '_1_3::A' : template parameter 'i' : 'x' : a local variable cannot be used as a non-type argument
}
```



#### 整型也可是Template参数

模板参数除了类型外（包括基本类型、结构、类类型等），也可以是一个整型数（Integral Number）。**这里的整型数比较宽泛，包括布尔型，不同位数、有无符号的整型，甚至包括指针**。我们将整型的模板参数和类型作为模板参数来做一个对比：

```cpp
template <typename T> class TemplateWithType;
template <int      V> class TemplateWithValue;
```

可看出 `typename` 的意思：它相当于是模板参数的“类型”，告诉你 `T` 是一个 `typename`。

整型模板参数最基本的用途，就是定义一个常数。

```cpp
template <int i> class A 
{
public:
    void foo(int) {}
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
```

