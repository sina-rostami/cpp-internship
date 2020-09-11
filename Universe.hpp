#include "Array2D.hpp"


namespace Universe {
enum class HumanState { DEAD, ALIVE };
class World {
private:
  Array2D<HumanState> board;

  std::size_t neighbour_counter(const std::size_t h_index,
                                const std::size_t w_index) const {
    std::size_t lives = 0;

    for (std::size_t i = h_index + board.get_height() - 1;
         i <= h_index + board.get_height() + 1; ++i)
      for (std::size_t j = w_index + board.get_width() - 1;
           j <= w_index + board.get_width() + 1; ++j)
        if (board[i % get_height()][j % get_width()] == HumanState::ALIVE)
          lives++;

    if (board[h_index][w_index] == HumanState::ALIVE)
      lives--;

    return lives;
  };

public:
  World(const Array2D<HumanState> &worldb) : board(worldb){};

  std::size_t get_height() const { return board.get_height(); };

  std::size_t get_width() const { return board.get_width(); };

  void evolution() {
    Array2D<HumanState> newWorld(board.get_height(), board.get_width());
    int lives;

    for (std::size_t i = 0; i != board.get_height(); ++i)
      for (std::size_t j = 0; j != board.get_width(); ++j) {
        lives = neighbour_counter(i, j);
        if (board[i][j] == HumanState::ALIVE)
          newWorld[i][j] =
              (lives == 3 || lives == 2) ? HumanState::ALIVE : HumanState::DEAD;
        else
          newWorld[i][j] = (lives == 3) ? HumanState::ALIVE : HumanState::DEAD;
      }

    board = newWorld;
  };

  bool operator==(const World &other) const { return board == other.board; };

  bool operator!=(const World &other) const { return !operator==(other); };

  void next_world() {
    int max_h = get_height() - 1;
    int max_w = get_width() - 1;

    if (board[max_h][max_w] == HumanState::ALIVE) {
      for (std::size_t i = get_height() - 1; i >= 0 && i < get_height(); --i) {
        for (std::size_t j = get_width() - 1; j >= 0 && j < get_width(); --j) {
          if (board[i][j] == HumanState::DEAD) {
            board[i][j] = HumanState::ALIVE;
            return;
          }

          board[i][j] = HumanState::DEAD;
        }
      }
    } else
      board[max_h][max_w] = HumanState::ALIVE;
  };

  friend std::ostream &operator<<(std::ostream &os, const World &w);
};

std::ostream &operator<<(std::ostream &os, const World &w) {
  for (std::size_t i = 0; i < w.board.get_height(); i++) {
    for (std::size_t j = 0; j < w.board.get_width(); j++)
      os << (w.board[i][j] == HumanState::ALIVE ? "*" : ".");
    os << std::endl;
  }
  os << std::endl;

  return os;
}
}; // namespace Universe
