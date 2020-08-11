#include "TwoDimentioalArray.h"
#include <iostream>
using namespace std;

int main() {
  Array2D<bool> arr(3, 3);

  arr.print();
  arr[0][0] = 1;
  arr[0][1] = 1;
  arr[1][0] = 1;
  arr[2][0] = 1;
  int onesCntTemp = 0;
  for (std::size_t i = 0; i < 9; i++) {
    if (*(arr[0] + i) == 1)
      onesCntTemp++;
  }
  cout << onesCntTemp << endl;
  arr.print();
}