#include "2d_array.h"
#include <iostream>
using namespace std;
void strArrCpy(string str, bool *arr) {
  for (std::size_t i = 0; i != str.size(); ++i) {
    arr[i] = str[i] - 48;
  }
}

int main() {
  Array2D<bool> arr(3, 3);
  arr[0][0] = 1;
  arr[0][1] = 1;
  arr[1][0] = 1;
  arr[2][0] = 1;
  arr[0][4] = 1;
  arr.print();
}