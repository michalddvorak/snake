#include "game/game.hpp"
#include "io/termio.hpp"

//todo high scores
//todo options
//todo increasing difficulty of snake
int main()
{
	term_io io;
	game g(50, 50, io);
	g.run();
	return 0;
}
