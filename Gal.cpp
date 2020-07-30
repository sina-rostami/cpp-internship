#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

class ReverseWorld {
private:
  int n, m, l;
  bool *firstWorld;
  bool *finalWorld;

public:
  ReverseWorld(int n1, int m1, int l1, bool *finalWorld1)
      : n(n1), m(m1), l(l1), finalWorld(finalWorld1) {}
  bool check(string str);
  void makePermutatios(string prefix, int k);
  int neighbourCnt(bool *world, int i, int j);
  void evolution(bool *world);
  void solve() {
    makePermutatios("", m * n);
    cout << "impossible" << endl;
  };
  friend ostream &operator<<(ostream &out, ReverseWorld &r);
};

ostream &operator<<(ostream &out, ReverseWorld &r) {
  for (int i = 0; i < r.n; i++) {
    for (int j = 0; j < r.m; j++)
      out << (*(r.firstWorld + i * r.m + j) ? "*" : ".");
    out << endl;
  }
  out << endl;
  return out;
}

// counts the neighbours of a element in the world
int ReverseWorld::neighbourCnt(bool *world, int i, int j) {
  int lives = 0;
  for (int it = i - 1; it <= i + 1; it++)
    for (int jt = j - 1; jt <= j + 1; jt++)
      if (*(world + (m * ((it + n) % n)) + ((jt + m) % m)))
        lives++;

  if (*(world + i * m + j))
    lives--;
  return lives;
}

void ReverseWorld::evolution(bool *world) {
  bool newWorld[n][m];
  int lives;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      lives = neighbourCnt(world, i, j);

      if (*(world + i * m + j))
        newWorld[i][j] = (lives == 3 || lives == 2);
      else
        newWorld[i][j] = (lives == 3);
    }

  std::copy(&newWorld[0][0], &newWorld[0][0] + m * n, world);
}

// convert str to an array (tempWorld), call evolution on it l time and
// check if it equals to finalarray or not
bool ReverseWorld::check(string str) {
  int onesCntFinal = 0, onesCntTemp = 0;
  bool tempWrold[n * m];
  for (size_t i = 0; i != str.size(); ++i) {
    tempWrold[i] = str[i] - 48;
  }

  for (int i = 0; i < n * m; i++) {
    if (*(finalWorld + i) == 1)
      onesCntFinal++;
    if (*(tempWrold + i) == 1)
      onesCntTemp++;
  }
  if (onesCntFinal - 2 > onesCntTemp || onesCntTemp > onesCntFinal + 3)
    return false;
  for (int i = 0; i < l; i++)
    evolution(tempWrold);

  if (!std::equal(finalWorld, finalWorld + m * n, tempWrold))
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
  int n, m, l;
  cin >> n >> m >> l;
  bool final[n][m];
  string str = "";
  string temp;
  for (int i = 0; i < n; i++) {
    cin >> temp;
    str += temp;
  }
  // store input World to an array and make finalWorld point to it.
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      final[i][j] = str[m * i + j] == '*' ? true : false;

  ReverseWorld reverseWorld(n, m, l, final[0]);
  reverseWorld.solve();
  return 0;
}