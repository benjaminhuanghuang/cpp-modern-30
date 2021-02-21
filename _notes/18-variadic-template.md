

可变参数模板可变参数模板(variadic template)为一个接受`可变数目参数`的`模板函数`或`模板类`

是 C++11 引入的一项新功能

它有两个明显的用途：
  用于在通用工具模板中转发参数到另外一个函数
  用于在递归的模板中表达通用的情况

## 递归用法
```
  template <typename T>
  constexpr auto sum(T x)
  {
    return x;
  }
  template <typename T1, typename T2, typename... Targ>
  constexpr auto sum(T1 x, T2 y, Targ... args)
  {
    return sum(x + y, args...);
  }
```