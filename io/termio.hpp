#pragma once
#include <termios.h>
#include "io.hpp"

class term_io : public io
{
 public:
	term_io();
	~term_io() override;
	virtual bool kbhit() override;
	void clear_screen() override;
	void exit(const matrix<board_state>& board, int score) override;
	void handle_loss(const matrix<board_state>& board, int score) override;
	void print_board(const matrix<board_state>& board) override;
	int getc() override;
 private:
	struct rgb
	{
		uint8_t r,g,b;
	};
	void init_terminal();
	void restore_terminal();
	void move_cursor(size_t i, size_t j);
	
	struct termios m_old_ttystate;
};




