#include <iostream>
#include <memory>

using std::unique_ptr;

template <typename T> class Array2D {
private:
  std::size_t height, width;
  unique_ptr<T[]> arr_ptr;

public:
  Array2D() : Array2D(0,0) {};

  Array2D(const std::size_t height1, const std::size_t width1) // constructor
      : height(height1), width(width1),
        arr_ptr(unique_ptr<T[]>(new T[height * width])){};

  Array2D(const Array2D<T> &other)
      : height(other.height), width(other.width),
        arr_ptr(unique_ptr<T[]>(new T[height * width])) { // copy constructor
    std::copy(other.arr_ptr.get(), other.arr_ptr.get() + height * width,
              arr_ptr.get());
  }

  ssize_t get_height() const { return height; }

  ssize_t get_width() const { return width; }

  bool operator==(const Array2D<T> &other) const {
    if (width != other.width || height != other.height)
      return false;
    for (std::size_t i = 0; i < height * width; ++i)
      if (arr_ptr[i] != other.arr_ptr[i])
        return false;
    return true;
  }

  bool operator!=(const Array2D<T> &other) const { return !operator==(other); }

  Array2D<T> &operator=(const Array2D<T> &other) {
    if (this == &other) // self assingment
      return *this;

    height = other.height;
    width = other.width;
    arr_ptr = unique_ptr<T[]>(new T[height * width]);
    std::copy(other.arr_ptr.get(), other.arr_ptr.get() + height * width,
              arr_ptr.get());
    return *this;
  }

  T *operator[](std::size_t hei) { return (arr_ptr.get() + hei * width); };

  const T *operator[](std::size_t hei) const {
    return (arr_ptr.get() + hei * width);
  };
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Array2D<T> &arr) {
  os << std::endl;
  for (std::size_t i = 0; i < arr.get_height(); ++i) {
    for (std::size_t j = 0; j < arr.get_width(); ++j)
      os << arr[i][j] << ", ";
    os << std::endl;
  }
  return os;
}