#include "Array2D.h"

#include <iostream>

using std::size_t;

class World {

private:
  Array2D<bool> board;

  size_t neighbour_counter(const size_t h_index, const size_t w_index) const {
    size_t lives = 0;

    for (size_t i = h_index + board.get_height() - 1;
         i <= h_index + board.get_height() + 1; ++i)
      for (size_t j = w_index + board.get_width() - 1;
           j <= w_index + board.get_width() + 1; ++j)
        if (board[i % board.get_height()][j % board.get_width()])
          lives++;

    if (board[h_index][w_index])
      lives--;

    return lives;
  };

public:
  World(const Array2D<bool> &worldb) : board(worldb){};

  size_t get_height() const { return board.get_height(); };

  size_t get_width() const { return board.get_width(); };

  void evolution() {
    Array2D<bool> newWorld(board.get_height(), board.get_width());
    int lives;

    for (size_t i = 0; i != board.get_height(); ++i)
      for (size_t j = 0; j != board.get_width(); ++j) {
        lives = neighbour_counter(i, j);
        if (board[i][j])
          newWorld[i][j] = (lives == 3 || lives == 2);
        else
          newWorld[i][j] = (lives == 3);
      }

    board = newWorld;
  };

  bool operator==(const World &other) const { return board == other.board; };

  bool operator!=(const World &other) const { return !operator==(other); };

  void next_world() {
    int max_h = board.get_height() - 1;
    int max_w = board.get_width() - 1;
    if (board[max_h][max_w]) {
      for (size_t i = board.get_height() - 1; i >= 0 && i < board.get_height(); --i) {
        for (size_t j = board.get_width() - 1; j >= 0 && j < board.get_width(); --j) {
          if (!board[i][j]) {
            board[i][j] = 1;
            return;
          }

          board[i][j] = 0;

        }
      }
    } else {
      board[max_h][max_w] = 1;
    }
  };

  friend std::ostream &operator<<(std::ostream &os, const World &w);
};

std::ostream &operator<<(std::ostream &os, const World &w) {
  for (size_t i = 0; i < w.board.get_height(); i++) {
    for (size_t j = 0; j < w.board.get_width(); j++)
      os << (w.board[i][j] ? "*" : ".");
    os << std::endl;
  }
  os << std::endl;

  return os;
};