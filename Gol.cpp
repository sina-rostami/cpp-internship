#include "2d_array.h"
#include <algorithm>
#include <iostream>
using namespace std;

class ReverseWorld {
private:
  std::size_t height, width, evolution_num;
  Array2D<bool> &finalWorld, *firstWorld;

public:
  ReverseWorld(std::size_t height1, std::size_t width1, int evolution_num1,
               Array2D<bool> &finalWorld1)
      : height(height1), width(width1), evolution_num(evolution_num1),
        finalWorld(finalWorld1){};

  bool check(string str);
  void makePermutatios(string prefix, int k);
  std::size_t neighbourCnt(Array2D<bool> &world, std::size_t hindex,
                           std::size_t windex);
  void evolution(Array2D<bool> &world);
  void solve() {
    makePermutatios("", width * height);
    cout << "impossible" << endl;
  };
  friend ostream &operator<<(ostream &out, ReverseWorld &r);
};

ostream &operator<<(ostream &out, ReverseWorld &r) {
  for (std::size_t i = 0; i < r.height; i++) {
    for (std::size_t j = 0; j < r.width; j++)
      out << ((r.firstWorld->operator[](i))[j] ? "*" : ".");
    out << endl;
  }
  out << endl;
  return out;
}

// counts the neighbours of a element in the world
std::size_t ReverseWorld::neighbourCnt(Array2D<bool> &world,
                                       std::size_t height_index,
                                       std::size_t width_index) {
  std::size_t lives = 0;

  for (std::size_t it = height_index + height - 1;
       it <= height_index + height + 1; ++it)
    for (std::size_t jt = width_index + width - 1;
         jt <= width_index + width + 1; ++jt)
      if (world[it % height][jt % width])
        lives++;

  if (world[height_index][width_index])
    lives--;
  return lives;
}

void ReverseWorld::evolution(Array2D<bool> &world) {
  Array2D<bool> newWorld(height, width);
  int lives;

  for (std::size_t i = 0; i != height; ++i)
    for (std::size_t j = 0; j != width; ++j) {
      lives = neighbourCnt(world, i, j);
      if (world[i][j])
        newWorld[i][j] = (lives == 3 || lives == 2);
      else
        newWorld[i][j] = (lives == 3);
    }
  world = newWorld;
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
    if (*(finalWorld[0] + i))
      onesCntFinal++;
    if (*(tempWorld[0] + i))
      onesCntTemp++;
  }

  if (onesCntFinal - 2 > onesCntTemp || onesCntTemp > onesCntFinal + 3) {
    return false;
  }

  for (std::size_t i = 0; i < evolution_num; i++)
    evolution(tempWorld);

  if (finalWorld != tempWorld)
    return false;

  strArrCpy(str, tempWorld[0]);
  firstWorld = &tempWorld;
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
  Array2D<bool> finalWorld(height, width);

  for (std::size_t i = 0; i < height; i++) {
    cin >> temp;
    str += temp;
  }
  // store input World to an array and make finalWorld point to it.
  for (std::size_t i = 0; i < height; i++)
    for (std::size_t j = 0; j < width; j++)
      finalWorld[i][j] = (str[width * i + j] == '*');

  ReverseWorld reverseWorld(height, width, evolution_num, finalWorld);
  reverseWorld.solve();
  return 0;
}