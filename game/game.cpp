#include <chrono>
#include <thread>
#include <map>
#include "game.hpp"

game::game(size_t rows, size_t cols, io& io) : m_board(rows, cols),
											   m_snake({{static_cast<int>(rows / 2), static_cast<int>(cols / 2)}}),
											   m_io(io)
{
	m_board[m_snake.front().y][m_snake.front().x] = board_state::SNAKE;
}

void game::run()
{
	m_io.clear_screen();
	put_random_food();
	m_io.print_board(m_board);
	size_t delay_ms = 100;
	const static vec2 RIGHT = {1, 0};
	const static vec2 LEFT = {-1, 0};
	const static vec2 UP = {0, -1};
	const static vec2 DOWN = {0, 1};
	const static std::map<int, vec2> direction_handler = {
			{'a', LEFT},
			{'d', RIGHT},
			{'s', DOWN},
			{'w', UP}
	};
	vec2 direction = RIGHT;
	while(true)
	{

rd_again:
		if(m_io.kbhit())
		{
			int c = m_io.getc();
			switch(c)
			{
				case 'w':
				case 'a':
				case 's':
				case 'd':
					if(direction == direction_handler.at(c))
						goto rd_again;
					direction = direction_handler.at(c);
					break;
				case 'x':
				case 'q':
					m_io.exit(m_board, score());
					return;
				case '+':
					if(delay_ms >= 10)
						delay_ms -= 10;
					break;
				case '-':
					delay_ms += 10;
					break;
			}
		}
		
		
		switch(update_snake(direction))
		{
			case update_result::MOVE:
				break;
			case update_result::PROLONG:
				put_random_food();
				break;
			default://case update_result::FAIL:
				m_io.handle_loss(m_board, score());
				return;
		}
		
		m_io.print_board(m_board);
		
		std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
	}
}
game::update_result game::update_snake(const vec2& direction)
{
	point new_head = m_snake.front() + direction;
	
	//walls
	if(!(0 <= new_head.x && new_head.x < static_cast<int>(m_board.num_cols())
		 &&
		 0 <= new_head.y && new_head.y < static_cast<int>(m_board.num_rows()))
			)
		return update_result::FAIL;
	
	switch(m_board[new_head.y][new_head.x])
	{
		case board_state::EMPTY:
			m_snake.push_front(new_head);
			m_board[new_head.y][new_head.x] = board_state::SNAKE;
			m_board[m_snake.back().y][m_snake.back().x] = board_state::EMPTY;
			m_snake.pop_back();
			return update_result::MOVE;
		case board_state::FOOD:
			m_snake.push_front(new_head);
			m_board[new_head.y][new_head.x] = board_state::SNAKE;
			return update_result::PROLONG;
		default://case board_state::SNAKE:
			return update_result::FAIL;
	}
}
int game::score() const
{
	return static_cast<int>(m_snake.size());
}
void game::put_random_food()
{
	size_t i, j;
	if(!generate_random_empty_index(i, j))
		return;
	m_board[i][j] = board_state::FOOD;
}
bool game::generate_random_empty_index(size_t& r, size_t& c)
{
	size_t cnt = 0;
	for(size_t i = 0; i < m_board.num_rows(); ++i)
		for(size_t j = 0; j < m_board.num_cols(); ++j)
			if(m_board[i][j] == board_state::EMPTY)
				cnt++;
	if(cnt == 0)
		return false;
	
	std::uniform_int_distribution<typename std::mt19937::result_type> distr(0, cnt - 1);
	auto offset = distr(m_gen);
	
	for(size_t i = 0; i < m_board.num_rows(); ++i)
		for(size_t j = 0; j < m_board.num_cols(); ++j)
			if(m_board[i][j] == board_state::EMPTY && offset-- == 0)
			{
				r = i;
				c = j;
				return true;
			}
	return true;
}
