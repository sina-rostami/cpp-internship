#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  int arr1[] = {1, 2, 3, 5, 4, 7};
  int arr2[] = {1, 2, 3, 5, 4, 8};
  string str = "010101";
  std::copy(str.begin(), str.end(), arr1, [](char c) -> int { return c - 48; });
  std::transform(arr1, arr1 + 6, arr1, [](int a) -> int { return a - 48; });
  cout << arr1[1] << endl;
}