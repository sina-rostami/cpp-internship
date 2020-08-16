#include "world.h"
#include <unistd.h>
int main() {
    world w(3, 3);
    for (int i = 0; i >= 0 ; i++)
    {
        w.print_world();
        w++;
        usleep(100000);
    }
}