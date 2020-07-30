#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  string str = "0010";
  bool arr1[str.size()];
  cout << sizeof(arr1) << endl;
  // for (size_t i = 0; i < size_t(arr1); ++i) {
  //   cout << i << endl;
  //   arr1[i] = str[i] - 48;
  // }
  cout << arr1[0] << endl;
  cout << arr1[2] << endl;
}