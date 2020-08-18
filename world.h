#include "2d_array.h"
#include <iostream>
using stdsize = std::size_t;

class world {

private:
  Array2D<bool> world_board;

  stdsize neighbour_counter(stdsize h_index, stdsize w_index) {
    stdsize lives = 0;

    for (stdsize it = h_index + world_board.get_height() - 1;
         it <= h_index + world_board.get_height() + 1; ++it)
      for (stdsize jt = w_index + world_board.get_width() - 1;
           jt <= w_index + world_board.get_width() + 1; ++jt)
        if (world_board[it % world_board.get_height()]
                       [jt % world_board.get_width()])
          lives++;

    if (world_board[h_index][w_index])
      lives--;

    return lives;
  };

public:
  world(const Array2D<bool> worldb) : world_board(worldb){};

  ssize_t get_height() const { return world_board.get_height(); };

  ssize_t get_width() const { return world_board.get_width(); };

  void evolution() {
    Array2D<bool> newWorld(world_board.get_height(), world_board.get_width());
    int lives;

    for (std::size_t i = 0; i != world_board.get_height(); ++i)
      for (std::size_t j = 0; j != world_board.get_width(); ++j) {
        lives = neighbour_counter(i, j);
        if (world_board[i][j])
          newWorld[i][j] = (lives == 3 || lives == 2);
        else
          newWorld[i][j] = (lives == 3);
      }

    world_board = newWorld;
  };

  world &operator=(const world &other) {
    world_board = other.world_board;

    return *this;
  };

  bool operator==(const world &other) const {
    return world_board == other.world_board;
  };

  bool operator!=(const world &other) const { return !operator==(other); };

  world &operator++(int) {
    int max_h = world_board.get_height() - 1;
    int max_w = world_board.get_width() - 1;

    if (world_board[max_h][max_w]) {
      for (ssize_t i = world_board.get_height() * world_board.get_width() - 1;
           i > 0; --i) {
        if (!world_board[0][i]) {
          world_board[0][i] = true;
          break;
        }

        world_board[0][i] = false;
      }
    } else {
      world_board[max_h][max_w] = true;
    }

    return *this;
  };

  void print_world() {
    for (std::size_t i = 0; i < world_board.get_height(); i++) {
      for (std::size_t j = 0; j < world_board.get_width(); j++)
        std::cout << (world_board[i][j] ? "*" : ".");
      std::cout << std::endl;
    }
    std::cout << std::endl;
  };
};