#include <unistd.h>
#include <sys/time.h>
#include <cstdio>
#include <iostream>
#include "termio.hpp"


term_io::term_io()
{
	init_terminal();
}
term_io::~term_io()
{
	restore_terminal();
}
bool term_io::kbhit()
{
	struct timeval tv;
	fd_set fds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv);
	return FD_ISSET(STDIN_FILENO, &fds);
}
int term_io::getc()
{
	return std::getc(stdin);
}
void term_io::init_terminal()
{
	tcgetattr(STDIN_FILENO, &m_old_ttystate); //store old ttystate
	struct termios ttystate;
	tcgetattr(STDIN_FILENO, &ttystate);
	ttystate.c_lflag &= ~ICANON; //disable canonical mode
	ttystate.c_cc[VMIN] = 1; //react on 1 character
	ttystate.c_lflag &= ~ECHO; //don't echo pressed characters
	tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

void term_io::restore_terminal()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &m_old_ttystate);
}
void term_io::clear_screen()
{
	std::cout << "\033[2J";
}
void term_io::move_cursor(size_t i, size_t j)
{
	std::cout << "\033[" << i << ';' << j << 'H';
}

void term_io::print_board(const matrix<board_state>& board)
{
	move_cursor(1, 1);
	for(size_t j = 0; j < board.num_cols() + 2; ++j)
		std::cout << 'X';
	std::cout << '\n';
	
	for(size_t i = 0; i < board.num_rows(); ++i)
	{
		std::cout << 'X';
		for(size_t j = 0; j < board.num_cols(); ++j)
		{
			switch(board[i][j])
			{
				case board_state::EMPTY:
					std::cout << ' ';
					break;
				case board_state::SNAKE:
					std::cout << 'o';
					break;
				case board_state::FOOD:
					std::cout << "\033[5m+\033[0m";
					break;
			}
		}
		std::cout << "X\n";
	}
	
	for(size_t j = 0; j < board.num_cols() + 2; ++j)
		std::cout << 'X';
	std::cout << '\n';
	
	std::cout.flush();
}
void term_io::exit(const matrix<board_state>& board, int score)
{
	clear_screen();
	print_board(board);
	std::cout << "exited, your score: " << score << std::endl;
}

void term_io::handle_loss(const matrix<board_state>& board, int score)
{
	clear_screen();
	print_board(board);
	std::cout << "you lost, your score: " << score << std::endl;
}
