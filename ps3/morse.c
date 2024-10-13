#include "morse.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void text_to_morse(const char text[], char output[]){
    output[0] = '\0'; 
    const char *morse[26] = {".-","-...","-.-.","-..",".","..-.",
                         "--.","....","..",".---","-.-",
                         ".-..","--","-.","---",".--.",
                         "--.-",".-.","...","-","..-",
                         "...-",".--","-..-","-.--","--.."};
    char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char string[strlen(text)];
    for (int i = 0; i < strlen(text); ++i) {string[i] = toupper(text[i]);}

    for(int i = 0; i < strlen(string); i++) {
        for (int j = 0; j < 26; j++) {
            if (string[i] == alphabet[j]) {
                strcat(output, (const char *) morse[j]);
                if(i < strlen(string)){
                    strcat(output, " ");
                }else {output[strlen(output)-1] = '\0'; return;}
                break;
            }
        }
    }
    output[strlen(output)-1] = '\0';
}

void morse_to_text(const char morse[], char output[]) {
    output[0] = '\0';
    char code[strlen(morse)];
    strncpy(code, morse, sizeof(code));
    code[strlen(morse)] = ' ';
    const char *morseovka[36] = {".-", "-...", "-.-.", "-..", ".", "..-.",
                                 "--.", "....", "..", ".---", "-.-",
                                 ".-..", "--", "-.", "---", ".--.",
                                 "--.-", ".-.", "...", "-", "..-",
                                 "...-", ".--", "-..-", "-.--", "--..",
                                 ".----", "..---", "...--", "....-", ".....",
                                 "-....", "--...", "---..", "----.", "-----"};
    char alphabet[36] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    char word[6];
    int word_i = 0;
    int count = 0;

    for (int i = 0; i < strlen(code); i++) {
        if(code[i] == ' '){
            word[word_i] = '\0';
            word_i = 0;

            for (int j = 0; j < 36; ++j) {
                if (strcmp(word, morseovka[j]) == 0){
                    output[count] = alphabet[j];
                    count++;
                    break;
                }
            }

        }else{
            word[word_i] = code[i];
            word_i++;
        }
    }
    output[count] = '\0';
}

int is_morse_code_valid(const char morse[]){
    if(strlen(morse)<1) {return 1;}
    //puts(morse);
    char code[150];
    strncpy(code, morse, sizeof(code));
    code[strlen(morse)] = ' ';
    const char *morseovka[36] = {".-", "-...", "-.-.", "-..", ".", "..-.",
                                 "--.", "....", "..", ".---", "-.-",
                                 ".-..", "--", "-.", "---", ".--.",
                                 "--.-", ".-.", "...", "-", "..-",
                                 "...-", ".--", "-..-", "-.--", "--..",
                                 ".----", "..---", "...--", "....-", ".....",
                                 "-....", "--...", "---..", "----.", "-----"};
    char word[6];
    int word_i = 0;
    int check = 0;
    const char space = ' ';

    for (int i = 0; i < strlen(code); i++) {
        check = 1;
        if(code[i] == space && word[0] != '\0'){
            word[word_i] = '\0';
            word_i = 0;

            //puts(word);
            for (int j = 0; j < 36; ++j) {
                if (strcmp(word, morseovka[j]) == 0){
                    check = 0;
                    word[0] = '\0';
                    break;
                }
            }
            if(check) {return 0;}
        }else if (code[i] != space){
           // putchar(morse[i]);
            word[word_i] = code[i];
            word_i++;
        }
    }
    return 1;
}
