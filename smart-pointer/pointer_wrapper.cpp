class shape
{
};

shape* create_shape() {
  return nullptr;
}

/*
  完成智能指针的最基本的功能：对超出作用域的对象进行释放,

  缺点是
  1. 这个类只适用于 shape 类
  2. 该类对象的行为不够像指针
  3. 拷贝该类对象会引发程序行为异常
*/
class shape_wrapper
{
public:
  explicit shape_wrapper(shape *ptr = nullptr) : ptr_(ptr) {}

  // 确保 delete 被包裹的*变量
  ~shape_wrapper()
  {
    delete ptr_;
  }
  shape *get() const { return ptr_; }

private:
  shape *ptr_;
};

void foo()
{
  /*
    把工厂方法 返回的sharp* 放到一个本地变量里，并确保其析构函数会删除该对象
  */
  shape_wrapper ptr_wrapper(create_shape());
}