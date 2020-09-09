#include <iostream>
#include <memory>
#include <vector>
using std::size_t;
using std::vector;

template <typename T> class Array2D {
private:
  std::size_t height, width;
  vector<vector<T>> vc;

public:
  Array2D() : Array2D(0, 0){};

  Array2D(const size_t height1, const size_t width1) // constructor
      : height(height1), width(width1), vc(vector<vector<T>>(height)) {
    for (size_t i = 0; i < height; ++i)
      vc[i] = vector<T>(width);
  }

  Array2D(const Array2D<T> &other)
      : height(other.height), width(other.width) { // copy constructor
    vc = other.vc;
  }

  size_t get_height() const { return height; }

  size_t get_width() const { return width; }

  bool operator==(const Array2D<T> &other) const {
    if (width != other.width || height != other.height)
      return false;
    return vc == other.vc;
  }

  bool operator!=(const Array2D<T> &other) const { return !operator==(other); }

  Array2D<T> &operator=(const Array2D<T> &other) {
    if (this == &other) // self assingment
      return *this;

    height = other.height;
    width = other.width;
    vc = other.vc;
    return *this;
  }

  vector<T> &operator[](size_t hei) { return vc.at(hei); }

  const vector<T> &operator[](size_t hei) const { return vc.at(hei); }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Array2D<T> &arr) {
  os << std::endl;
  for (size_t i = 0; i < arr.get_height(); ++i) {
    for (size_t j = 0; j < arr.get_width(); ++j)
      os << arr[i][j] << ", ";
    os << std::endl;
  }
  return os;
}
