### 几个注意点

- C++98 STL	`std::vector<int> v(4);`。

- C++11 引入了 {} 初始化表达式

  ```cpp
  std::vector<int> v = {4, 3, 2, 1};
  ```

- C++11 引入了 range-based for-loop

  ```cpp
  for (int vi : v)
  	sum += vi;
  ```

- for_each 算法模板

  ```cpp
  std::for_each(v.begin(), v.end(), func);
  ```

- C++11 引入了 lambda 表达式

  ```cpp
      std::for_each(v.begin(), v.end(), [&] (int vi) {
          sum += vi;
      });
  ```

- C++14 的 lambda 允许用 auto 自动推断类型

  ```cpp
      std::for_each(v.begin(), v.end(), [&] (auto vi) {
          sum += vi;
      });
  ```

- C++17 CTAD / compile-time argument deduction / 编译期参数推断

  ```cpp
  std::vector v = {4, 3, 2, 1};	// 去掉 int
  ```

  

### RALL

Resource Acquisition Is Initialization。 资源获取视为初始化，反之，资源释放视为销毁。而不再是采用 `malloc` 和 `free `的手动方法。



## 构造函数

### 构造函数初始化表达式

#### 使用方法：

```cpp
struct Pig {
    std::string m_name;
    int m_weight;

    Pig(std::string name, int weight) : m_name(name), m_weight(weight) 		{}
};

int main() {
    Pig pig("aaa", 100);
}
```

[C++ 初始化列表 ](https://www.cnblogs.com/graphics/archive/2010/07/04/1770900.html)

- 初始化类的成员有两种方式，一是使用初始化列表，二是在构造函数体内进行赋值操作。
- 构造函数的执行可以分成两个阶段，初始化阶段和计算阶段，初始化阶段先于计算阶段。

而对于赋值操作，会在初始化阶段**对于需要赋值的对象调用其默认构造函数**。

因此使用初始化列表少了一次调用默认构造函数的过程。

（1）没有默认构造函数的成员类对象；（2）const成员或引用类型的成员。

- 常量成员，因为常量只能初始化不能赋值，所以必须放在初始化列表里面

- 引用类型，引用必须在定义的时候初始化，并且不能重新赋值，所以也要写在初始化列表里面

- 没有默认构造函数的成员类对象，因为使用初始化列表可以不必调用默认构造函数来初始化，而是直接调用拷贝构造函数初始化。

  > ```cpp
  > struct Test1
  > {
  >     Test1(int a):i(a){}
  >     int i ;
  > };
  > 
  > struct Test2
  > {
  >     Test1 test1 ;
  >     Test2(Test1 &t1)
  >     {
  >         test1 = t1 ;
  >     }
  > };
  > ```
  >
  > 以上代码无法通过编译，因为 Test2 类中 Test1 test1; 需要调用默认的构造函数，但是 Test1 类没有无参的构造函数，即 Test1 没有默认的构造函数，故而编译错误。



### 自定义构造函数：单个参数

可以发现当只有一个参数的时候，下面还存在着一种 `Pig pig2 = 80;` 的写法，很难以理解。

```cpp
struct Pig {
    std::string m_name;
    int m_weight;

    Pig(int weight) 
    : m_name("一只 Pig" + std::to_string(weight))
    , m_weight(weight) {}
};

int main() {
    Pig pig(80);
    Pig pig2 = 80;
}
```

可以加上以下 `explicit` 显示定义来限制不能使用 `=` 这种方法。

```cpp
    explicit Pig(int weight) 
    : m_name("一只 Pig" + std::to_string(weight))
    , m_weight(weight) {}
```

因此：请给单参数的构造函数加上 `explicit`。

> **对于多参数**
>
> explicit 的作用体现在禁止从一个 {} 表达式初始化。
>
> 不加的话，其实是可以 `Pig pig1 = {"aaa", 100};` 这样通过`{}`来初始化，但是加上之后便会禁止。

![image-20220116225451768](../assets/blog_image/README/image-20220116225451768.png)



### 编译器默认生成的构造函数

当一个类没有定义任何构造函数，且所有成员都有无参构造函数时，编译器会自动生成一个无参构造函数 Pig()，**他会调用每个成员的无参构造函数**。

#### 初始化某些类型时的问题：

> 但是请注意，这些类型不会被初始化为 0：
>
> - int, float, double 等基础类型
>
> - void *, Object * 等指针类型
>
> - 完全由这些类型组成的类
>
>   这些类型被称为 POD（plain-old-data）。POD 的存在是出于兼容性和性能的考虑。

比如下列 Demo 会打印随机值生成的 `weight`。

```cpp
struct Pig {
    std::string m_name;
    int m_weight;
};

void show(Pig pig) {
    std::cout << "name: " << pig.m_name << std::endl;
    std::cout << "weight: " << pig.m_weight << std::endl;
}

int main() {
    Pig pig;

    show(pig);
    return 0;
}

```

解决办法是 `int m_weight{0};` 或者 `int m_weight = 0;` 进行初始化。

> 顺便一提：
> `int x{};` 、`void *p{};`
> 与
> `int x{0};`、`void *p{nullptr};`等价，都会零初始化。但是不写那个空括号就会变成内存中随机的值。
>
> 再比如：std::cout << int{}; 会打印出 0

#### C++11 会自动生成初始化表达式

他会将 {} 内的内容，会按顺序赋值给对象的每一个成员。但是不支持 `（）`

> 在 C++ 14 后，支持部分初始化。`Pig pig1 = {"佩奇"};`，但是记得保证没有初始化的类成员在定义时进行初始化 `int m_weight{0};` ，以避免随机值。

```cpp
struct Pig {
    std::string m_name;
    int m_weight;
};

void show(Pig pig) {
    std::cout << "name: " << pig.m_name << std::endl;
    std::cout << "weight: " << pig.m_weight << std::endl;
}

int main() {
    Pig pig1 = {"佩奇", 80};   // 编译通过
    Pig pig2{"佩奇", 80};      // 编译通过
    // Pig pig3("佩奇", 80);   // 编译错误！

    show(pig1);
    return 0;
}
```

#### default

如果还想让编译器自动生成默认的无参构造函数，可以用 C++11 新增的这个语法：

```cpp
Pig() = default;
```

如果想要让编译器不要自动生成无参构造函数，可以用 = delete 语法删除：

```cpp
Pig() = delete;
```

> 注：= delete 和 = default 是一对。如果你不确定某个函数有没有被编译器默认生成，可以都用这两个显式地声明一下。



#### 拷贝构造函数

除了无参和初始化列表构造函数外，编译器默认还会生成这样一个特殊的构造函数：

`Pig(Pig const &other);`

可见他的参数是一个 Pig 类型，他的功能就是拷贝 Pig 对象，故称为拷贝构造函数。

> 当然也可以自定义

```cpp
int main() {
    Pig pig1 = {"happy", 70};
    Pig pig = pig1;
    // Pig pig(pig1);
}
```



#### 拷贝赋值函数

除了拷贝构造函数外，编译器默认还会生成这样一个重载 `=` 这个运算符的函数：

```cpp
Pig &operator=(Pig const &other);
```

**拷贝构造函数**的作用是在 Pig **尚未**初始化时，将另一个 Pig 拷贝进来，以初始化当前 Pig 。

```cpp
Pig pig = pig2;  // 拷贝构造
```

**拷贝赋值函数**的作用是在 Pig **已经**初始化后，将当前 Pig 销毁，同时将另一个 Pig 拷贝进来。

```cpp
Pig pig;           // 无参构造
pig = pig2;        // 拷贝赋值
```

追求性能时推荐用拷贝构造，因为可**以避免一次无参构造**，拷贝赋值是出于需要临时修改对象的灵活性需要。

这个函数同样可以由 = delete 和 = default 控制是否默认生成。

> 注：return *this 是为了支持连等号 a = b = c;



#### 深浅拷贝

[c++的默认拷贝构造函数，从深度拷贝和浅拷贝说起](https://blog.csdn.net/qq_29344757/article/details/76037255)

默认的**拷贝构造函数**都是浅拷贝，智能指针是浅拷贝

> 小 tip
>
> c++的拷贝构造函数还有一处妙用，就是自定义拷贝构造函数，并设置为private属性，其实现体可以什么都不写，那么这个类将变成一个不可被复制的类了。



**拷贝赋值** ～ 解构函数 + 拷贝构造函数

法一：

可以这样整：（placement new），当然这样会损失性能。

```cpp
    Vector &operator=(Vector const &other) {
        this->~Vector();             // 先销毁现有的
        new (this) Vector(other);    // 再重新构造（placement new）
        return *this;                // 支持连等号：v1 = v2 = v3
    }
```

法二：

内存的销毁重新分配可以通过 realloc，从而就地利用当前现有的 m_data，避免重新分配。

```cpp
    Vector &operator=(Vector const &other) {
        m_size = other.m_size;
        m_data = (int *)realloc(m_data, m_size * sizeof(int));
        memcpy(m_data, other.m_data, m_size * sizeof(int));
        return *this;
    }
```



### 移动、swap O(1)

swap 相当于使用 tmp 临时对象

```cpp
void test_copy() {
    std::vector<int> v1(10);
    std::vector<int> v2(200);

    v1 = v2;                  // 拷贝赋值 O(n)

    std::cout << "after copy:" << std::endl;
    std::cout << "v1 length " << v1.size() << std::endl;  // 200
    std::cout << "v2 length " << v2.size() << std::endl;  // 200
}

void test_move() {
    std::vector<int> v1(10);
    std::vector<int> v2(200);

    v1 = std::move(v2);      // 移动赋值 O(1)

    std::cout << "after move:" << std::endl;
    std::cout << "v1 length " << v1.size() << std::endl;  // 200
    std::cout << "v2 length " << v2.size() << std::endl;  // 0
}

void test_swap() {
    std::vector<int> v1(10);
    std::vector<int> v2(200);

    std::swap(v1, v2);      // 交换两者 O(1)

    std::cout << "after swap:" << std::endl;
    std::cout << "v1 length " << v1.size() << std::endl;  // 200
    std::cout << "v2 length " << v2.size() << std::endl;  // 10
}
```

当然对时间复杂度要求高的，可以进行移动构造函数的自定义。

![image-20220118003517647](../assets/blog_image/README/image-20220118003517647.png)

还存在一个小技巧：如果有移动赋值函数，可以删除拷贝赋值函数

![image-20220118003657900](../assets/blog_image/README/image-20220118003657900.png)
