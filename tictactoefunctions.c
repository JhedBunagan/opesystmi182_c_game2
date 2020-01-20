#include <ncurses.h>
#include <string.h>


#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define PLAYER_1 1
#define PLAYER_2 2


#define OKAY 5

void initCurses();
void drawBoard();
void initBoard(int * boardData);
int playGame();
int updateBoardData(int * boardData, int x, int y, int XorO);
int checkWin(int * boardData);










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
    char exits[] = "Press 'Ctrl + C' to EXIT"; 
    mvprintw((screenY - 20)/2, (screenX - strlen(message))/2, message);
    
    /*exit*/
    mvprintw((screenY - 18)/2, (screenX - strlen(exits))/2, exits);
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
                mvprintw(i+18, h+77, "-");
            }
        }
        move(1,2);
    }
    refresh();
    ints();
}

void initBoard(int * boardData){

    int i;

    for(i=0; i<=8;i++){
        boardData[i] = i+2;
    }
}

int playGame() {

        int boardData[9];
        int playerNum = 1;
        int inputChar = ' ';
        int pgX = 2, pgY = 1;
        int didWin = 0;
        int canWeMove = 0;
        int nMoves = 0;

        char pOneTurn[]="It is Player 1's turn to place an (X)";
        char pTwoTurn[]="It is Player 2's turn to place an (O)";
        char tieGame[]= "Tie Game";
        char oneWin[]= "Player 1 WIN!";
        char twoWin[]= "Player 2 WIN!";
        char playAg[]= "Press any key to play again.";


        initBoard(boardData);

        
        /* Move to y=8, x = 0 */
        
        mvprintw((screenY - 10)/2, (screenX - strlen(pOneTurn))/2, pOneTurn);
        
        move(pgY, pgX); /* move to origin */
        refresh();

        while (inputChar != 'q') {

                if(nMoves == 9) {
                        mvprintw((screenY - 10)+ 1/2, (screenX - strlen(tieGame))/2, tieGame);
                        mvprintw((screenY - 8)+ 1/2, (screenX - strlen(playAg))/2, playAg);
                        inputChar = getch();
                        erase();
                        return 3;
                }
                inputChar = getch();

                /* If not spacebar, they are moving */
                if(inputChar != ' '){

                        switch (inputChar){

                                case KEY_UP:
                                        if(pgY == 3 || pgY == 5){
                                                move(pgY-=2, pgX);
                                        }
                                        break;

                                case KEY_DOWN:
                                        if(pgY == 1 || pgY == 3){
                                                move(pgY+=2, pgX);
                                        }
                                        break;

                                case KEY_LEFT:
                                        if(pgX == 10 || pgX == 6){
                                                move(pgY, pgX-=4);
                                        }
                                        break;
                                case KEY_RIGHT:
                                        if(pgX == 2 || pgX == 6){
                                                move(pgY, pgX+=4);
                                        }
                                        break;
                        }
                }

                else if(playerNum == PLAYER_1 && inputChar == ' '){

                        getyx(stdscr, pgY, pgX);
                        canWeMove = updateBoardData(boardData, pgX, pgY,1);

                        if(canWeMove == OKAY) {

                                mvprintw(pgY, pgX, "X");

                                /* Returns 1 if last move caused winning scenario */
                                didWin = checkWin(boardData);

                                if(didWin){

                                        mvprintw((screenY - 10)+ 1/2, (screenX - strlen(oneWin))/2, oneWin);
                                        mvprintw((screenY - 8)+ 1/2, (screenX - strlen(playAg))/2, playAg);

                                        inputChar = getch();
                                        erase();
                                        return TRUE;
                                }
                                nMoves += 1;

                                playerNum = 2;
                                /*p2 mag lagay ng O*/
                                mvprintw((screenY - 10)/2, (screenX - strlen(pTwoTurn))/2, pTwoTurn);
                                move(pgY, pgX);
                                /*refresh();*/

                        }
                }
                else if(playerNum == PLAYER_2 && inputChar == ' ') {

                        getyx(stdscr, pgY, pgX);
                        canWeMove = updateBoardData(boardData, pgX, pgY,0);

                        if(canWeMove == OKAY) {

                                mvprintw(pgY, pgX, "O");

                                /* Returns 1 if last move caused winning scenario */
                                didWin = checkWin(boardData);

                                if(didWin){

                                        mvprintw((screenY - 10)+ 1/2, (screenX - strlen(twoWin))/2, twoWin);
                                        mvprintw((screenY - 8)+ 1/2, (screenX - strlen(playAg))/2, playAg);

                                        inputChar = getch();
                                        erase();
                                        return TRUE;
                                }
                                nMoves += 1;

                                playerNum = 1;
                                /*p1 mag lagay ng x*/
                                mvprintw((screenY - 10)/2, (screenX - strlen(pOneTurn))/2, pOneTurn);
                                move(pgY, pgX);
                                /*refresh();*/
                        }
                }
                refresh();
        }
        return FALSE;
        endwin();

}

int updateBoardData(int * boardData, int pgX, int pgY, int XorO) {

        /* Check row 1*/
        if(pgY == 1){
                if(pgX == 2){
                        if(boardData[0] > 1){
                                boardData[0] = XorO;
                                return OKAY;
                        }
                }
                else if( pgX == 6){
                        if(boardData[1] > 1){
                                boardData[1] = XorO;
                                return OKAY;
                        }
                }
                else if( pgX == 10){
                        if(boardData[2] > 1){
                                boardData[2] = XorO;
                                return OKAY;
                        }
                }
        }

        /* Check row 2 */
        else if(pgY == 3){
                if(pgX == 2){
                        if(boardData[3] > 1){
                                boardData[3] = XorO;
                                return OKAY;
                        }
                }
                else if( pgX == 6){
                        if(boardData[4] > 1){
                                boardData[4] = XorO;
                                return OKAY;
                        }
                }
                else if( pgX == 10){
                        if(boardData[5] > 1){
                                boardData[5] = XorO;
                                return OKAY;
                        }
                }
        }

        /* Check row 3*/
        else if(pgY == 5){
                if(pgX == 2){
                        if(boardData[6] > 1){
                                boardData[6] = XorO;
                                return OKAY;
                        }
                }
                else if( pgX == 6){
                        if(boardData[7] > 1){
                                boardData[7] = XorO;
                                return OKAY;
                        }
                }
                else if( pgX == 10){
                        if(boardData[8] > 1){
                                boardData[8] = XorO;
                                return OKAY;
                        }
                }
        }
        return FALSE;
}

int checkWin(int * boardData) {

        /* Check rows */
        if( boardData[0] == boardData[1] && boardData[1] == boardData[2] )
                return TRUE;
        else if( boardData[3] == boardData[4] && boardData[4] == boardData[5] )
                return TRUE;
        else if( boardData[6] == boardData[7] && boardData[7] == boardData[8] )
                return TRUE;

        /* Check cols */
        else if( boardData[0] == boardData[3] && boardData[3] == boardData[6] )
                return TRUE;
        else if( boardData[1] == boardData[4] && boardData[4] == boardData[7] )
                return TRUE;
        else if( boardData[2] == boardData[5] && boardData[5] == boardData[8] )
                return TRUE;

        /* Check diagonals */
        else if( boardData[0] == boardData[4] && boardData[4] == boardData[8] )
                return TRUE;
        else if( boardData[2] == boardData[4] && boardData[4] == boardData[6] )
                return TRUE;

        else
                return FALSE;

}
