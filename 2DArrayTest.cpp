#include <iostream>
#include "TwoDimentioalArray.h"
using namespace std;

int main() {
  Array2D<int> arr(3, 3);

  arr.print();
  arr[0][0] = 1;
  arr.print();
}