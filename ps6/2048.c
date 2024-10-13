#define _DEFAULT_SOURCE

#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "unistd.h"
#include "curses.h"
#include "math.h"

void initialize(int rows, int cols, int field[rows][cols]){
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            field[row][col] = 0;
        }
    }
}

void add_num(int rows, int cols, int field[rows][cols], int score[1]){
    int four = rand() % 12; // pravdepodobnost stvorky je 1:12

    int row; int col;
    do{
        row = rand() % rows;
        col = rand() % cols;
    } while (field[row][col] != 0);

    score[0] += (four == 0) ? 4 : 2;
    field[row][col] = (four == 0) ? 4 : 2;
}

int move_up(int rows, int cols, int field[rows][cols], int score[1]) {
    int check = 0;

    for (int col = 0; col < cols; ++col) { // ide po stlpcoch zlava doprava
        for (int row = 1; row < rows; ++row) { // zhora dole

            if (field[row][col] == 0) {continue;} // ak je ten blok prazdny, ide na dalsi
            int row_up = row - 1;

            while (row_up >= 0 && field[row_up][col] == 0) { // ak je hore volne
                field[row_up][col] = field[row_up + 1][col]; // posun to hore
                field[row_up + 1][col] = 0; // vymaz spodne
                row_up--;
                check = 1;
            }

            if (row_up >= 0 && field[row_up][col] == field[row_up + 1][col]) { // ak sa rovnaju
                field[row_up][col] += field[row_up + 1][col]; // spocitaj ich
                field[row_up + 1][col] = 0; // vymaz dolne
                score[0] += 2 * field[row_up][col];
                check = 1;
            }
        }
    }
    return check;
}

int move_down(int rows, int cols, int field[rows][cols], int score[1]) {
    int check = 0;

    for (int col = 0; col < cols; ++col) { // ide po stlpcoch zlava doprava
        for (int row = rows - 2; row >= 0; --row) { // zdola hore

            if (field[row][col] == 0) {continue;} // ak je ten blok prazdny, ide na dalsi
            int row_down = row + 1;

            while (row_down < rows && field[row_down][col] == 0) { // ak je dole volne
                field[row_down][col] = field[row_down - 1][col]; // posun to dole
                field[row_down - 1][col] = 0; // vymaz horne
                row_down++;
                check = 1;
            }

            if (row_down < rows && field[row_down][col] == field[row_down - 1][col]) { // ak sa rovnaju
                field[row_down][col] += field[row_down - 1][col]; // spocitaj
                field[row_down - 1][col] = 0; // vymaz horne
                score[0] += 2 * field[row_down][col];
                check = 1;
            }
        }
    }
    return check;
}

int move_right(int rows, int cols, int field[rows][cols], int score[1]) {
    int check = 0;

    for (int row = 0; row < rows; ++row) { // ide po riadkoch zhora dole
        for (int col = cols - 2; col >= 0; --col) { // sprava dolava

            if (field[row][col] == 0) {continue;} // ak je ten blok prazdny, ide na dalsi
            int col_right = col + 1;

            while (col_right < cols && field[row][col_right] == 0) { // ak je vpravo volne
                field[row][col_right] = field[row][col_right - 1]; // posun do doprava
                field[row][col_right - 1] = 0; // vymaz lave
                col_right++;
                check = 1;
            }

            if (col_right < cols && field[row][col_right] == field[row][col_right - 1]) { // ak sa rovnaju
                field[row][col_right] += field[row][col_right - 1]; // spocitaj
                field[row][col_right - 1] = 0; // vymaz lave
                score[0] += 2 * field[row][col_right];
                check = 1;
            }
        }
    }
    return check;
}

int move_left(int rows, int cols, int field[rows][cols], int score[1]) {
    int check = 0;

    for (int row = 0; row < rows; ++row) { // ide po riadkoch zhora dole
        for (int col = 1; col < cols; ++col) { // zlava doprava

            if (field[row][col] == 0) {continue;} // ak je ten blok prazdny, ide na dalsi
            int col_left = col - 1;

            while (col_left >= 0 && field[row][col_left] == 0) { // ak je vlavo volne pole
                field[row][col_left] = field[row][col_left + 1]; // posun dolava
                field[row][col_left + 1] = 0; // vymaz prave
                col_left--;
                check = 1;
            }

            if (col_left >= 0 && field[row][col_left] == field[row][col_left + 1]) { // ak sa rovnaju
                field[row][col_left] += field[row][col_left + 1]; // spocitaj
                field[row][col_left + 1] = 0; // vymaz prave
                score[0] += 2 * field[row][col_left];
                check = 1;
            }
        }
    }
    return check;
}

int move_tiles(int rows, int cols, int field[rows][cols], int score[1]){
    int check = 0;
    char arrow = getch();
    if(arrow == '^') {getch(); arrow = getch();}

    if(arrow == 'A' || arrow == 'w'){
        check = move_up(rows, cols, field, score);
    }
    else if(arrow == 'B' || arrow == 's'){
        check = move_down(rows, cols, field, score);
    }
    else if(arrow == 'C' || arrow == 'd'){
        check = move_right(rows, cols, field, score);
    }
    else if(arrow == 'D' || arrow == 'a'){
        check = move_left(rows, cols, field, score);
    }
    else if(arrow == 'q') return 2;
    else if(arrow == 'r') return 3;
    return check;
}

int game_over(int rows, int cols, int field[rows][cols]){
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if(field[row][col] == 0) return 0;
        }
    }

    for (int row = 0; row < rows-1; ++row) {
        for (int col = 0; col < cols-1; ++col) {
            if(field[row][col] == field[row+1][col]) return 0;
            if(field[row][col] == field[row][col+1]) return 0;
        }
    }
    for (int row = 0; row < rows-1; ++row) {
        if(field[row][cols-1] == field[row+1][cols-1]) return 0;
    }

    for (int col = 0; col < cols-1; ++col) {
        if(field[rows-1][col] == field[rows-1][col+1]) return 0;
    }

    return 1;
}

int win(int rows, int cols, int field[rows][cols]){
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if(field[row][col] == 32) return 1;
        }
    }
    return 0;
}

void print_field(int rows, int cols, int field[rows][cols], int score[1], int high_score, int new_best){
    clear();
    attron(COLOR_PAIR(14));
    mvprintw(1,COLS/2-7,"PRESS 'Q' TO QUIT");
    mvprintw(2,COLS/2-8,"PRESS 'R' TO RESTART");
    attroff(COLOR_PAIR(14));

    int x = LINES/2 - 10; int y = COLS/2 - 2*13;
    attron(COLOR_PAIR(11));
    mvprintw(x+0,y,"          ");
    mvprintw(x+1,y,"            ");
    mvprintw(x+2,y+8,"    ");
    mvprintw(x+3,y+2,"          ");
    mvprintw(x+4,y,"          ");
    mvprintw(x+5,y,"    ");
    mvprintw(x+6,y,"            ");
    mvprintw(x+7,y,"            ");

    mvprintw(x+0,14+y+2,"        ");
    mvprintw(x+1,14+y,"            ");
    mvprintw(x+2,14+y,"    "); mvprintw(x+2,14+y+8,"    ");
    mvprintw(x+3,14+y,"    "); mvprintw(x+3,14+y+8,"    ");
    mvprintw(x+4,14+y,"    "); mvprintw(x+4,14+y+8,"    ");
    mvprintw(x+5,14+y,"    "); mvprintw(x+5,14+y+8,"    ");
    mvprintw(x+6,14+y,"            ");
    mvprintw(x+7,14+y+2,"        ");

    mvprintw(x+0,2*14+y,"    "); mvprintw(x+0,2*14+y+8,"    ");
    mvprintw(x+1,2*14+y,"    "); mvprintw(x+1,2*14+y+8,"    ");
    mvprintw(x+2,2*14+y,"    "); mvprintw(x+2,2*14+y+8,"    ");
    mvprintw(x+3,2*14+y,"            ");
    mvprintw(x+4,2*14+y+2,"          ");
    mvprintw(x+5,2*14+y+8,"    ");
    mvprintw(x+6,2*14+y+8,"    ");
    mvprintw(x+7,2*14+y+8,"    ");

    mvprintw(x+0,3*14+y+2,"        ");
    mvprintw(x+1,3*14+y,"            ");
    mvprintw(x+2,3*14+y,"    "); mvprintw(x+2,3*14+y+8,"    ");
    mvprintw(x+3,3*14+y,"            ");
    mvprintw(x+4,3*14+y,"            ");
    mvprintw(x+5,3*14+y,"    "); mvprintw(x+5,3*14+y+8,"    ");
    mvprintw(x+6,3*14+y,"            ");
    mvprintw(x+7,3*14+y+2,"        ");
    attroff(COLOR_PAIR(11));

    int begin_line = x+10;
    int size_cols = cols*5;
    int begin_col = COLS/2 - size_cols/2 -10;
    int row_m = 0;
    move(begin_line+row_m, begin_col);
    for (int i = 0; i < rows; ++i) {
        printw(" ");
        //attron(COLOR_PAIR(14));
        printw("****");
        //attroff(COLOR_PAIR(14));
    }

    for (int row_f = 0; row_f < rows; ++row_f) {
        row_m++;
        move(begin_line + row_m, begin_col);
        //attron(COLOR_PAIR(14));
        printw("*");
        //attroff(COLOR_PAIR(14));
        for (int col = 0; col < cols; ++col) {
            if (field[row_f][col] == 0) printw("    ");
            else {
                attron(COLOR_PAIR(log2(field[row_f][col])));
                if (field[row_f][col] < 1000) { printw(" "); }
                printw("%d", field[row_f][col]);
                if (field[row_f][col] < 10) { printw(" "); }
                if (field[row_f][col] < 100) { printw(" "); }
                attroff(COLOR_PAIR(log2(field[row_f][col])));
            }
            //if(col < cols-1) printw(" ");
            //attron(COLOR_PAIR(14));
            printw("*");
            //attroff(COLOR_PAIR(14));
        }
        row_m++;
        move(begin_line + row_m, begin_col);
        for (int i = 0; i < rows; ++i) {
            //attron(COLOR_PAIR(14));
//            if(row_f == rows-1) printw(" ");
//            else printw("*");
            printw(" ****");
            //attroff(COLOR_PAIR(14));
        }
        if (row_f < rows - 1) {
            //attron(COLOR_PAIR(14));
            printw("*");
            //attroff(COLOR_PAIR(14));
        }
    }

    if(new_best) {
        attron(COLOR_PAIR(12));
        mvprintw(begin_line +1, begin_col + cols*5 + 5, "NEW HIGH SCORE!: %d",high_score);
        attroff(COLOR_PAIR(12));
    }else mvprintw(begin_line +1, begin_col + cols*5 + 5, "HIGH SCORE: %d", high_score);
    mvprintw(begin_line +2, begin_col + cols*5 + 5, "SCORE: %d", score[0]);
    refresh();
}

void print_menu(int cursor, int screen, int score_list[3]){
    clear();
    int x = LINES/2 - 10; int y = COLS/2 - 2*13;
    attron(COLOR_PAIR(11));
    mvprintw(x+0,y,"          ");
    mvprintw(x+1,y,"            ");
    mvprintw(x+2,y+8,"    ");
    mvprintw(x+3,y+2,"          ");
    mvprintw(x+4,y,"          ");
    mvprintw(x+5,y,"    ");
    mvprintw(x+6,y,"            ");
    mvprintw(x+7,y,"            ");

    mvprintw(x+0,14+y+2,"        ");
    mvprintw(x+1,14+y,"            ");
    mvprintw(x+2,14+y,"    "); mvprintw(x+2,14+y+8,"    ");
    mvprintw(x+3,14+y,"    "); mvprintw(x+3,14+y+8,"    ");
    mvprintw(x+4,14+y,"    "); mvprintw(x+4,14+y+8,"    ");
    mvprintw(x+5,14+y,"    "); mvprintw(x+5,14+y+8,"    ");
    mvprintw(x+6,14+y,"            ");
    mvprintw(x+7,14+y+2,"        ");

    mvprintw(x+0,2*14+y,"    "); mvprintw(x+0,2*14+y+8,"    ");
    mvprintw(x+1,2*14+y,"    "); mvprintw(x+1,2*14+y+8,"    ");
    mvprintw(x+2,2*14+y,"    "); mvprintw(x+2,2*14+y+8,"    ");
    mvprintw(x+3,2*14+y,"            ");
    mvprintw(x+4,2*14+y+2,"          ");
    mvprintw(x+5,2*14+y+8,"    ");
    mvprintw(x+6,2*14+y+8,"    ");
    mvprintw(x+7,2*14+y+8,"    ");

    mvprintw(x+0,3*14+y+2,"        ");
    mvprintw(x+1,3*14+y,"            ");
    mvprintw(x+2,3*14+y,"    "); mvprintw(x+2,3*14+y+8,"    ");
    mvprintw(x+3,3*14+y,"            ");
    mvprintw(x+4,3*14+y,"            ");
    mvprintw(x+5,3*14+y,"    "); mvprintw(x+5,3*14+y+8,"    ");
    mvprintw(x+6,3*14+y,"            ");
    mvprintw(x+7,3*14+y+2,"        ");
    attroff(COLOR_PAIR(11));

    x = LINES/2 -2; y = COLS/2 +2;

    if(screen == 0){
        attron(COLOR_PAIR(14));
        if(cursor == 0) {attroff(COLOR_PAIR(14)); attron(COLOR_PAIR(15));}
        mvprintw(x+2,y-5,"START GAME");
        if(cursor == 0) {attroff(COLOR_PAIR(15)); attron(COLOR_PAIR(14));}
        if(cursor == 1) {attroff(COLOR_PAIR(14)); attron(COLOR_PAIR(15));}
        mvprintw(x+4,y-5,"RESUME GAME");
        if(cursor == 1) {attroff(COLOR_PAIR(15)); attron(COLOR_PAIR(14));}
        if(cursor == 2) {attroff(COLOR_PAIR(14)); attron(COLOR_PAIR(15));}
        mvprintw(x+6,y-3,"RULES");
        if(cursor == 2) {attroff(COLOR_PAIR(15)); attron(COLOR_PAIR(14));}
        if(cursor == 3) {attroff(COLOR_PAIR(14)); attron(COLOR_PAIR(15));}
        mvprintw(x+8,y-5,"HIGH SCORE");
        if(cursor == 3) {attroff(COLOR_PAIR(15)); attron(COLOR_PAIR(14));}
        if(cursor == 4) {attroff(COLOR_PAIR(14)); attron(COLOR_PAIR(15));}
        mvprintw(x+10,y-2,"EXIT");
        if(cursor == 4) {attroff(COLOR_PAIR(15)); attron(COLOR_PAIR(14));}
        attroff(COLOR_PAIR(14));
    }
    else if(screen == 1){
        attron(COLOR_PAIR(14));
        if(cursor == 0) {attroff(COLOR_PAIR(14)); attron(COLOR_PAIR(15));}
        mvprintw(x+2,y-2,"EASY");
        if(cursor == 0) {attroff(COLOR_PAIR(15)); attron(COLOR_PAIR(14));}
        if(cursor == 1) {attroff(COLOR_PAIR(14)); attron(COLOR_PAIR(15));}
        mvprintw(x+4,y-3,"MEDIUM");
        if(cursor == 1) {attroff(COLOR_PAIR(15)); attron(COLOR_PAIR(14));}
        if(cursor == 2) {attroff(COLOR_PAIR(14)); attron(COLOR_PAIR(15));}
        mvprintw(x+6,y-2,"HARD");
        if(cursor == 2) {attroff(COLOR_PAIR(15)); attron(COLOR_PAIR(14));}
        if(cursor == 3) {attroff(COLOR_PAIR(14)); attron(COLOR_PAIR(15));}
        mvprintw(x+8,y-2,"MENU");
        if(cursor == 3) {attroff(COLOR_PAIR(15)); attron(COLOR_PAIR(14));}
        attroff(COLOR_PAIR(14));
    }
    else if(screen == 2){
        attron(COLOR_PAIR(14));
        mvprintw(x+1,y-3,"RULES");
        attroff(COLOR_PAIR(14));
        mvprintw(x+3,y-28,"The game 2048 starts with two tiles on the board. There");
        usleep(1*80000);
        refresh();
        mvprintw(x+4,y-28,"are 4 possible moves: RIGHT, LEFT, UP and DOWN to unveil");
        usleep(1*80000);
        refresh();
        mvprintw(x+5,y-28,"  a new tile. Each tile bears a value of power of two,");
        usleep(1*80000);
        refresh();
        mvprintw(x+6,y-28," starting at 2. The point of the game is to merge tiles");
        usleep(1*80000);
        refresh();
        mvprintw(x+7,y-28,"with the same value until there are no more empty spaces");
        usleep(1*80000);
        refresh();
        mvprintw(x+8,y-28,"     or a tile with value of 2048 has been created.");
        usleep(1*80000);
        refresh();

        attron(COLOR_PAIR(14));
        mvprintw(x+10,y-4,"CONTROLS");
        usleep(1*80000);
        refresh();
        attroff(COLOR_PAIR(14));

        mvprintw(x+12,y-11,"W - UP        S - DOWN");
        usleep(1*80000);
        refresh();
        mvprintw(x+13,y-11,"A - LEFT      D - RIGHT");
    }
    else if(screen == 3){
        attron(COLOR_PAIR(14));
        mvprintw(x+3,y-5-10,"EASY");   mvprintw(x+3,y-3,"MEDIUM");   mvprintw(x+3,y+5+5,"HARD");
        mvprintw(x+4,y-5-10,"%d",score_list[0]);   mvprintw(x+4,y-3,"%d",score_list[1]);   mvprintw(x+4,y+5+5,"%d",score_list[2]);
    }
    refresh();
}

int menu(int difficulty[1], int score_list[3]){
    int screen = 0;
    int cursor = 0;
    char arrow;
    do {
        print_menu(cursor, screen, score_list);
        arrow = getch();
        if (arrow == '^') {getch(); arrow = getch();}

        if ((arrow == 'A' || arrow == 'w') && cursor > 0) cursor--;
        else if ((arrow == 'B' || arrow == 's') && cursor < 4) cursor++;
    }while(arrow != '\n');

    if(cursor == 0) screen = 1; // start
    else if(cursor == 1) return 2; // resume
    else if(cursor == 2) screen = 2; // rules
    else if(cursor == 3) screen = 3; // highscore
    else if(cursor == 4) return 1; // exit

    if(screen == 1) {
        cursor = 0;
        do {
            print_menu(cursor, screen, score_list);
            arrow = getch();
            if (arrow == '^') {getch(); arrow = getch();}

            if ((arrow == 'A' || arrow == 'w') && cursor > 0) cursor--;
            else if ((arrow == 'B' || arrow == 's') && cursor < 3) cursor++;
        }while(arrow != '\n');

        if (cursor == 0) difficulty[0] = 0;
        else if (cursor == 1) difficulty[0] = 1;
        else if (cursor == 2) difficulty[0] = 2;
        else if (cursor == 3) menu(difficulty, score_list);
    }
    else if(screen > 1){
        print_menu(cursor, screen, score_list);
        do {
            arrow = getch();
            if (arrow == '^') {getch(); arrow = getch();}
        }while(arrow != '\n');
        menu(difficulty, score_list);
    }

    return 0;
}

int main(){
    srand(time(NULL));

    initscr();
    noecho(); // hide user input
    curs_set(0); // hide cursor

    start_color();

    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_CYAN);
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);
    init_pair(7, COLOR_RED, COLOR_RED);
    init_pair(8, COLOR_GREEN, COLOR_GREEN);
    init_pair(9, COLOR_BLUE, COLOR_BLUE);
    init_pair(10, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(11, COLOR_CYAN, COLOR_CYAN);

    init_pair(12, COLOR_GREEN, COLOR_BLACK);
    init_pair(13, COLOR_RED, COLOR_BLACK);
    init_pair(14, COLOR_CYAN, COLOR_BLACK);
    init_pair(15, COLOR_WHITE, COLOR_CYAN);

    FILE *file_score;
    FILE *file_field;
    file_score = fopen("high_score.txt", "r");
    int score_list[3];
    for (int i = 0; i < 3; ++i) {
        fscanf(file_score, "%d", &score_list[i]);
    }
    fclose(file_score); // mam pole s high score

    int difficulty[1];
    int output = menu(difficulty, score_list); // kvoli exit a resume
    if(output == 1) {endwin(); return 0;}
    if(output == 2) {
        file_field = fopen("field.txt", "r");
        fscanf(file_score, "%d", &difficulty[0]); // 0 pre easy 2 pre hard
    }

    int high_score = score_list[difficulty[0]];
    int new_best = 0;
    int score[1] = {0};         if(output == 2) fscanf(file_score, "%d", &score[0]);
    int result = 0; // to je na to aby som vedela co potom vypisat
    int input; // to je kvoli r a q
    int size = 5 - difficulty[0];
    int rows = size; int cols = size;

    int field[rows][cols];
    if(output == 2){
        int value;
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                fscanf(file_score, "%d", &value);
                field[row][col] = value;
            }
        }
        fclose(file_field);
    }
    else{
        initialize(rows, cols, field);
        add_num(rows, cols, field, score);
        add_num(rows, cols, field, score);
    }

    while(!game_over(rows,cols,field)){
        if(score[0] > high_score) {
            new_best = 1;
            print_field(rows,cols,field, score, score[0], new_best);
        }
        else print_field(rows,cols,field, score, high_score, new_best);

        input = move_tiles(rows, cols, field, score);
        if(input == 1) {// ked sa podari pohnut
            add_num(rows, cols, field, score);

            file_field = fopen("field.txt", "w"); // zapise progress
            fprintf(file_field, "%d\n", difficulty[0]);
            fprintf(file_field, "%d\n", score[0]);
            for (int row = 0; row < rows; ++row) {
                for (int col = 0; col < cols; ++col) {
                    fprintf(file_field, "%d ", field[row][col]);
                }
                fprintf(file_field, "\n");
            }
            fclose(file_field);
        }
        else if(input == 2) { // ked sa stlaci q
            if(new_best == 1) { // ak ma new best, tak ho zapise do suboru
                high_score = score[0];
                file_score = fopen("high_score.txt", "w");
                for (int i = 0; i < 3; ++i) {
                    if (i == difficulty[0]) fprintf(file_score, "%d\n", high_score);
                    else fprintf(file_score, "%d\n", score_list[i]);
                }
                fclose(file_score);
            }
            endwin();
            main();
        }

        else if(input == 3) { // ked sa stlaci r
            if(new_best == 1) { // ak ma new best, tak ho zapise do suboru
                high_score = score[0];
                file_score = fopen("high_score.txt", "w");
                for (int i = 0; i < 3; ++i) {
                    if (i == difficulty[0]) fprintf(file_score, "%d\n", high_score);
                    else fprintf(file_score, "%d\n", score_list[i]);
                }
                fclose(file_score);

                score_list[difficulty[0]] = high_score;
            }

            score[0] = 0; // vynuluje score
            new_best = 0;
            initialize(rows, cols, field); // zacne novu hru
            add_num(rows, cols, field, score);
            add_num(rows, cols, field, score);
        }

        if(win(rows,cols,field)) {
            result = 1;
            break;
        }
    }

    if(new_best) high_score = score[0];
    file_score = fopen("high_score.txt", "w");
    for (int i = 0; i < 3; ++i) {
        if(i == difficulty[0]) fprintf(file_score, "%d\n", high_score);
        else fprintf(file_score, "%d\n", score_list[i]);
    }
    fclose(file_score);

    print_field(rows, cols, field, score, high_score, new_best);
    if(result){
        if(difficulty[0] == 1) move(LINES/2 +4, COLS/2 + cols*5/2 -5);
        else mvprintw(LINES/2 +4, COLS/2 + cols*5/2 -5, " ");
        attron(COLOR_PAIR(12));
        printw("CONGRATS! YOU WON THE GAME!");
        attroff(COLOR_PAIR(12));

        score[0] = 0; // vynuluje score
        new_best = 0;
        initialize(rows, cols, field); // zacne novu hru
        add_num(rows, cols, field, score);
        add_num(rows, cols, field, score);

        file_field = fopen("field.txt", "w"); // zapise progress
        fprintf(file_field, "%d\n", difficulty[0]);
        fprintf(file_field, "%d\n", score[0]);
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                fprintf(file_field, "%d ", field[row][col]);
            }
            fprintf(file_field, "\n");
        }
        fclose(file_field);

    }else{
        if(difficulty[0] == 1) move(LINES/2 +4, COLS/2 + cols*5/2 -5);
        else mvprintw(LINES/2 +4, COLS/2 + cols*5/2 -5, " ");
        attron(COLOR_PAIR(13));
        printw("GAME OVER");
        attroff(COLOR_PAIR(13));
    }

    mvprintw(1,COLS/2-8,"PRESS ENTER TO QUIT");
    char esc;
    do {esc = getch();} while (esc != '\n');
    endwin();
    main();
    return 0;
}

/*
int move_up(int rows, int cols, int field[rows][cols], int score[1]){
    int check = 0;
    //for (int i = 0; i < rows-1; ++i) {
        for (int row = 1; row < rows; ++row) { // ide po riadkoch zhora dole
            for (int col = 0; col < cols; ++col) { // dalsi blok v riadku

                if (field[row][col] == 0) { continue; } //ak je ten blok prazdny, ide na dalsi

                int row_up = row - 1;

                if (field[row_up][col] == field[row][col]) { // ak je blok nad nim rovnaky
                    field[row_up][col] += field[row][col];
                    score[0] += 2 * field[row][col];
                    field[row][col] = 0;
                    check = 1;
                    continue; // tak sa spocitaju a ide sa na dalsi blok v riadku
                }

                if (field[row_up][col] != 0) { continue; } // ak nad nim nie je miesto, ide na dalsi

                while (row_up > 0 &&
                       field[row_up - 1][col] == 0) { row_up--; } // ak je volne este vyssie, presun sa tam

                if (row_up > 0) { //ak sa da ist vyssie
                    if (field[row_up - 1][col] == field[row][col]) { // skontroluje ci je blok nad nim rovnaky
                        field[row_up - 1][col] += field[row][col];
                        score[0] += 2 * field[row][col];
                        field[row][col] = 0;
                        check = 1;
                        continue; // spocitaju sa a ide sa na dalsi blok v riadku
                    }
                }

                field[row_up][col] = field[row][col];
                field[row][col] = 0;
                check = 1;
                break;
            }
        }
    //}
    return check;
}

int move_down(int rows, int cols, int field[rows][cols], int score[1]){
    int check = 0;
    //for (int i = 0; i < rows-1; ++i) {
        for (int row = rows - 2; row >= 0; --row) { // ide po riadkoch zdola hore
            for (int col = 0; col < cols; ++col) { // dalsi blok v riadku

                if (field[row][col] == 0) { continue; } //ak je ten blok prazdny, ide na dalsi

                int row_down = row + 1;

                if (field[row_down][col] == field[row][col]) { // ak je blok pod nim rovnaky
                    field[row_down][col] += field[row][col];
                    score[0] += 2 * field[row][col];
                    field[row][col] = 0;
                    check = 1;
                    continue; // tak sa spocitaju a ide sa na dalsi blok v riadku
                }

                if (field[row_down][col] != 0) { continue; } // ak pod nim nie je miesto, ide na dalsi

                while (row_down < rows - 1 &&
                       field[row_down + 1][col] == 0) { row_down++; } // ak je volne este nizsie, presun sa tam

                if (row_down < rows - 1) { //ak sa da ist nizsie
                    if (field[row_down + 1][col] == field[row][col]) { // skontroluje ci je blok pod nim rovnaky
                        field[row_down + 1][col] += field[row][col];
                        score[0] += 2 * field[row][col];
                        field[row][col] = 0;
                        check = 1;
                        continue; // spocitaju sa a ide sa na dalsi blok v riadku
                    }
                }

                field[row_down][col] = field[row][col];
                field[row][col] = 0;
                check = 1;
                break;
            }
        }
    //}
    return check;
}

int move_right(int rows, int cols, int field[rows][cols], int score[1]){
    int check = 0;
    //for (int i = 0; i < rows-1; ++i) {
        for (int col = cols - 2; col >= 0; --col) { // ide po stlpcoch sprava dolava
            for (int row = 0; row < rows; ++row) { // dalsi blok v stlpci

                if (field[row][col] == 0) { continue; } //ak je ten blok prazdny, ide na dalsi

                int col_right = col + 1;

                if (field[row][col_right] == field[row][col]) { // ak je blok vpravo rovnaky
                    field[row][col_right] += field[row][col];
                    score[0] += 2 * field[row][col];
                    field[row][col] = 0;
                    check = 1;
                    continue; // tak sa spocitaju a ide sa na dalsi blok v stlpci
                }

                if (field[row][col_right] != 0) { continue; } // ak vpravo nie je miesto, ide na dalsi

                while (col_right < cols - 1 &&
                       field[row][col_right + 1] == 0) { col_right++; } // ak je volne este viac vpravo, presun sa tam

                if (col_right < cols - 1) { //ak sa da ist doprava
                    if (field[row][col_right + 1] == field[row][col]) { // skontroluje ci je blok vpravo rovnaky
                        field[row][col_right + 1] += field[row][col];
                        score[0] += 2 * field[row][col];
                        field[row][col] = 0;
                        check = 1;
                        continue; // spocitaju sa a ide sa na dalsi blok v stlpci
                    }
                }

                field[row][col_right] = field[row][col];
                field[row][col] = 0;
                check = 1;
                break;
            }
        }
    return check;
}

int move_left(int rows, int cols, int field[rows][cols], int score[1]){
    int check = 0;
        for (int col = 1; col < cols; ++col) { // ide po stlpcoch zlava doprava
            for (int row = 0; row < rows; ++row) { // dalsi blok v stlpci

                if (field[row][col] == 0) {continue;} //ak je ten blok prazdny, ide na dalsi

                int col_left = col - 1;

                if (field[row][col_left] == field[row][col]) { // ak je blok vlavo rovnaky
                    field[row][col_left] += field[row][col];
                    score[0] += 2 * field[row][col];
                    field[row][col] = 0;
                    check = 1;
                    continue; // tak sa spocitaju a ide sa na dalsi blok v stlpci
                }

                if (field[row][col_left] != 0) {continue;} // ak vlavo nie je miesto, ide na dalsi

                while (col_left > 0 && field[row][col_left - 1] == 0) {col_left--;} // ak je volne este viac vlavo, presun sa tam

                if (col_left > 0) { //ak sa da ist dolava
                    if(field[row][col_left-1] == field[row][col]) { // skontroluje ci je blok vlavo rovnaky
                        field[row][col_left-1] += field[row][col];
                        score[0] += 2 * field[row][col];
                        field[row][col] = 0;
                        check = 1;
                        continue; // spocitaju sa a ide sa na dalsi blok v stlpci
                    }
                }

                field[row][col_left] = field[row][col];
                field[row][col] = 0;
                check = 1;
                break;
            }
        }
    return check;
}*/