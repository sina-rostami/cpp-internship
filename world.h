#include "2d_array.h"
#include <iostream>
using stdsize = std::size_t;

class world {

private:
  stdsize height, width;
  Array2D<bool> world_board;

public:
  world(stdsize height1, stdsize width1, Array2D<bool> worldb)
      : height(height1), width(width1), world_board(worldb){};

  world(stdsize height1, stdsize width1)
      : height(height1), width(width1),
        world_board(Array2D<bool>(height, width)){};

  world(const world &other) // copy constructor
      : height(other.height), width(other.width),
        world_board(other.world_board){};

  void evolution() {
    Array2D<bool> newWorld(height, width);
    int lives;

    for (std::size_t i = 0; i != height; ++i)
      for (std::size_t j = 0; j != width; ++j) {
        lives = neighbour_counter(i, j);
        if (world_board[i][j])
          newWorld[i][j] = (lives == 3 || lives == 2);
        else
          newWorld[i][j] = (lives == 3);
      }

    world_board = newWorld;
  };

  int neighbour_counter(stdsize h_index, stdsize w_index) {
    stdsize lives = 0;

    for (stdsize it = h_index + height - 1; it <= h_index + height + 1; ++it)
      for (stdsize jt = w_index + width - 1; jt <= w_index + width + 1; ++jt)
        if (world_board[it % height][jt % width])
          lives++;

    if (world_board[h_index][w_index])
      lives--;

    return lives;
  };

  world &operator=(const world &other) {
    height = other.height;
    width = other.width;
    world_board = other.world_board;

    return *this;
  };

  bool operator!=(const world &other) const {
    if (height != other.height || width != other.width ||
        world_board != other.world_board)
      return true;

    return false;
  };

  world &operator++(int) {
    int max_h = height - 1;
    int max_w = width - 1;

    if (world_board[max_h][max_w]) {

      for (ssize_t i = height * width - 1; i > 0; --i) {

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
    for (std::size_t i = 0; i < height; i++) {
      for (std::size_t j = 0; j < width; j++)
        std::cout << (world_board[i][j] ? "*" : ".");
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
};