- heap，在内存管理的语境下，指的是动态分配内存的区域。这个堆跟数据结构
里的堆不是一回事。这里的内存，被分配之后需要手工释放，否则，就会造成内存泄漏。

C++ 标准里一个相关概念是自由存储区(free store)，特指使用 new 和 delete 来
分配和释放内存的区域。一般而言，这是堆的一个子集：
但 new 和 delete 通常底层使用 malloc 和 free 来实现，所以 free store 也是 heap。

- stack，在内存管理的语境下，指的是函数调用过程中产生的`本地变量`和`调用数
据`的区域。这个栈和数据结构里的栈高度相似，都满足“后进先出”（last-in-first-out 或
LIFO）。

- RAII，完整的英文是 Resource Acquisition Is Initialization，是 C++ 所特有的资源管理
方式。有少量其他语言，如 D、Ada 和 Rust 也采纳了 RAII，但主流的编程语言中， C++
是唯一一个依赖 RAII 来做资源管理的。
RAII 依托栈和析构函数，来对所有的资源——包括堆内存在内——进行管理。对 RAII 的
使用，使得 C++ 不需要类似于 Java 那样的垃圾收集方法，也能有效地对内存进行管理。



## Heap
使用堆，或者说使用动态内存分配:
```
// C++
auto ptr = new std::vector<int>();

// Java
ArrayList<int> list = new ArrayList<int>();

# Python
lst = list()
```
1. 让内存管理器分配一个某个大小的内存块
2. 让内存管理器释放一个之前分配的内存块
3. 让内存管理器进行垃圾收集操作，寻找不再使用的内存块并予以释放

C++ 通常会做上面的操作 1 和 2。
Java 会做上面的操作 1 和 3。
Python 会做上面的操 作 1、2、3。

## Stack
在包括 x86 在内的大部分计算机体系架构中，栈的增长方向是低地址，因而栈顶意味着低地址

当函数调用另外一个函数时，
1. 把参数也压入栈里（此处忽略使用寄存器传递参数的情况），
2. 把下一行汇编指令的地址压入栈，并跳转到新的函数。
3. 新的函数进入后，首先做一些必须的保存工作，然后会调整栈指针，分配出本地变量所需的空间，
4. 随后执行函数中的代码，并在执行完毕之后，根据调用者压入栈的地址，返回到调用者未执行的代码中继续执行。
```
  void foo(int n)
  {

  }
  void bar(int n)
  {
    int a = n + 1;
    foo(a);
  }
  int main()
  {
    bar(42);
  }
```
![](./_images/stack.png)

栈上的分配/释放极为简单，移动一下栈指针而已。由于后进先出的执行过程，不可能出现内存碎片。

本地变量所需的内存就在栈上，跟函数执行所需的其他数据在一起。当函数执行完成之后，这些内存也就自然而然释放掉了
本地变量是简单类型，C++ 里称之为 POD 类型（Plain Old Data）。

对于有构造和析构函数的非 POD 类型，栈上的内存分配也同样有效，只不过 C++ 编译器会在生成代码的合适位置，插入对构造和析构函数的调用。

编译器会自动调用析构函数，包括在函数执行发生异常的情况。在发生异常时对析构函数的调用，还有一个专门的术语，叫栈展开（stack unwinding）

```
  stack-unwinding.cpp
```

在 C++ 里，所有的变量缺省都是值语义

## RAII(Resource Acquisition Is Initialization)
在很多情况下，对象不能，或不应该，存储在栈上。比如：
- 对象很大；
- 对象的大小在编译时不能确定；
- 对象是函数的返回值。


New operation
1. alloc memory
2. construct object

Delete operation
1. descrutc
2. free memory
```
new circle(…)
{
  void* temp = operator new(sizeof(circle));
  try {
    circle* ptr =
    static_cast<circle*>(temp);
    ptr->circle(…);
    return ptr;
  }
  catch (...) {
    operator delete(ptr);
    throw;
  }
}


if (ptr != nullptr) {
  ptr->~shape();
  operator delete(ptr);
}
```


RAII 除了释放内存，也可以：
关闭文件（fstream 的析构就会这么做）
释放同步锁
释放其他重要的系统资源

```
std::mutex mtx;
void some_func()
{
  std::lock_guard<std::mutex> guard(mtx);
  // 做需要同步的工作
}
```

解决如下问题：
```
std::mutex mtx;
void some_func()
{
    mtx.lock();
    // 做需要同步的工作……
    // 如果发生异常或提前返回，
    // 下面这句不会自动执行。
    mtx.unlock();
}
```