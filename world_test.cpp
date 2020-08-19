#include "world.h"
#include <unistd.h>

int main() {
  world w({3, 3});
  int i = 9;
  int ai = 1 << i;
  std::cout << i << std::endl << ai << std::endl;
  for (int i = 0; i <= 16; i++) {
    w.next_world();
  }
  world ww(w);
  ww.print_world();
}