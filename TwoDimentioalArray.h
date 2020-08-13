#include <iostream>

template <typename T> class Array2D {
private:
  std::size_t height, width;
  T *arr_ptr;

public:
  Array2D(){}; // default constructor

  Array2D(std::size_t height1, std::size_t width1) // constructor
      : height(height1), width(width1), arr_ptr(new T[height * width]){};

  Array2D(const Array2D<T> &other) { // copy constructor
    height = other.height;
    width = other.width;
    arr_ptr = new T[height * width];
    for (size_t i = 0; i < height * width; ++i)
      arr_ptr[i] = other.arr_ptr[i];
  }

  ~Array2D() { delete[] arr_ptr; } // distructor

  void print() {
    std::cout << std::endl;
    for (std::size_t i = 0; i < height; ++i) {
      for (std::size_t j = 0; j < width; ++j)
        std::cout << arr_ptr[i * width + j] << ", ";
      std::cout << std::endl;
    }
  };

  bool operator==(const Array2D<T> &other) {
    if (width != other.width || height != other.height)
      return false;
    for (std::size_t i = 0; i < height * width; ++i)
        if (arr_ptr[i] != other.arr_ptr[i])
          return false;
    return true;
  }
  bool operator!=(const Array2D<T> &other) {
    if (width != other.width || height != other.height)
      return true;
    for (std::size_t i = 0; i < height * width; ++i)
      if (arr_ptr[i] != other.arr_ptr[i])
        return true;
    return false;
  }
  Array2D<T> &operator=(const Array2D<T> &other) {
    if (this == &other) // self assingment
      return *this;

    height = other.height;
    width = other.width;
    delete[] arr_ptr;
    arr_ptr = new T[height * width];
    for (size_t i = 0; i < height * width; ++i)
      arr_ptr[i] = other.arr_ptr[i];
    return *this;
  }

  T *operator[](std::size_t hei) { return (arr_ptr + hei * width); };
};