#include <iostream>

using std::cout;
using std::endl;

template <typename T> class UniquePointer {
private:
  T *obj_ptr;

public:
  UniquePointer() : obj_ptr(nullptr){};

  UniquePointer(T *t) : obj_ptr(t) { cout << "unique pointer creating\n"; };

  UniquePointer(UniquePointer<T> &&other)
      : obj_ptr(nullptr) { // move constructor
    obj_ptr = other.obj_ptr;
    other.obj_ptr = nullptr;
  }

  ~UniquePointer() {
    cout << "unique pointer deleting\n";
    delete obj_ptr;
  }


  void reset(T *t) {
    if(obj_ptr) {
      delete obj_ptr;
    }
    obj_ptr = t;
  }

  T *release() {
    T *temp = obj_ptr;
    obj_ptr = nullptr;
    return temp;
  }


  void swap(UniquePointer<T> &other) {
    T *temp = obj_ptr;
    obj_ptr = other.obj_ptr;
    other.obj_ptr = temp;
  }

  UniquePointer<T> &operator=(UniquePointer<T> &&other) { // move assignment
    if (this == &other) // self assingment
      return *this;

    delete obj_ptr;
    obj_ptr = other.obj_ptr;
    other.obj_ptr = nullptr;
    return *this;
  }

  /*
    UniquePointer<T> &operator=(const UniquePointer<T> &other) {
      if (this == &other) // self assingment
        return *this;

      delete obj_ptr;
      obj_ptr = new T(*other.obj_ptr);
      return *this;
    }
  */

  T *operator->() const { return obj_ptr; }

  T &operator*() const { return *obj_ptr; }

  operator bool() const { return obj_ptr != nullptr; }
};

using std::string;
int main()
{
  UniquePointer<string> a(new string("are"));
  
  string *r = a.release();
  
}
