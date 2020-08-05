#include <iostream>
#include "TwoDimentioalArray.h"
using namespace std;

int main() {
  Array2D<int> arr(3, 3);

  arr.print();
  try {
    arr(0, 0) = 1;
    arr(2, 2) = 1;
    arr(3, 3) = 1;
  } catch (out_of_bounds_Exception &e) {
    cout << "out of bounds" << endl;
  }
  arr.print();
}