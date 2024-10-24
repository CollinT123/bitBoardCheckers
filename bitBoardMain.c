#include <stdio.h>
#include <stdint.h>
#include "utility.h"

int main(){
/*
    int bitBoardRed[64];
    int bitBoardBlack[64];
    int bitBoardQueen[64];
    initializeBoards(bitBoardRed, bitBoardBlack, bitBoardQueen);
    int keepPlaying = 1;
    bitBoardBlack[32]=1;
    bitBoardRed[25] = 1;
    bitBoardRed[18] = 0;
    bitBoardRed[0] = 0;
    bitBoardBlack[39]=1;
    bitBoardRed[30] = 1;
    bitBoardRed[14]=1;
    printBoard(bitBoardRed, bitBoardBlack, bitBoardQueen);
    movePieceBlack(bitBoardBlack, bitBoardRed, 64, bitBoardQueen);
    printBoard(bitBoardRed, bitBoardBlack, bitBoardQueen);
*/

    int bitBoardRed[64];
    int bitBoardBlack[64];
    int bitBoardQueen[64];
    int keepPlaying = 1;
    initializeBoards(bitBoardRed, bitBoardBlack, bitBoardQueen);
    printf("Welcome to Checkers!\n");
    printf("Lowercase letters represent regular pieces, uppercase letters represent queens\n");
        while(keepPlaying == 1){
        printBoard(bitBoardRed, bitBoardBlack, bitBoardQueen);
        printf("Red to move\n");
        movePieceRed(bitBoardRed, bitBoardBlack, 64, bitBoardQueen);
        createQueens(bitBoardRed, bitBoardBlack, bitBoardQueen);
        printBoard(bitBoardRed, bitBoardBlack, bitBoardQueen);
        if(checkIfWin(bitBoardBlack) == 1){
            printf("Congratulations red you win!");
            return 0;
        }
        printf("Black to move\n");
        movePieceBlack(bitBoardBlack, bitBoardRed, 64, bitBoardQueen);
        createQueens(bitBoardRed, bitBoardBlack, bitBoardQueen);
        printBoard(bitBoardRed,bitBoardBlack, bitBoardQueen);
        if(checkIfWin(bitBoardRed) == 1){
            printf("Congratulations black you win!");
            return 0;
        }
    }    
    
    return 0;
}