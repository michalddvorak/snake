#pragma once

#include "../utils/matrix.hpp"
#include "../utils/board_state.hpp"

class io
{
 public:
	virtual ~io() = default;
	virtual void clear_screen() = 0;
	virtual void print_board(const matrix<board_state>& board) = 0;
	virtual void handle_loss(const matrix<board_state>& board, int score) = 0;
	virtual void exit(const matrix<board_state>& board, int score) = 0;
	virtual bool kbhit() = 0;
	virtual int getc() = 0;
};

