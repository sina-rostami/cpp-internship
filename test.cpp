#include "Array2D_unique_ptr.h"
#include <iostream>

int main() {
  Array2D<int> arr(3, 4);
  arr[0][0] = 1;
  arr[2][3] = 1;

  Array2D<int> arr1(3, 4);
  arr1[0][0] = 1;

  std::cout << arr1;
  arr1 = arr;
  arr1[0][0] = 2;
  std::cout << arr1;
  std::cout << arr;
}