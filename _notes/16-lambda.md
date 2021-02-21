函数对象（function object） 自 C++98 开始就已经被标准化了

函数对象是一个可以被当作函数来用的对象。它有时也会被叫做 functor，

```
struct adder {
  adder(int n) : n_(n) {}
  // functor
  int operator()(int x) const
  {
    return x + n_;
  }

private:
    int n_; 
};


// C++11
auto add_2 = adder(2);

// C++98
adder result(2);
```


## 函数的指针和引用



## 变量捕获

