#include <stdio.h>

int search_word(char word[50], FILE *file) {
    int index = 0;
    char character = fgetc(file);

    while (character != EOF && character != ' ') {
        word[index] = character;
        index++;
        character = fgetc(file);
    }
    word[index] = '\0';

    if(character == EOF) return 0; // nedokoncene slovo
    else return 1;
}

int main(int zevraj_tu_ma_byt_daco_intove, char *arg[]){
//int main(){
    FILE *file;
    file = fopen(arg[1], "r");
    if(file == NULL) return -1;
    int count = 0;
    int read = 1;

    char word[50];
    while(read) {
        read = search_word(word,file);
        //puts(word);

        int len = 0;
        for (int i = 0; word[i] != '\0'; ++i) {
            len++;
        }
        if(len < 6) continue;

        for (int c = 0; word[c + 5] != '\0'; ++c) {
            //printf("   ..%d..\n", c);
            if (word[c] == 'a' || word[c] == 'A')
                if (word[c + 1] == 'n' || word[c + 1] == 'N')
                    if (word[c + 2] == 'a' || word[c + 2] == 'A')
                        if (word[c + 3] == 'n' || word[c + 3] == 'N')
                            if (word[c + 4] == 'a' || word[c + 4] == 'A')
                                if (word[c + 5] == 's' || word[c + 5] == 'S')
                                    count++;
        }
    }
    //printf("\n%d\n", count);
    fclose(file);

    file = fopen(arg[1], "w");
    if(count == 0) fputc('0', file);
    else {
        char string[5];
        for (int num, i = 0; count > 0; count /= 10, i++) {
            num = count % 10;
            string[i] = num + '0';
            string[i + 1] = '\0';
        }

        int len = 0;
        for (int i = 0; string[i] != '\0'; ++i) {
            len++;
        }

        for (int i = len - 1; i >= 0; --i) {
            fputc(string[i], file);
        }
    }
    fclose(file);
    
    return 0;
}

//    int num;
//    char write;
//    if(count > 9){
//        num = count/10;
//        write = (char)num;
//        fputc(write, file);
//        num = count % 10;
//        write = (char)num;
//        fputc(write, file);
//    }else{
//        num = count % 10;
//        write = (char)num;
//        fputc(write, file);
//    }
//    if(count == 0) fputc('0', file);
//    for(int num; count > 0; count/=10){
//        num = count % 10;
//        fputc(num + '0', file); // ONO TO IDE
//    }
    //fprintf(file, "%d", count);



//    char character = fgetc(file);
//    while (character != 'a' && character != 'A'){
//        character = fgetc(file);
//    }
//
//    char string

//    int count = 0;
//    const char pineapple[] = "ananas";
//    const char PINEAPPLE[] = "ANANAS";
//    char character;
//    int index = -1;
//
//    FILE *file;
//    file = fopen(arg[1], "r");
//    if(file == NULL) return -1;
//
//    character = fgetc(file);
//    while (character != EOF){
//        if(index == -1 && (character == 'a' || character == 'A')) index = 0;
//        if(index>=0) {
//            if (character == pineapple[index] || character == PINEAPPLE[index]) index++;
//            else index = -1;
//            if(index == 6){
//                index = -1;
//                count ++;
//                //printf("\n");
//            }
//        }
//        character = fgetc(file);
//    }
//    fclose(file);
//    file = fopen(arg[1], "w");
//
//    printf("%d" , count);
//    if(count == 0) fputc('0', file);
//
//    for(int num; count > 0; count/=10){
//        num = count % 10;
//        fputc(num + '0', file); // ONO TO IDE
//    }
////    fputc((char)num, file);
////    fprintf(file, "%d\n", count);
////    fputc(count,file);
//    fclose(file);
////    printf("\n%d\n", count);
