#include <iterator>
#include <vector>

template <typename T> class Array2D {
private:
  std::size_t height, width;
  std::vector<T> vc;

public:
  Array2D() : Array2D(0, 0){};

  Array2D(const std::size_t height1, const std::size_t width1) // constructor
      : height(height1), width(width1), vc(height * width) {}

  std::size_t get_height() const { return height; }

  std::size_t get_width() const { return width; }

  bool operator==(const Array2D<T> &other) const {
    return height == other.height && width == other.width && vc == other.vc;
  }

  typename std::vector<T>::iterator operator[](std::size_t hei) {
    return vc.begin() + hei * width;
  }
  typename std::vector<T>::const_iterator operator[](std::size_t hei) const {
    return vc.cbegin() + hei * width;
  }
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
