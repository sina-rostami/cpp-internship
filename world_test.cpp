#include "world.h"
#include <unistd.h>
int main() {
    world w(3, 3);
    for (int i = 0; i < 16; i++)
    {
        w.print_world();
        w++;
        sleep(1);
    }
}