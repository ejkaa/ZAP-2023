#include "c4.h"
#include <stdio.h>
#include <curses.h>
//.
void initialize_board(int rows, int cols, char board[rows][cols]){
    if(rows<4 || cols<4) {return;}
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            board[r][c] = '.';
        }
    }
}

void print_board(int rows, int cols, const char board[rows][cols]){
    clear();
    printw("\n");

    //for (int r = 0; r < cols; ++r) {
    for (int r = 0; r < rows; ++r) {
        printw("|");
        //for (int c = 0; c < rows; ++c) {
        for (int c = 0; c < cols; ++c) {
            if(board[r][c] == '.') {printw(" . ");}
            else if(board[r][c] == 'X'){
                attron(COLOR_PAIR(1));
                printw("   ");
                attroff(COLOR_PAIR(1));
            }else{
                attron(COLOR_PAIR(2));
                printw("   ");
                attroff(COLOR_PAIR(2));
            }
            printw("|");
        }
        printw("\n");
    }

    for (int i = 0; i < cols; ++i) {printw("----");}
    printw("-\n  1");

    for (int c = 1; c < cols; ++c) {printw("   %d", c+1);}
    printw("\n");
}

int is_valid_move(int rows, int cols, const char board[rows][cols], int col){
    if(board[0][col-1] == '.') {return 1;}
    return 0;
}

int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece){
    if(col>cols) {
        printw("Out of range"); 
        getch();
        return 0;
    }
    col-=1;
    if(!is_valid_move(rows, cols, board, col)) {
        printw("Invalid move"); 
        getch(); 
        return 0;
    }

    for (int r = rows-1; r >= 0; r--) {
        if(board[r][col] == '.') {
            board[r][col] = player_piece;
            print_board(rows,cols, board);
            return r;
        }
    }
    return 0;
}

int check_win(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece){
    //check row
    for (int c = 0; c < cols-3; ++c) {
        if(
            board[row][c] == player_piece
            && board[row][c+1] == player_piece
            && board[row][c+2] == player_piece
            && board[row][c+3] == player_piece
        ){return 1;}
    }
    //check col
    
    /*takto to ide mne
    for (int r = 0; r < rows; ++r) {
        if(
            board[r][col-1] == player_piece
            && board[r+1][col-1] == player_piece
            && board[r+2][col-1] == player_piece
            && board[r+3][col-1] == player_piece
        ){return 1;}
    }*/
    //ale takto to ide v arene
    for (int r = 0; r < rows-3; ++r) {
        if(
            board[r][col] == player_piece
            && board[r+1][col] == player_piece
            && board[r+2][col] == player_piece
            && board[r+3][col] == player_piece
        ){return 1;}
    }

    //diagonal right
    for (int c = 0; c < cols-3; ++c) {
        for (int r = 0; r < rows-3; ++r) {
            if(
                board[r][c] == player_piece
                && board[r+1][c+1] == player_piece
                && board[r+2][c+2] == player_piece
                && board[r+3][c+3] == player_piece
            ){return 1;}
        }
    }
    //diagonal left
    for (int c = 3; c < cols; ++c) {
        for (int r = 0; r < rows-3; ++r) {
            if(
                board[r][c] == player_piece
                && board[r+1][c-1] == player_piece
                && board[r+2][c-2] == player_piece
                && board[r+3][c-3] == player_piece
                ){return 1;}
        }
    }
    return 0;
}

int is_board_full(int rows, int cols, const char board[rows][cols]){
    for (int c = 0; c < cols; ++c) {
        if(board[0][c] == '.') {return 0;}
    }return 1;
}
