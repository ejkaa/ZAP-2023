#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
//arena je blbost 
void encode_char(const char character, bool bits[8]){
    int decimal = character; //cislo v ascii
    bool binary[8];
    for(int i = 0; i < 8; i++) {
        if(decimal>0){
            binary[i] = decimal%2;
            decimal/=2;
        }
        else {binary[i] = 0;}
    }
    for (int i = 0; i < 8; ++i) {bits[i] = binary[8-1-i];}
}

char decode_byte(const bool bits[8]){
    int sum = 0;
    for (int i = 0; i < 8; ++i) {
        if(bits[i]) {
            sum+= pow(2,7-i);
        }
    }
    return (char)sum;
}

void encode_string(const char string[], bool bytes[strlen(string)+1][8]){
    for (int letter = 0; letter <= strlen(string); ++letter) {
        bool bits[8];
        encode_char(string[letter],bits);
        for (int i = 0; i < 8; ++i) {
            bytes[letter][i] = bits[i];
        }
    }
    for (int i = 0; i < 8; ++i) {
        bytes[strlen(string)][i] = 0;
    }
}

void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]){
    for (int row = 0; row < rows; ++row) {
        char letter = decode_byte(bytes[row]);
        string[row] = letter;
    }
}

void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    int begin = 0;
    for (int off = 0, on = 0; off < offset*8; ++off, on++) {

        for (int c = 0; c < cols; ++c) {
            if(c+begin >= rows) {blocks[off][c] = 0;}
            else{blocks[off][c] = bytes[c+begin][on];}
        }
        if(off % 8 == 7) {begin+=cols; on = -1;}
    }
}

void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    int begin = 0;
    for (int row = 0, col = 0; row < rows; ++row, col++) {
        for (int i = 0; i < 8; ++i) {
            bytes[row][i] = blocks[i+begin][col];
        }
        if(col==cols-1) {begin+=8; col = -1;}
    }
}

int main(){
    int length = 4+1, cols = 3, offset = 2;
    bool bytes1[4+1][8] = {
            {0,1,0,0,0,0,0,1},
            {0,1,1,0,1,0,0,0},
            {0,1,1,0,1,1,1,1},
            {0,1,1,0,1,0,1,0},
            {0,0,0,0,0,0,0,0}
    };
    bool blocks1[offset*8][cols];
    bytes_to_blocks(cols, offset, blocks1, length, bytes1);
    for(int j = 0; j < offset*8; j++){
        for(int i = 0; i < cols; i++){
            printf("%d ", (blocks1[j][i] == true) ? 1 : 0);
        }
        printf("\n");
        if(j % 8 == 7){
            printf("\n");
        }
    }

    bool blocks2[2*8][3] = {
            {0,0,0},
            {1,1,1},
            {0,1,1},
            {0,0,0},
            {0,1,1},
            {0,0,1},
            {0,0,1},
            {1,0,1},
            {0,0,0},
            {1,0,0},
            {1,0,0},
            {0,0,0},
            {1,0,0},
            {0,0,0},
            {1,0,0},
            {0,0,0}
    };
    bool bytes2[length][8];
    blocks_to_bytes(3, 2, blocks2, length, bytes2);
    for(int j = 0; j < length; j++){
        for(int i = 0; i < 8; i++){
            printf("%d", bytes2[j][i]);
        }
        printf("\n");
    }

    return 0;
}
