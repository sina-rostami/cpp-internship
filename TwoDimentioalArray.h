#include <iostream>

template <typename T> class Array2D {
private:
  std::size_t height, width;
  T *arr_ptr;

public:
  Array2D(std::size_t height1, std::size_t width1)
      : height(height1), width(width1), arr_ptr(new T[height * width]){};

  ~Array2D() { delete[] arr_ptr; }

  void print() {
    std::cout << std::endl;
    for (std::size_t i = 0; i < height; ++i) {
      for (std::size_t j = 0; j < width; ++j)
        std::cout << (this->operator[](i))[j] << ", ";
      std::cout << std::endl;
    }
  };

  bool operator==(Array2D<T> &other) {
    if (this->width != other.width || this->height != other.height)
      return false;
    for (std::size_t i = 0; i < this->height; ++i) {
      for (std::size_t j = 0; j < this->width; ++j) {
        if ((this->operator[](i))[j] != other[i][j])
          return false;
      }
    }
    return true;
  }

  Array2D<T> &operator=(Array2D<T> &other) {
    std::copy(other.arr_ptr, other.arr_ptr + other.height * other.width, arr_ptr);
    return *this;
  }

  T *operator[](std::size_t hei) { return (arr_ptr + hei * width); };
};