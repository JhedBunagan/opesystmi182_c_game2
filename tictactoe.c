#include <ncurses.h>
#include "tictactoe.h"

//int screenY = 0, screenX = 0;

int main() {
 	initscr();
	getmaxyx(stdscr, screenY, screenX);
	endwin();
  	return 0;

do {

	initCurses();
	drawBoard();

} 
while (playGame());

	endwin();
	return(0);
}
