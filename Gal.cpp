#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

class ReverseWorld {
private:
  int n, m, l;
  int *finalWorld;

public:
  ReverseWorld(int n1, int m1, int l1, int *finalWorld1)
      : n(n1), m(m1), l(l1), finalWorld(finalWorld1) {}
  bool check(string str);
  void makePermutatios(string prefix, int k);
  int neighbourCnt(int *world, int i, int j);
  void evolution(int *world);
  void drawWorld(int *world);
  void solve() {
    makePermutatios("", m * n);
    cout << "impossible" << endl;
  };
};


// counts the neighbours of a element in the world
int ReverseWorld::neighbourCnt(int *world, int i, int j) {
  int lives = 0;
  for (int it = i - 1; it <= i + 1; it++)
    for (int jt = j - 1; jt <= j + 1; jt++)
      if (*(world + (m * ((it + n) % n)) + ((jt + m) % m)))
        lives++;

  if (*(world + i * m + j))
    lives--;
  return lives;
}

void ReverseWorld::evolution(int *world) {
  int newWorld[n][m];
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

void ReverseWorld::drawWorld(int *world) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      cout << (*(world + i * m + j) ? "*" : ".");
    printf("\n");
  }
  printf("\n");
}

// convert str to an array (tempWorld), call evolution on it l time and
// check if it equals to finalarray or not
bool ReverseWorld::check(string str) {
  int onesCntFinal = 0, onesCntTemp = 0;
  int tempWrold[n][m];

  std::copy(str.begin(), str.end(), tempWrold[0]);
  std::transform(tempWrold[0], tempWrold[0] + m * n, tempWrold[0],
                 [](int a) -> int { return a - 48; });

  for (int i = 0; i < n * m; i++) {
    if (*(finalWorld + i) == 1)
      onesCntFinal++;
    if (*(*tempWrold + i) == 1)
      onesCntTemp++;
  }
  if (onesCntFinal - 2 > onesCntTemp || onesCntTemp > onesCntFinal + 3)
    return false;
  for (int i = 0; i < l; i++)
    evolution(tempWrold[0]);

  if (!std::equal(finalWorld, finalWorld + m * n, tempWrold[0]))
    return false;

  std::copy(str.begin(), str.end(), tempWrold[0]);
  std::transform(tempWrold[0], tempWrold[0] + m * n, tempWrold[0],
                 [](int a) -> int { return a - 48; });
                 
  drawWorld(tempWrold[0]);
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
  int final[n][m];
  string str = "";
  string temp;
  for (int i = 0; i < n; i++) {
    cin >> temp;
    str += temp;
  }
  // store input World to an array and make finalWorld point to it.
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      final[i][j] = str[m * i + j] == '*' ? 1 : 0;

  ReverseWorld reverseWorld(n, m, l, final[0]);
  reverseWorld.solve();
  return 0;
}