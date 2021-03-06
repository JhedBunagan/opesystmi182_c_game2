
#include <ncurses.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define PLAYER_1 1
#define PLAYER_2 2

#define OKAY 5

int updateBoardData(int * boardData, int x, int y, int XorO) {
        /* Check row 1*/
        if(y == 1){
                if(x == 2){
                        if(boardData[0] > 1){
                                boardData[0] = XorO;
                                return 1;
                        }
                }
                else if( x == 6){
                        if(boardData[1] > 1){
                                boardData[1] = XorO;
                                return 1;
                        }
                }
                else if( x == 10){
                        if(boardData[2] > 1){
                                boardData[2] = XorO;
                                return 1;
                        }
                }
        }

        /* Check row 2 */
        else if(y == 3){
                if(x == 2){
                        if(boardData[3] > 1){
                                boardData[3] = XorO;
                                return 1;
                        }
                }
                else if( x == 6){
                        if(boardData[4] > 1){
                                boardData[4] = XorO;
                                return 1;
                        }
                }
                else if( x == 10){
                        if(boardData[5] > 1){
                                boardData[5] = XorO;
                                return 1;
                        }
                }
        }

        /* Check row 3*/
        else if(y == 5){
                if(x == 2){
                        if(boardData[6] > 1){
                                boardData[6] = XorO;
                                return 1;
                        }
                }
                else if( x == 6){
                        if(boardData[7] > 1){
                                boardData[7] = XorO;
                                return 1;
                        }
                }
                else if( x == 10){
                        if(boardData[8] > 1){
                                boardData[8] = XorO;
                                return 1;
                        }
                }
        }
        return 0;
}

int screenY = 0;
int screenX = 0;

void initCurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, screenY, screenX);
}

/*Instructions*/
void ints(){
    char message[] = "Press the Space bar ( _ ) button for Inputing:";
    mvprintw((screenY - 9)/2, (screenX - strlen(message))/2, message);
}


/* Draw game grid */
void drawBoard() {

    int i, h;

    for(i = 0; i <= 6; i++) {
        mvprintw((screenY - 9)/2 + 1 + i, (screenX - 13)/2 + 0, "|");
        mvprintw((screenY - 9)/2 + 1 + i, (screenX - 13)/2 + 4, "|");
        mvprintw((screenY - 9)/2 + 1 + i, (screenX - 13)/2 + 8, "|");
        mvprintw((screenY - 9)/2 + 1 + i, (screenX - 13)/2 + 12,"|");

        if(i % 2 == 0){
            for(h = 0; h <= 12; h++) {
                mvprintw(i, h, "-");
            }
        }
        move(1,2);
    }
    refresh();
    ints();
}

void initBoard(int * boardData) {

    int i;

    for(i=0; i<=8;i++){
        boardData[i] = i+2;
    }
}

int checkWin(int * boardData) {

        /* Check rows */
        if( boardData[0] == boardData[1] && boardData[1] == boardData[2] )
                return 1;
        else if( boardData[3] == boardData[4] && boardData[4] == boardData[5] )
                return 1;
        else if( boardData[6] == boardData[7] && boardData[7] == boardData[8] )
                return 1;

        /* Check cols */
        else if( boardData[0] == boardData[3] && boardData[3] == boardData[6] )
                return 1;
        else if( boardData[1] == boardData[4] && boardData[4] == boardData[7] )
                return 1;
        else if( boardData[2] == boardData[5] && boardData[5] == boardData[8] )
                return 1;

        /* Check diagonals */
        else if( boardData[0] == boardData[4] && boardData[4] == boardData[8] )
                return 1;
        else if( boardData[2] == boardData[4] && boardData[4] == boardData[6] )
                return 1;

        else
                return 0;

        return 0;

}

int playGame() {

        int boardData[9];
        int playerNum = 1;
        int inputChar = ' ';
        int x = 2, y = 1;
        int didWin = 0;
        int canWeMove = 0;
        int nMoves = 0;

        initBoard(boardData);

        /* Move to y=8, x = 0 */
        mvprintw(8, 0, "It is Player 1's turn to place an (X)");
        move(y, x); /* move to origin */
        refresh();

        while (inputChar != 'q') {

                if(nMoves == 9) {
                        mvprintw(10, 0, "Tie game");
                        inputChar = getch();
                        erase();
                        return 3;
                }
                inputChar = getch();

                /* If not spacebar, they are moving */
                if(inputChar != ' '){

                        switch (inputChar){

                                case KEY_UP:
                                        if(y == 3 || y == 5){
                                                move(y-=2, x);
                                        }
                                        break;

                                case KEY_DOWN:
                                        if(y == 1 || y == 3){
                                                move(y+=2, x);
                                        }
                                        break;

                                case KEY_LEFT:
                                        if(x == 10 || x == 6){
                                                move(y, x-=4);
                                        }
                                        break;
                                case KEY_RIGHT:
                                        if(x == 2 || x == 6){
                                                move(y, x+=4);
                                        }
                                        break;
                        }
                }

                else if(playerNum == PLAYER_1 && inputChar == ' '){

                        getyx(stdscr, y, x);
                        canWeMove = updateBoardData(boardData, x, y,1);

                        if(canWeMove == OKAY) {

                                mvprintw(y, x, "X");

                                /* Returns 1 if last move caused winning scenario */
                                didWin = checkWin(boardData);

                                if(didWin){

                                        mvprintw(10,0, "Player 1 wins");
                                        inputChar = getch();
                                        erase();
                                        return TRUE;
                                }
                                nMoves += 1;

                                playerNum = 2;
                                mvprintw(8, 0, "It is Player 2's turn to place an (O)");
                                move(y, x);
                                /*refresh();*/

                        }
                }
                else if(playerNum == PLAYER_2 && inputChar == ' ') {

                        getyx(stdscr, y, x);
                        canWeMove = updateBoardData(boardData, x, y,0);

                        if(canWeMove == OKAY) {

                                mvprintw(y, x, "O");

                                /* Returns 1 if last move caused winning scenario */
                                didWin = checkWin(boardData);

                                if(didWin){

                                        mvprintw(10,0, "Player 2 wins");
                                        inputChar = getch();
                                        erase();
                                        return TRUE;
                                }
                                nMoves += 1;

                                playerNum = 1;
                                mvprintw(8, 0, "It is Player 1's turn to place an (X)");
                                move(y, x);
                                /*refresh();*/
                        }
                }
                refresh();
        }
        return 0;
        endwin();

}

int main() {
    do {
            initCurses();
            drawBoard();
    }

    while (playGame());

    endwin();
    return 0;
}
