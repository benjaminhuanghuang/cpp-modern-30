# 内存模型和原子量
C++98 的年代里，开发者们已经了解了线程的概念，但 C++ 的标准里则完全没有提到线程



## Double lock check
```
class singleton {
public:
  static singleton* instance();
private:
  static singleton* inst_ptr_;
};

// 实现文件
singleton* singleton::inst_ptr_ = nullptr;
singleton* singleton::instance()
{
  // double-lock-check
  if (inst_ptr_ == nullptr) {
    lock_guard lock; // 加锁
    if (inst_ptr_ == nullptr) {
      inst_ptr_ = new singleton();
    }
  }
  return inst_ptr_;
}
```

volatile 在某些编译器里，使用 volatile 关键字可以达到内存同步的效果。但我们必须记住，这
不是 volatile 的设计意图，也不能通用地达到内存同步的效果。

volatile 的语义只是防止编译器“优化”掉对内存的读写而已。它的合适用法，目前主要是用来读写映射到内存地址上的 I/O 操作。
由于 volatile 不能在多处理器的环境下确保多个线程能看到同样顺序的数据变化，在今
天的通用应用程序中，不应该再看到 volatile 的出现

## C++11 的内存模型



