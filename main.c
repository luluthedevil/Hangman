#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hangman.h"

char secretWord[WORD_SIZE];
char tries[26];
int tried = 0;


int existLetter(char letter) {
	int j;
    for(j = 0; j < strlen(secretWord); j++) {
        if(letter == secretWord[j]) {
            return 1;
        }
    }

    return 0;
}

int wrongTries() {
    int wrong = 0;
    int i;
    for(i = 0; i < tried; i++) {

        if(!existLetter(tries[i])) {
            wrong++;
        }
    }

    return wrong;
}

int hanged() {
    return wrongTries() >= 5;
}

int win() {
	int i;
    for(i = 0; i < strlen(secretWord); i++) {
        if(!alreadyTried(secretWord[i])) {
            return 0;
        }
    }

    return 1;
}


void open() {
    printf("/****************/\n");
    printf("/* Hangman game */\n");
    printf("/****************/\n\n");
}

void kick() {
    char kick;
    printf("Type a letter ");
    scanf(" %c", &kick);

    if(existLetter(kick)) {
        printf("\nYou are right: the word has the letter %c\n\n", kick);
    } else {
        printf("\nBetter luck next time: the word does't have letter %c\n\n", kick);
    }

    tries[tried] = kick;
    tried++;
}

int alreadyTried(char letter) {
    int find = 0;
    int j;
    for(j = 0; j < tried; j++) {
        if(tries[j] == letter) {
            find = 1;
            break;
        }
    }

    return find;
}

void drawHangman() {

    int errors = wrongTries();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (errors>=1?'(':' '), (errors>=1?'_':' '), (errors>=1?')':' '));
    printf(" |      %c%c%c  \n", (errors>=3?'\\':' '), (errors>=2?'|':' '), (errors>=3?'/': ' '));
    printf(" |       %c     \n", (errors>=2?'|':' '));
    printf(" |      %c %c   \n", (errors>=4?'/':' '), (errors>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");
	
	int i;
    for(i = 0; i < strlen(secretWord); i++) {

        if(alreadyTried(secretWord[i])) {
            printf("%c ", secretWord[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");

}

void chooseWord() {
    FILE* f;

    f = fopen("words.txt", "r");
    if(f == 0) {
        printf("Database not available\n\n");
        exit(1);
    }

    int quantityOfWords;
    fscanf(f, "%d", &quantityOfWords);

    srand(time(0));
    int random = rand() % quantityOfWords;

	int i;
    for(i = 0; i <= random; i++) {
        fscanf(f, "%s", secretWord);
    }

    fclose(f);
}


void addWord() {
    char want;

    printf("Do you want add a new word to the game (Y/N)?");
    scanf(" %c", &want);

    if(want == 'Y' || want == 'y') {
        char newWord[WORD_SIZE];

        printf("Type the new word in capital letters: ");
        scanf("%s", newWord);

        FILE* f;

        f = fopen("words.txt", "r+");
        if(f == 0) {
            printf("Database not available\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", newWord);

        fclose(f);

    }

}

int main() {

    open();
    chooseWord();

    do {

        drawHangman();
        kick();

    } while (!win() && !hanged());

    if(win()) {
        printf("\nCongratulations! You won the game\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

    } else {
        printf("\nI'm sorry, you were hanged!\n");
        printf("The secret word was **%s**\n\n", secretWord);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    addWord();
}
