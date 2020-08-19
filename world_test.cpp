#include "world.h"
#include <unistd.h>

int main() {
  world w({3, 3});
  world a = w;
  for (int i = 0; i <= 16; i++) {
    w.next_world();
  }
  w.print_world();
  a.print_world();
  a = w;
  a.print_world();
}