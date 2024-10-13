#include "hangman.h"
//#include "hangman.c"
#include "morse.h"
#include <time.h>
#include <stdlib.h>

int main(){
    srand(time(NULL));
    char secret[20]; 
    get_word(secret);
    hangman(secret);

    return 0;
}
