all:
	gcc -Wall -ansi tictactoe.c tictactoefunctions.c -Iinclude -o TicTacToe -lncurses

clean:
	rm tictactoe
