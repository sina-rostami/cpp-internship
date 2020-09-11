#include <gtest/gtest.h>

#include "../Gol.hpp"

void set_array(const std::string &str, Array2D<Universe::HumanState> &arr) {
  for (std::size_t i = 0; i < arr.get_height(); i++)
    for (std::size_t j = 0; j < arr.get_width(); j++)
      arr[i][j] = (str[arr.get_width() * i + j] == '*')
                      ? Universe::HumanState::ALIVE
                      : Universe::HumanState::DEAD;
}

TEST(ExampleTests, test1) {
  const int height = 4, width = 5, ev_num = 10;
  const std::string final_str = "....*..*.*.*..*..*.*",
                    first_str = "..*.*...*.**.***...*";
  Array2D<Universe::HumanState> final_world_arr(height, width),
      first_world_arr(height, width);

  set_array(final_str, final_world_arr);
  set_array(first_str, first_world_arr);

  Gol::GameOfLife gol(ev_num, Universe::World(final_world_arr));
  Gol::Result gol_result = gol.solve();

  if (gol_result == Gol::Result::FOUND)
    EXPECT_EQ(Universe::World(first_world_arr), gol.get_first_world());
  else
    FAIL();
}