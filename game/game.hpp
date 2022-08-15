#pragma once

#include <deque>
#include <random>
#include "../io/io.hpp"
#include "../utils/point.hpp"
#include "../utils/board_state.hpp"

class game
{
 public:
	game(size_t rows, size_t cols, io& io);
	void run();
 private:
	int score() const;
	void put_random_food();
	bool generate_random_empty_index(size_t& r, size_t& c);
	enum class update_result
	{
		MOVE,
		FAIL,
		PROLONG
	};
	update_result update_snake(const vec2& direction);
	matrix<board_state> m_board;
	std::deque<point> m_snake;
	std::mt19937 m_gen = std::mt19937(std::random_device {}());
	io& m_io;
};




