#include "Universe.hpp"

namespace Gol {

enum class Result { NOT_FOUND, FOUND };
class GameOfLife {
private:
  const std::size_t evolution_num;
  const Universe::World final_world;
  Universe::World first_world;

public:
  GameOfLife(const std::size_t ev_num, const Universe::World final_world1)
      : evolution_num(ev_num), final_world(final_world1),
        first_world(Universe::World(Array2D<Universe::HumanState>(
            final_world1.get_height(), final_world1.get_width()))){};

  Universe::World do_evolutions(Universe::World temp_world) {
    for (std::size_t i = 0; i < evolution_num; i++)
      temp_world.evolution();
    return temp_world;
  }

  Result solve() {
    const std::size_t max_size =
        1 << first_world.get_height() * first_world.get_width();

    for (std::size_t i = 0; i < max_size; i++) {
      first_world.next_world();

      if (do_evolutions(first_world) == final_world) {
        return Result::FOUND;
      }
    }
    return Result::NOT_FOUND;
  };

  Universe::World get_first_world() const { return first_world; }
};

}; // namespace Gol