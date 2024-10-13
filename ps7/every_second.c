#include "stdio.h"

int search_word(char word[50], FILE *input) {
    int index = 0;
    char character = fgetc(input);

    while (character != EOF && character != ' ') {
        word[index] = character;
        index++;
        character = fgetc(input);
    }
    word[index] = '\0';

    if(character == EOF) return 0; // nedokoncene slovo
    else return 1;
}
int main(int int_int, char *arg[]){
//int main(){
    FILE *input;
    FILE *output;

    output = fopen(arg[2], "w");
    fclose(output);
    input = fopen(arg[1], "r");
    if(input == NULL) return 0;
    char word[50];

    if(search_word(word, input) == 0) return 0;
    if(word[0] == '\0' || word[0] == EOF) { fclose(input); return 0; }

    while(!(word[0] == 'S' && word[1] == 'T' && word[2] == 'A' && word[3] == 'R' && word[4] == 'T')) {
        search_word(word, input);
    }

    output = fopen(arg[2], "w");
    if(output == NULL) return 0;
    int first = 0;

    while(search_word(word, input) && !(word[0] == 'S' && word[1] == 'T' && word[2] == 'O' && word[3] == 'P')) {
        if(!search_word(word, input)) break;
        if(!(word[0] == 'S' && word[1] == 'T' && word[2] == 'O' && word[3] == 'P')){
            if(first) fputc(' ',output);
            for(int i = 0; word[i] != '\0'; i++){
                fputc(word[i], output);
            }
            first = 1;
            //fputs(word,output);
        }else break;
    }

    fclose(output);
    fclose(input);

    return 0;
}


//    while(character != EOF){
//        if(index == -1 && (character == 'a' || character == 'A')) index = 0;
//
//        else if(index>=0) {
//            if(read == 0){ // search START
//                if (character == start_stop[index]) index++;
//                else index = -1;
//                if(index == 4){
//                    index = -1;
//                    read = 1;
//                }
//            }else{ // search STOP
//                if (character == start_stop[index+6]) index++;
//                else index = -1;
//                if(index == 4){
//                    index = -1;
//                    read = 0;
//                }
//            }
//        }
//
//        if(read)
//
