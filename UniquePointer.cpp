#include <iostream>
#include <memory>

using std::cout;
using std::endl;

template <typename T> class UniquePointer {
private:
  T *obj_ptr;

public:
  UniquePointer() : obj_ptr(nullptr){};

  UniquePointer(T *const t) : obj_ptr{t} {
    cout << "unique pointer creating\n";
  };

  UniquePointer(UniquePointer<T> &&other)
      : obj_ptr(nullptr) { // move constructor
    cout << "move constructor\n";
    obj_ptr = other.obj_ptr;
    other.obj_ptr = nullptr;
  }

  ~UniquePointer() {
    cout << "unique pointer deleting\n";
    delete obj_ptr;
  }

  void reset(T *const t) {
    if (obj_ptr)
      delete obj_ptr;
    obj_ptr = t;
  }

  T *release() {
    T *const temp = obj_ptr;
    obj_ptr = nullptr;
    return temp;
  }

  void swap(UniquePointer<T> &other) {
    T *const temp = obj_ptr;
    obj_ptr = other.obj_ptr;
    other.obj_ptr = temp;
  }

  T *const get() const { return obj_ptr; }

  UniquePointer<T> &operator=(UniquePointer<T> &&other) { // move assignment
    cout << "move assignment\n";
    if (this == &other) // self assingment
      return *this;

    delete obj_ptr;
    obj_ptr = other.obj_ptr;
    other.obj_ptr = nullptr;
    return *this;
  }

  T *operator->() const { return obj_ptr; }

  T &operator*() const { return *obj_ptr; }

  operator bool() const { return obj_ptr != nullptr; }

  UniquePointer<T> &
  operator=(const UniquePointer<T> &other) = delete;     // copy assignment
  UniquePointer(const UniquePointer<T> &other) = delete; // copy constructor
};
using std::string;

int main() {
  string *s =
      new string("holle");
  UniquePointer<string> str(s);
  cout << *str << endl;
  cout << *s << endl;
  return 0;
}