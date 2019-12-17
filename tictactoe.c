#include <ncurses.h>
#include "tictactoe.h"

int main() {

	do {

		initCurses();
		drawBoard();

	} while (playGame());

	endwin();
	return(0);
}
