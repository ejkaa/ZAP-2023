#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "ballsortpuzzle.h"
#include <curses.h>

void generator(const int rows, const int columns, char field[rows][columns]) {
    if(columns>8) {return;}
    srand(time(NULL));

    int empty_column1 = rand() % columns;
    int empty_column2;
    do { empty_column2 = rand() % columns; }
    while (empty_column2 == empty_column1);

    char characters[] = "^+*@&|";
    characters[columns - 2] = '\0';
    int count_char[] = {0, 0, 0, 0, 0, 0};
    int random;

    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            if (column == empty_column1 || column == empty_column2) {
                field[row][column] = ' ';
                continue;
            }
            do { random = rand() % (columns-2); }
            while (count_char[random] >= rows);
            field[row][column] = characters[random];
            count_char[random]++;
        }
    }
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y) {
    int c_x, c_y;
    getmaxyx(stdscr, c_x, c_y); //screen size
    c_x/=2; c_y/=2; //center

    x -= 1;
    y -= 1;
    if (x < 0 || x >= columns || y < 0 || y >= columns) {mvprintw(c_x-5,c_y-7,"Out of range"); getch(); return;}
    if (x == y) {mvprintw(c_x-5,c_y-3,"Huhh?"); getch(); return;}
    if (field[rows - 1][x] == ' ') {mvprintw(c_x-5,c_y-8,"Invalid take"); getch(); return;}
    if (field[0][y] != ' ') {mvprintw(c_x-5,c_y-8,"Invalid put"); getch(); return;}

    int level;
    for (int r = 0; r < rows; ++r) {
        if (field[r][x] != ' ') {
            level = r;
            break;
        }
    }

    if (field[rows - 1][y] == ' ') {
        field[rows - 1][y] = field[level][x];
        field[level][x] = ' ';
        printf("Dal som to tam\n"); }
    else {
        for (int r = 1; r < rows; ++r) {
            if (field[r][y] != ' ') {
                if (field[r][y] == field[level][x]) {
                    field[r - 1][y] = field[level][x];
                    field[level][x] = ' ';
                } else {
                    mvprintw(c_x-5,c_y-8,"Invalid move");
                    getch();
                    return;
                }
                break;
            }
        }
    }
}

bool check(const int rows, const int columns, char field[rows][columns]){
    int znak;
    for (int c = 0; c < columns; ++c) {
        znak = field[0][c];
        for (int r = 1; r < rows; ++r) {
            if(field[r][c] != znak) {return 0;}
        }
    }
    return 1;
}

void game_field(const int rows, const int columns, char field[rows][columns]){
    //initscr();
    clear();
    int x, y;
    getmaxyx(stdscr, x, y); //screen size
    x/=2; y/=2; //center

    int size_x = rows+2;
    int size_y = 5*columns+2;
    int farba;

    for (int r = 0; r < rows; ++r) {
        mvprintw(x-size_x/2+r,y-(size_y/2),"%d |", r+1);
        for (int c = 0; c < columns; ++c) {
            if(field[r][c] == ' ') {printw(" %c |", field[r][c]); continue;}
            if(field[r][c] == '^') {farba=1;}
            if(field[r][c] == '+') {farba=2;}
            if(field[r][c] == '*') {farba=3;}
            if(field[r][c] == '@') {farba=4;}
            if(field[r][c] == '&') {farba=5;}
            if(field[r][c] == '|') {farba=6;}

            attron(COLOR_PAIR(farba));
            printw("   ");//, field[r][c]);
            attroff(COLOR_PAIR(farba));
            printw("|");
        }
        printw("\n");
    }
    mvprintw(rows+5,5,"  ");
    move(x+size_x/2-2,y-4*columns+10);
    for (int i = 0; i < columns; ++i) {
        printw(" ---");
    }
    mvprintw(rows+6,5," ");
    move(x+size_x/2-1,y-4*columns+9);
    for (int i = 0; i < columns; ++i) {
        printw("   %d", i+1);
    }

    refresh();
}

void ball_sort_puzzle(){
    int rows = 4; int columns = 6;
    //printf("Rows:"); scanf("%d", &rows);
    //printf("Columns:"); scanf("%d", &columns);
    //if(columns>8) { printf("Field too big! I don't have time for this... bye.\n"); return;}

    initscr();
    start_color();

    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(5, COLOR_CYAN, COLOR_CYAN);
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW);

    char field[rows][columns];
    generator(rows,columns, field);

    int x, y;
    getmaxyx(stdscr, x, y); //screen size
    x/=2; y/=2; //center

    int size_x = rows+2;
    //int size_y = 5*columns+2;

    while(!check(rows,columns,field)){
        game_field(rows, columns, field);
        int take; int put;
        move(x+size_x/2,y-4*columns+9);
        printw("From: "); scanw("%d", &take);
        move(x+size_x/2+1,y-4*columns+9);
        printw("To: "); scanw("%d", &put);
        if(put==0 && take==0) {endwin(); return;}
        down_possible(rows, columns, field, take,put);
    }
    game_field(rows, columns, field);
    move(x+size_x/2,y-4*columns+14);
    printw("Congrats! You won!");
    char again;
    move(x+size_x/2+1,y-4*columns+11);
    printw("Wanna play again? (y/n)"); scanw("%c",&again);
    endwin();
    if(again == 'y') {ball_sort_puzzle();}
}
