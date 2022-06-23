#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Levels
#include "levels/Abominable.h"
#include "levels/Alien.h"
#include "levels/Awful.h"
#include "levels/Bad.h"
#include "levels/Blood.h"
#include "levels/Butcher.h"
#include "levels/Clown.h"
#include "levels/Crazy.h"
#include "levels/Creepy.h"
#include "levels/Crime.h"
#include "levels/Dangerous.h"
#include "levels/Death.h"
#include "levels/Demonic.h"
#include "levels/Dracula.h"
#include "levels/Evil.h"
#include "levels/Fear.h"
#include "levels/Forbidding.h"
#include "levels/Fury.h"
#include "levels/Ghost.h"
#include "levels/Help.h"
#include "levels/Horror.h"
#include "levels/Joker.h"
#include "levels/Kanibal.h"
#include "levels/Knight.h"
#include "levels/Murderer.h"
#include "levels/Nightmare.h"
#include "levels/Sad.h"
#include "levels/Silly.h"
#include "levels/Spirit.h"
#include "levels/Tiger.h"
#include "levels/War.h"

#define clear() printf("\033[H\033[J")

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"


int divideDigits(int num, int method){
    if (method){
        int mod = num % 10;  //split last digit from number
        return mod;
    } else {
        num = num / 10; //split first digit from number
        return num;
    }
}

int getFirstDigit(int Number) {
    int FirstDigit, Count;
    Count = log10(Number);
    FirstDigit = Number / pow(10, Count);
}


int second_last_digit(int N) {
    N = N / 10;
    return N % 10;
}

int getNumberOfDigits(int n) {
    int count = 0;

    while(n !=0) {
        n=n/10;
        count++;
    }

    return count;
}

unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}

void displayGameBoard(int board[6][6]){

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {

            if (getNumberOfDigits(board[i][j]) == 3) {

                switch (getFirstDigit(board[i][j])) {
                case 1:
                    printf(GRN "%d " RESET, second_last_digit(board[i][j]));
                    break;
                case 2:
                    printf(YEL "%d " RESET, second_last_digit(board[i][j]));
                    break;
                case 3:
                    printf(BLU "%d " RESET, second_last_digit(board[i][j]));
                    break;
                case 4:
                    printf(RED "%d " RESET, second_last_digit(board[i][j]));
                    break;
                default:
                    break;
                }
            } else {

                switch (board[i][j])
                {
                case 10:
                    printf(GRN "x " RESET);
                    break;

                case 20:
                    printf(YEL "x " RESET);
                    break;

                case 30:
                    printf(BLU "x " RESET);
                    break;

                case 40:
                    printf(RED "x " RESET);
                    break;

                default :
                    printf("%d ", divideDigits(board[i][j], 1));
                }

            }
        }
        printf("\n");
    }  
}

int findXYpos(int color, int board[6][6]){
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {            
            if (board[i][j] == color) {
                return concatenate(i,j);
            }
        }
    }
}

int isChainCompleted(int board[6][6], int color){
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if(divideDigits(board[i][j], 0) == getFirstDigit(color) && board[i][j] != color)
                return 0;
        }
    }
    return 1;
}

void eraseChain(int board[6][6], int chain) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if(getFirstDigit(board[i][j]) == getFirstDigit(chain) && getNumberOfDigits(board[i][j]) > 2) {
                board[i][j] = board[i][j]/10;
            }
               
        }
    }
}

void restartLevel(int board[6][6]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if(getNumberOfDigits(board[i][j]) > 2) {
                board[i][j] = board[i][j]/10;
            }
               
        }
    }
}

int numberOfCasePlayed(int board[6][6]) {
    int counter = 0;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if(getNumberOfDigits(board[i][j]) > 2) {
                counter += 1;
            }
        }
    }
    return counter;
}

void play(int board[6][6], int chain) {
    int starter;
    starter = findXYpos(chain, board);
    
    int xPos = divideDigits(starter, 0);
    int yPos = divideDigits(starter, 1);

    int isChainOver = 0;
    int chainJustGotChanged = 0;

    while (isChainOver == 0)
    {

        if (numberOfCasePlayed(board) == 0){
            if(chainJustGotChanged == 0) {
                starter = findXYpos(10, board);
                chain = 10;
                xPos = divideDigits(starter, 0);
                yPos = divideDigits(starter, 1);
            }
        }

        if (chainJustGotChanged) {
            chainJustGotChanged = 0;
        }

        switch (chain)
        {
        case 10:
            printf("\n--- line: %d, column: %d, chain: %sgreen%s ---\n", xPos+1, yPos+1, GRN, RESET);
            break;
        case 20:
            printf("\n--- line: %d, column: %d, chain: %syellow%s ---\n", xPos+1, yPos+1, YEL, RESET);
            break;
        case 30:
            printf("\n--- line: %d, column: %d, chain: %sblue%s ---\n", xPos+1, yPos+1, BLU, RESET);
            break;
        case 40:
            printf("\n--- line: %d, column: %d, chain: %sred%s ---\n", xPos+1, yPos+1, RED, RESET);
            break;
        
        default:
            break;
        }
        
        printf("Select a direction (U, D, R, L).\n");
        printf("Cancel the previous move (B).\n");
        printf("Erase the chain (K).\n");
        printf("Restart the level (X).\n");
        printf("Select another chain (C).\n");

        int taken;

        char direction;
        printf("\n>> ");
        fflush(stdin);
        scanf("%c", &direction);
        fflush(stdin);

        int lastMove;
        int lastPos;
        
        switch (direction)
        {
        case 'u':
            printf("u\n");
            if(xPos > 0) {
                if (getFirstDigit(board[xPos][yPos]) == getFirstDigit(board[xPos-1][yPos])) {
                    if (getNumberOfDigits(board[xPos-1][yPos]) < 3) {
                        if (board[xPos-1][yPos] % 5 != 0) {
                            if (board[xPos-1][yPos]*10 >= board[xPos][yPos]) {
                                xPos -= 1;
                                taken = board[xPos][yPos] * 10;
                                board[xPos][yPos] = taken;

                                lastMove = 1;
                                lastPos = board[xPos][yPos];
                            }
                        }
                    }
                }
            }

            break;
        case 'd':
            printf("d\n");
            if(xPos < 5) {
                if(getFirstDigit(board[xPos][yPos]) == getFirstDigit(board[xPos+1][yPos])) {
                    if (getNumberOfDigits(board[xPos+1][yPos]) < 3) {
                        if (board[xPos+1][yPos] % 5 != 0) {
                            if (board[xPos+1][yPos]*10 >= board[xPos][yPos]) {
                                xPos += 1;
                                taken = board[xPos][yPos] * 10;
                                board[xPos][yPos] = taken;

                                lastMove = 2;
                                lastPos = board[xPos][yPos];
                            }
                        }
                    }
                }
            }
            
            break;
        case 'r':
            printf("r\n");
            if(yPos < 5) {
                if(getFirstDigit(board[xPos][yPos]) == getFirstDigit(board[xPos][yPos+1])) {
                    if (getNumberOfDigits(board[xPos][yPos+1]) < 3) {
                        if (board[xPos][yPos+1] % 5 != 0) {
                            if (board[xPos][yPos+1]*10 >= board[xPos][yPos]) {
                                yPos += 1; 
                                taken = board[xPos][yPos] * 10;
                                board[xPos][yPos] = taken;

                                lastMove = 3;
                                lastPos = board[xPos][yPos];
                            }
                        }
                    }
                }
            }

            break;
        case 'l':
            printf("l\n");
            if(yPos > 0) {
                if(getFirstDigit(board[xPos][yPos]) == getFirstDigit(board[xPos][yPos-1])) {
                    if (getNumberOfDigits(board[xPos][yPos-1]) < 3) {
                        if (board[xPos][yPos-1] % 5 != 0) {
                            if (board[xPos][yPos-1]*10 >= board[xPos][yPos]) {
                                yPos -= 1;
                                taken = board[xPos][yPos] * 10;
                                board[xPos][yPos] = taken;

                                lastMove = 4;
                                lastPos = board[xPos][yPos];
                            }
                        }
                    }
                }
            }
            break;

        case 'b':
            if (board[xPos][yPos] != 10 && board[xPos][yPos] != 20 && board[xPos][yPos] != 30 && board[xPos][yPos] != 40) {
                for (int f = 0; f < 6; f++) {
                    for (int q = 0; q < 6; q++) {
                        if ((board[f][q]) == lastPos) {
                            lastPos = board[f][q];
                        }
                    }
                }
                
                board[xPos][yPos] = lastPos/10;
                
                switch (lastMove)
                {
                case 1:
                    xPos += 1;
                    break;
                case 2:
                    xPos -= 1;
                    break;
                case 3:
                    yPos -= 1;
                    break;
                case 4:
                    yPos += 1;
                    break;
                default:
                    break;
                }

                lastMove = 0;
                lastPos = 0;
            }
            break;
        
        case 'k':
            eraseChain(board, chain);
            xPos = divideDigits(starter, 0);
            yPos = divideDigits(starter, 1);
            break;

        case 'x':
            restartLevel(board);
            break;

        case 'c':
            eraseChain(board, chain);

            switch (chain)
            {
            case 10:
                chain = 20;
                break;
            case 20:
                chain = 30;
                break;
            case 30:
                chain = 40;
                break;
            case 40:
                chain = 10;
                break;
            
            default:
                break;
            }
            starter = findXYpos(chain, board);
            xPos = divideDigits(starter, 0);
            yPos = divideDigits(starter, 1);

            chainJustGotChanged = 1;
            break;
        default:
            break;
        }
        clear();

        displayGameBoard(board);

        // Debug
        // for (int i = 0; i < 6; i++) {
        //     for (int j = 0; j < 6; j++) {
        //         printf("%d|", board[i][j]);
        //         int lol = board[i][j];
        //     }
        //     printf("\n");
        // }

        if(isChainCompleted(board, chain)){
            printf("\nCongratulation, you've completed the level!\n\n");
            isChainOver = 1;
        }        
    }
}


int main() {
    clear();

    printf("%s|---------------------|%s\n", YEL, RESET);
    printf("%s|%s   %sCardinal Chains%s   %s|%s\n", RED, RESET, BLU, RESET, RED, RESET);
    printf("%s|---------------------|%s\n", GRN, RESET);
    printf("\nPlease, choose a level :\n");

    char *ll[] = {"Abominable", "Alien", "Awful", "Bad", "Blood", "Butcher", "Clown", "Crazy", "Creepy", "Crime", "Dangerous", "Death", "Demonic", "Dracula", "Evil", "Fear", "Forbidding", "Fury", "Ghost", "Help", "Horror", "Joker", "Kanibal", "Knight", "Murderer", "Nightmare", "Sad", "Silly", "Spirit", "Tiger", "War"};
    int *ll2[] = {*Abominable, *Alien, *Awful, *Bad, *Blood, *Butcher, *Clown, *Crazy, *Creepy, *Crime, *Dangerous, *Death, *Demonic, *Dracula, *Evil, *Fear, *Forbidding, *Fury, *Ghost, *Help, *Horror, *Joker, *Kanibal, *Knight, *Murderer, *Nightmare, *Sad, *Silly, *Spirit, *Tiger, *War};

    for (int i = 0; i < 30; i++){
        printf("[%d] %s\n", i+1, ll[i]);
    }

    int level;

    printf("\n>> ");
    scanf("%d", &level);
    fflush(stdin);
    int *tab = ll2[level-1];
    
    int c = 0;
    int newTab[6][6] = {0};

    for(int i = 0; i < 36; i++) {
        int j = 0;
        c += 1;
        newTab[j][i] = tab[i];

        if (c == 6) {
            c = 0;
            j += 1;
        }
    }
    
    displayGameBoard(newTab);
    play(newTab, 10);
    play(newTab, 20);
    play(newTab, 30);
    play(newTab, 40);

    return 0;
}