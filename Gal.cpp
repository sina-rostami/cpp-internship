#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

class ReverseWorld {
private:
  std::size_t height, width;
  int l;
  bool *firstWorld;
  bool *finalWorld;

public:
  ReverseWorld(std::size_t height1, std::size_t width1, int l1,
               bool *finalWorld1)
      : height(height1), width(width1), l(l1), finalWorld(finalWorld1) {}
  bool check(string str);
  void makePermutatios(string prefix, int k);
  int neighbourCnt(bool *world, int i, int j);
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
int ReverseWorld::neighbourCnt(bool *world, int i, int j) {
  int lives = 0;
  for (int it = i - 1; it <= i + 1; ++it)
    for (int jt = j - 1; jt <= j + 1; ++jt)
      if (*(world + (width * ((it + height) % height)) +
            ((jt + width) % width)))
        lives++;

  if (*(world + i * width + j))
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

// convert str to an array (tempWorld), call evolution on it l time and
// check if it equals to finalarray or not
bool ReverseWorld::check(string str) {
  int onesCntFinal = 0, onesCntTemp = 0;
  bool tempWrold[height * width];

  for (std::size_t i = 0; i != str.size(); ++i) {
    tempWrold[i] = str[i] - 48;
  }

  for (std::size_t i = 0; i < height * width; i++) {
    if (*(finalWorld + i) == 1)
      onesCntFinal++;
    if (*(tempWrold + i) == 1)
      onesCntTemp++;
  }
  if (onesCntFinal - 2 > onesCntTemp || onesCntTemp > onesCntFinal + 3)
    return false;
  for (int i = 0; i < l; i++)
    evolution(tempWrold);

  if (!std::equal(finalWorld, finalWorld + width * height, tempWrold))
    return false;

  for (size_t i = 0; i != str.size(); ++i) {
    tempWrold[i] = str[i] - 48;
  }
  firstWorld = tempWrold;
  cout << *this;
  exit(0);
}

// make every permutation of that world and pass it to the check function
void ReverseWorld::makePermutatios(string prefix, int k) {
  if (k == 0) {
    check(prefix);
    return;
  }
  for (int i = 0; i < 2; i++) {
    string newPrefix;
    newPrefix = prefix + (i == 0 ? '0' : '1');
    makePermutatios(newPrefix, k - 1);
  }
}

int main() {
  std::size_t n, width;
  int l;
  cin >> n >> width >> l;
  bool final[n][width];
  string str = "";
  string temp;
  for (int i = 0; i < n; i++) {
    cin >> temp;
    str += temp;
  }
  // store input World to an array and make finalWorld point to it.
  for (std::size_t i = 0; i < n; i++)
    for (std::size_t j = 0; j < width; j++)
      final[i][j] = str[width * i + j] == '*' ? true : false;

  ReverseWorld reverseWorld(n, width, l, final[0]);
  reverseWorld.solve();
  return 0;
}