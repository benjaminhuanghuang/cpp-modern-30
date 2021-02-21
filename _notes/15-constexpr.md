在 C++11 引入、在 C++14 得到大幅改进的 constexpr 关键字就是为了解决这些问题而
诞生的。

它的字面意思是 constant expression，常量表达式。

存在两类 constexpr 对象：
一个 constexpr 变量是一个编译时完全确定的常数。
一个 constexpr 函数至少对于某一组实参可以在编译期间产生一个编译期常数。

## constexpr 和 const
const 用来表示一个运行时常量


