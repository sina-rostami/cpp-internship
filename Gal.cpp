#include "TwoDimentioalArray.h"
#include <algorithm>
#include <iostream>
using namespace std;

class ReverseWorld {
private:
  std::size_t height, width, evolution_num;
  bool *firstWorld, *finalWorld;

public:
  ReverseWorld(std::size_t height1, std::size_t width1, int evolution_num1,
               bool *finalWorld1)
      : height(height1), width(width1), evolution_num(evolution_num1),
        finalWorld(finalWorld1){};
  bool check(string str);
  void makePermutatios(string prefix, int k);
  std::size_t neighbourCnt(bool *world, int i, int j);
  void evolution(bool *world);
  void solve() {
    makePermutatios("", width * height);
    cout << "impossible" << endl;
  };
  friend ostream &operator<<(ostream &out, ReverseWorld &r);
};

ostream &operator<<(ostream &out, ReverseWorld &r) {
  for (std::size_t i = 0; i < r.height; i++) {
    for (std::size_t j = 0; j < r.width; j++)
      out << (*(r.firstWorld + i * r.width + j) ? "*" : ".");
    out << endl;
  }
  out << endl;
  return out;
}

// counts the neighbours of a element in the world
std::size_t ReverseWorld::neighbourCnt(bool *world, int height_index,
                                       int width_index) {
  std::size_t lives = 0;

  for (int it = height_index - 1; it <= height_index + 1; ++it)
    for (int jt = width_index - 1; jt <= width_index + 1; ++jt)
      if (*(world + (width * ((it + height) % height)) +
            ((jt + width) % width)))
        lives++;

  if (*(world + height_index * width + width_index))
    lives--;
  return lives;
}

void ReverseWorld::evolution(bool *world) {
  bool newWorld[height * width];
  int lives;

  for (std::size_t i = 0; i != height; ++i)
    for (std::size_t j = 0; j != width; ++j) {
      lives = neighbourCnt(world, i, j);

      if (*(world + i * width + j))
        *(newWorld + i * width + j) = (lives == 3 || lives == 2);
      else
        *(newWorld + i * width + j) = (lives == 3);
    }
  std::copy(newWorld, newWorld + width * height, world);
}

void strArrCpy(string str, bool *arr) {
  for (std::size_t i = 0; i != str.size(); ++i) {
    arr[i] = str[i] - 48;
  }
}

// convert str to an array (tempWorld), call evolution on it l time and
// check if it equals to finalarray or not
bool ReverseWorld::check(string str) {
  std::size_t onesCntFinal = 0, onesCntTemp = 0;
  Array2D<bool> tempWorld(height, width);
  strArrCpy(str, tempWorld[0]);

  for (std::size_t i = 0; i < height * width; i++) {
    if (*(finalWorld + i) == 1)
      onesCntFinal++;
    if (*(tempWorld[0] + i) == 1)
      onesCntTemp++;
  }
  if (onesCntFinal - 2 > onesCntTemp || onesCntTemp > onesCntFinal + 3) {
    return false;
  }
  for (std::size_t i = 0; i < evolution_num; i++)
    evolution(tempWorld[0]);

  if (!std::equal(finalWorld, finalWorld + width * height, tempWorld[0])) {
    return false;
  }

  strArrCpy(str, tempWorld[0]);
  firstWorld = tempWorld[0];
  cout << *this;
  exit(0);
}

// make every permutation of that world and pass it to the check function
void ReverseWorld::makePermutatios(string prefix, int k) {
  if (k == 0) {
    check(prefix);
    return;
  }
  for (std::size_t i = 0; i < 2; i++) {
    string newPrefix;
    newPrefix = prefix + (i == 0 ? '0' : '1');
    makePermutatios(newPrefix, k - 1);
  }
}

int main() {
  std::size_t height, width, evolution_num;
  string str = "", temp;
  cin >> height >> width >> evolution_num;
  bool finalWorld[height][width];
  
  for (std::size_t i = 0; i < height; i++) {
    cin >> temp;
    str += temp;
  }
  // store input World to an array and make finalWorld point to it.
  for (std::size_t i = 0; i < height; i++)
    for (std::size_t j = 0; j < width; j++)
      finalWorld[i][j] = str[width * i + j] == '*' ? true : false;

  ReverseWorld reverseWorld(height, width, evolution_num, finalWorld[0]);
  reverseWorld.solve();
  return 0;
}