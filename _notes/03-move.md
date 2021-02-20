

 lvalue 是通常可以放在等号左边的表达式，左值
 rvalue 是通常只能放在等号右边的表达式，右值
 glvalue 是 generalized lvalue，广义左值
 xvalue 是 expiring lvalue，将亡值
 prvalue 是 pure rvalue，纯右值


左值 lvalue 是有标识符、可以取地址的表达式，最常见的情况有：
- 变量、函数或数据成员的名字
- 返回左值引用的表达式，如 ++x、x = 1、cout << ' '
- 字符串字面量如 "hello world"

在 C++11 之前，右值可以绑定到常左值引用（const lvalue reference）的参数，如
const T&，但不可以绑定到非常左值引用（non-const lvalue reference），如 T&。从
C++11 开始，C++ 语言里多了一种引用类型——右值引用。右值引用的形式是 T&&，比
左值引用多一个 & 符号。跟左值引用一样，我们可以使用 const 和 volatile 来进行修
饰，但最常见的情况是，我们不会用 const 和 volatile 来修饰右值


std::move(ptr) 的作用是把一个`左值引用`强制转换成一个`右值引用`，而并不改变其内容。
std::move(ptr1) 等价于 
static_cast<smart_ptr<shape>&&>(ptr1)。
因此，std::move(ptr1) 的结果是指向 ptr1 的一个右值引用，


## 移动的意义

对于 smart_ptr，使用右值引用的目的是实现移动，而实现移动的意义是减少运行的
开销——在引用计数指针的场景下，这个开销并不大。移动构造和拷贝构造的差异仅在
于