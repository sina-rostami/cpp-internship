#include "world.h"
#include <cmath>
using std::cin;
using std::cout;
using std::string;

class game_of_life {
private:
  std::size_t evolution_num;
  world first_world, final_world;

public:
  game_of_life(const std::size_t ev_num, const world final_world1)
      : evolution_num(ev_num), final_world(final_world1),
        first_world(world(Array2D<bool>(final_world1.get_height(),
                                        final_world1.get_width()))){};

  world do_evolutions(world temp_world) {
    for (std::size_t i = 0; i < evolution_num; i++)
      temp_world.evolution();
    return temp_world;
  }

  void handle_found() { first_world.print_world(); }

  void handle_not_found() { cout << "impossible" << std::endl; };

  void solve() {
    std::size_t max_size =
        1 << first_world.get_height() * first_world.get_width();

    for (std::size_t i = 0; i < max_size; i++) {
      first_world.next_world();
      if (do_evolutions(first_world) == final_world) {
        handle_found();
        return;
      }
    }
    handle_not_found();
  };
};

int main() {
  std::size_t height, width, evolution_num;
  string str = "", temp;
  cin >> height >> width >> evolution_num;
  Array2D<bool> final_world(height, width);

  for (std::size_t i = 0; i < height; i++) {
    cin >> temp;
    str += temp;
  }

  // store input World to an array and make finalWorld point to it.
  for (std::size_t i = 0; i < height; i++)
    for (std::size_t j = 0; j < width; j++)
      final_world[i][j] = (str[width * i + j] == '*');
  game_of_life gol(evolution_num, world(final_world));
  gol.solve();
}