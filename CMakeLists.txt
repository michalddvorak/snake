cmake_minimum_required(VERSION 3.20)
project(snake)

set(CMAKE_CXX_STANDARD 17)

add_executable(snake main.cpp utils/matrix.hpp utils/point.cpp utils/point.hpp utils/vec2.cpp utils/vec2.hpp game/game.cpp game/game.hpp io/io.hpp io/termio.cpp io/termio.hpp utils/board_state.hpp)
