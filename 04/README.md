

编译参数

```shell
gcc -fomit-frame-pointer -fverbose-asm -S main.cpp -o /tmp/main.S
vim /tmp/main.S
```

`-fomit-frame-pointer`：让生成代码更简洁

`-fverbose-asm` 在编译成汇编语言时，把C变量的名称作为汇编语言中的注释



### 指针的索引：尽量用 size_t

size_t 在 64 位系统上相当于 uint64_t
size_t 在 32 位系统上相当于 uint32_t
从而不需要用 movslq 从 32 位符号扩展到 64 位，更高效。而且也能处理数组大小超过 INT_MAX 的情况，推荐始终用 size_t 表示数组大小和索引。

由下图可以看到首先进行了 movslq 从 32 位符号扩展到 64 位。

![image-20220126131011589](../assets/blog_image/README/image-20220126131011589.png)



### 浮点数

#### xmm

浮点作为参数和返回：**xmm 系列寄存器**

```asm
float func(float a, float b) {
    return a + b;
}

# 以下为汇编
#---------------------------

_Z4funcff:
.LFB0:
	.cfi_startproc
# main.cpp:2:     return a + b;
	addss	%xmm1, %xmm0	# b, tmp90
# main.cpp:3: }
	ret
	.cfi_endproc
```

xmm 寄存器有 128 位宽。
可以容纳 4 个 float，或 2 个 double。比如上面代码就只用到了 xmm 的低 32 位用于存储 1 个 float。

![image-20220126132002408](../assets/blog_image/README/image-20220126132002408.png)

#### addss

可以拆分成三个部分：add，s，s
add 表示执行加法操作。
第一个 s 表示标量(scalar)，只对 xmm 的最低位进行运算；也可以是 p 表示矢量(packed)，一次对 xmm 中所有位进行运算。
第二个 s 表示单精度浮点数(single)，即 float 类型；也可以是 d 表示双精度浮点数(double)，即 double 类型。

> addss：一个 float 加法。
> addsd：一个 double 加法。
> addps：四个 float 加法。
> addpd：两个 double 加法。

![image-20220126134106038](../assets/blog_image/README/image-20220126134106038.png)

因此引出 SIMD 。这种单个指令处理多个数据的技术称为 SIMD（single-instruction multiple-data）。他可以大大增加计算密集型程序的吞吐量。

#### SIMD

这种单个指令处理多个数据的技术称为 SIMD（single-instruction multiple-data）。
他可以大大增加计算密集型程序的吞吐量。
因为 SIMD 把 4 个 float 打包到一个 xmm 寄存器里同时运算，很像数学中矢量的逐元素加法。因此 SIMD 又被称为矢量，而原始的一次只能处理 1 个 float 的方式，则称为标量。
在一定条件下，编译器能够把一个处理标量 float 的代码，转换成一个利用 SIMD 指令的，处理矢量 float 的代码，从而增强你程序的吞吐能力！
通常认为利用同时处理 4 个 float 的 SIMD 指令可以加速 4 倍。但是如果你的算法不适合 SIMD ，则可能加速达不到 4 倍；也有因为 SIMD 让访问内存更有规律，节约了指令解码和指令缓存的压力等原因，出现加速超过 4 倍的情况。



### PLT

@PLT 是 Procedure Linkage Table 的缩写，即函数链接表。链接器会查找其他 .o 文件中是否定义了 _Z5otheri 这个符号，如果定义了则把这个 @PLT 替换为他的地址。

定义在同一个文件中的函数就不会有 PLT 这个符号。

因为 static 声明表示不会暴露 other 给其他文件，而且 func 也已经内联了 other，所以编译器干脆不定义 other 了。

inline 关键字？不需要！

在现代编译器的高强度优化下，加不加 inline 无所谓。
编译器不是傻子，**只要他看得见 other 的函数体定义，就会自动内联**，内联与否和 inline 没关系，内联与否只取决于是否在同文件，且函数体够小
要性能的，定义在头文件声明为 static 即可，没必要加 inline 的
static 纯粹是为了避免多个 .cpp 引用同一个头文件造成冲突，并不是必须 static 才内联
如果你不确定某修改是否能提升性能，那你最好实际测一下，不要脑内模拟
inline 在现代 C++ 中有其他含义，但和内联没有关系，他是一个迷惑性的名字
