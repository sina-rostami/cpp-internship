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
        std::cout << *((arr_ptr + i * height) + j) << ", ";
      std::cout << std::endl;
    }
  };

  T *operator[](std::size_t hei) { return (arr_ptr + hei * height); };
};