#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include "hangman.h"


int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]){
    int check = 1;
    for (int i_s = 0; i_s < strlen(secret); i_s++) {
        check = 0;
        for (int i_l = 0; i_l < strlen(letters_guessed); i_l++) {
            if(secret[i_s] == letters_guessed[i_l]){
                check = 1;
                break;
            }
        }
        if(check == 0) {break;}
    }
    return check;
}

int inside(const char letter, const char string[]){
    for (int i = 0; i < strlen(string); i++) {
        if(letter == string[i]) {return 1;}
    } return 0;
}

void morevypissa (char guessed_word[]){
    printf("%c", guessed_word[0]);
    for (int i = 1; i < strlen(guessed_word); ++i) {
        printf(" %c", guessed_word[i]);
    }
    printf("\n");
}

//void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]){
//    for (int i = 0; i < strlen(secret); i++){
//        if (guessed_word[i] == '_' && (inside(secret[i], letters_guessed))) {
//            guessed_word[i] = secret[i];
//        }
//    }
//}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {
    for (int i = 0; i < strlen(secret); i++) {
        if((strchr(letters_guessed, secret[i]) != NULL)){
            guessed_word[i] = secret[i];
        }else{
            guessed_word[i] = '_';
        }
    }
    guessed_word[strlen(secret)] = '\0';
}

void get_available_letters(const char letters_guessed[], char available_letters[]){
    char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    int count = 0;

    for (int i = 0; i < 26; i++) {
        if(!inside(alphabet[i], letters_guessed)){
            available_letters[count] = alphabet[i];
            count++;
        }
    } available_letters[count] = '\0';
}

void hangman(const char secret[]){
    int guesses = 8;
    char guessed_word[] = "__________________________________________________";
    guessed_word[strlen(secret)] = '\0';
    char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    char available_letters[] = "abcdefghijklmnopqrstuvwxyz";
    char letters_guessed[26];
    int letters_count = 0;
    char input[50];

    printf("Welcome to the game, Hangman!\nI am thinking of a word that is %lu letters long.\n", strlen(secret));

    do{
        printf("-------------\nYou have %d guesses left.\nAvailable letters: %s\nPlease guess a letter: ", guesses, available_letters);
        scanf("%s", input);

        for (int i = 0; i < strlen(input); ++i) {
            input[i] = tolower(input[i]);
        }

        if(strlen(input)>1) {
            if (is_word_guessed(secret, input)) { printf("Congratulations, you won!"); }
            else { printf("Sorry, bad guess. The word was %s.", secret); }
            printf("\n");
            return;
        }

        if(inside(input[0], letters_guessed)) {printf("Oops! You've already guessed that letter: ");}
        else if(inside(input[0], alphabet)){
            letters_guessed[letters_count] = input[0];
            letters_count++;
            get_available_letters(letters_guessed, available_letters);

            if (inside(input[0], secret)) {
                printf("Good guess: ");
            } else {
                printf("Oops! That letter is not in my word: ");
                guesses--;
            }
        }else {printf("Oops! '%c' is not a valid letter: ", input[0]);}
        get_guessed_word(secret, letters_guessed, guessed_word);
        morevypissa(guessed_word);
    }while(guesses>0 && !is_word_guessed(secret, letters_guessed));
    if(guesses<1) { printf("-------------\nSorry, you ran out of guesses. The word was %s.", secret);}
    else { printf("-------------\nCongratulations, you won!");}
    printf("\n");
}
