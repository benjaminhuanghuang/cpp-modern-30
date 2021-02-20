class shape
{
};

shape* create_shape() {
  return nullptr;
}


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