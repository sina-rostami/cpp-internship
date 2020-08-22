#include "world.h"
#include <type_traits>
#include <unistd.h>

enum month { jan = 1, aa, bb };

using std::cout;
using std::endl;

int main() {
  world w({3, 3});
  world a = w;
  for (int i = 0; i <= 16; i++)
    w.next_world();
  
  w.print_world();
  a.print_world();
  a = w;
  a.print_world();
  return 0;
}