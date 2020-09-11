#include "Gol.hpp"
#include <iostream>

int main() {
  std::size_t height, width, evolution_num;
  std::string str = "", temp;
  std::cin >> height >> width >> evolution_num;
  Array2D<Universe::HumanState> final_world(height, width);

  for (std::size_t i = 0; i < height; i++) {
    std::cin >> temp;
    str += temp;
  }

  // store input World to an array and make finalWorld point to it.
  for (std::size_t i = 0; i < height; i++)
    for (std::size_t j = 0; j < width; j++)
      final_world[i][j] = (str[width * i + j] == '*')
                              ? Universe::HumanState::ALIVE
                              : Universe::HumanState::DEAD;

  Gol::GameOfLife gol(evolution_num, Universe::World(final_world));
  Gol::Result gol_result = gol.solve();

  if (gol_result == Gol::Result::FOUND)
    std::cout << gol.get_first_world();
  else
    std::cout << "impossible" << std::endl;

  return 0;
}