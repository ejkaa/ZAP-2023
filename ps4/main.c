#include "ballsortpuzzle.h"
#include "c4.h"
#include <stdio.h>
#include <ctype.h>

int main(){
    int rows = 4;
    int columns = 6;
    char field[rows][columns];
//    char field[4][6] = {
//            {' ', ' ', '^', '@', '@', ' '},
//            {'+', ' ', '^', '@', '^', ' '},
//            {'+', ' ', '*', '+', '+', ' '},
//            {'*', '*', '*', '@', '^', ' '}};
    generator(rows,columns, field);
    //down_possible(rows,columns,field, 1,2);
//    for (int r = 0; r < rows ; ++r) {
//        for (int c = 0; c < columns; ++c) {
//            printf("%c  ", field[r][c]);
//        }
//        printf("\n");
//    }
    //printf("%d ", check(rows,columns,field));
    return 0;
}