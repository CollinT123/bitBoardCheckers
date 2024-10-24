#include "utility.h"
#include <stdio.h>

//Check if the piece player wants to move exists at that space
int checkIfPieceExists(int bitBoard[], int spaceToMove){
    if(bitBoard[spaceToMove] == 1){
        return 1;
    }
    return 0;

}
//check if piece is a queen
int checkIfQueen(int bitBoardQueen[], int pieceToCheck){
    if(bitBoardQueen[pieceToCheck] == 1){
        return 1;
    }
    else{
        return 0;
    }

}
//Check if the move is valid. Able to check for occupied space and if move is in range and diagnol
int checkifValidMoveRed(int bitBoardToMove[], int bitBoardToCheck[], int spaceToMove, int pieceToMove){
    //check if move is diagnol
    if(spaceToMove != pieceToMove+7 && spaceToMove != pieceToMove + 9 && spaceToMove != pieceToMove+18 && spaceToMove != pieceToMove+14){
        return 0;
    }
    //check if space to move is occupied
    if(bitBoardToMove[spaceToMove] == 0 && bitBoardToCheck[spaceToMove] == 0){
        //if it is not a jump return valid move
        if(spaceToMove == pieceToMove+7 || spaceToMove == pieceToMove + 9){
            return 1;
        }
        //check to see if jump is valid
        else{
            //check if jumping over an oppsing piece
            if(spaceToMove == pieceToMove+14){
                if(bitBoardToCheck[pieceToMove+7] == 1){
                    return 1;
                }
                return 0;
            }
            //check if jumping over an oppising piece in other direction
            else{
                if(bitBoardToCheck[pieceToMove+9] == 1){
                    return 1;
                }
                return 0;
            }
        }
    }
    else{
        return 0;
    }
}
int checkifValidMoveBlack(int bitBoardToMove[], int bitBoardToCheck[], int spaceToMove, int pieceToMove){
    //check if move is diagnol
    if(spaceToMove != pieceToMove-7 && spaceToMove != pieceToMove - 9 && spaceToMove != pieceToMove-18 && spaceToMove != pieceToMove-14){
        return 0;
    }
    //check if space to move is occupied
    if(bitBoardToMove[spaceToMove] == 0 && bitBoardToCheck[spaceToMove] == 0){
        //if it is not a jump return valid move
        if(spaceToMove == pieceToMove-7 || spaceToMove == pieceToMove - 9){
            return 1;
        }
        //check to see if jump is valid
        else{
            //check if jumping over piece
            if(spaceToMove == pieceToMove-14){
                if(bitBoardToCheck[pieceToMove-7] == 1){
                    return 1;
                }
                return 0;
            }
            //check if jumping over piece in the other direction
            else{
                if(bitBoardToCheck[pieceToMove-9] == 1){
                    return 1;
                }
                return 0;
            }
        }
    }
    else{
        return 0;
    }
}
//establish boards
void initializeBoards(int bitBoardRed[], int bitBoardBlack[], int bitBoardQueen[]){
    //Establish red board
    for(int i =0; i<64; i++){
        bitBoardRed[i] = 0;
    }
    for(int i = 0; i<=7; i=i+2){
        bitBoardRed[i] = 1;
    }
    for(int i = 9; i<=15; i=i+2){
        bitBoardRed[i] = 1;
    }
    for(int i = 16; i<=22; i=i+2){
        bitBoardRed[i] = 1;
    }
    //establish black board
    for(int i = 0; i < 64; i++){
        bitBoardBlack[i] = 0;
    }
    for(int i =57; i<64; i=i+2){
        bitBoardBlack[i] = 1;
    }
    for(int i = 48; i<=55; i=i+2){
        bitBoardBlack[i] = 1;
    }
    for(int i = 41; i<=47; i=i+2){
        bitBoardBlack[i] = 1;
    }
    //establish queen board
    for(int i =0; i<64; i++){
        bitBoardQueen[i] = 0;
    }


}
//printBoard
void printBoard(int bitBoardRed[], int bitBoardBlack[], int bitBoardQueen[]){
    //Space tracker used to print board top to bottom to allow A1 to be space 0
    int SpaceTracker = 56;
    char letterToPrint = 104;
    //print either b for black piece, r for red piece or - for open space
    for(int i = 0; i<8; i++){
        printf("%c", letterToPrint);
        printf("|");
        for(int k = SpaceTracker; k<SpaceTracker+8; k++){
            if(bitBoardBlack[k] == 1){
                if(bitBoardQueen[k]==1){
                    printf("B");
                }
                else{
                    printf("b");
                }
            }
            else if(bitBoardRed[k] == 1){
                if(bitBoardQueen[k]==1){
                    printf("R");
                }
                else{
                    printf("r");
                }
            }
            else{
                printf("-");
            }
        }
        letterToPrint--;
        SpaceTracker = SpaceTracker-8;
        printf("\n");
    }
    printf("--12345678\n");
}
//convert letter and number to a space on bitBoard
int convertMoveToBitBoard(char moveLetter, int moveNumber){
    //convert letter row to a number
    int moveLetterToNumber;
    if(moveLetter == 'a'){
        moveLetterToNumber = 0;
    }
    if(moveLetter == 'b'){
        moveLetterToNumber = 1;
    }
    if(moveLetter == 'c'){
        moveLetterToNumber = 2;
    }
    if(moveLetter == 'd'){
        moveLetterToNumber = 3;
    }
    if(moveLetter == 'e'){
        moveLetterToNumber = 4;
    }
    if(moveLetter == 'f'){
        moveLetterToNumber = 5;
    }
    if(moveLetter == 'g'){
        moveLetterToNumber = 6;
    }
    if(moveLetter == 'h'){
        moveLetterToNumber = 7;
    }
    //return the move in the context of the bit board(a space the array can read)
    return (moveLetterToNumber*8) + moveNumber;
}
//move a queen
void moveQueen(int bitBoardToMove[], int bitBoardToCheck[], int initialSpaceInBitBoard, int bitBoardQueen[]){
// initialize variables needed
    int checkValid = 0;
    int spaceToMoveInBitBoard;
    int attemptingJump = 0;
    //check if piece wants to move to a valid location
    checkValid = 0;
    while(checkValid==0){
        printf("Select place to move");
        printf("\nEnter Row Letter in lowercase and collum number with no spaces: ");
        char moveLetter;
        scanf(" %c", &moveLetter);
        int moveNumber;
        scanf("%d", &moveNumber);
        spaceToMoveInBitBoard = convertMoveToBitBoard(moveLetter, moveNumber-1);
        checkValid = checkifValidMoveRed(bitBoardToMove, bitBoardToCheck, spaceToMoveInBitBoard, initialSpaceInBitBoard);
        if(checkValid == 0){
            checkValid = checkifValidMoveBlack(bitBoardToMove, bitBoardToCheck, spaceToMoveInBitBoard, initialSpaceInBitBoard);
        }
        if(checkValid==0){
            printf("Please enter a valid space\n");
        }
    }
    //check and see if attempting jump, used later for double jump
    if(spaceToMoveInBitBoard > initialSpaceInBitBoard + 9 || spaceToMoveInBitBoard < initialSpaceInBitBoard - 9){
        attemptingJump=1;
    }
    //move piece
    bitBoardToMove[initialSpaceInBitBoard] = 0;
    bitBoardToMove[spaceToMoveInBitBoard] = 1;
    bitBoardQueen[initialSpaceInBitBoard] = 0;
    bitBoardQueen[spaceToMoveInBitBoard] = 1;
    //if jumping delete correct piece
    if(attemptingJump == 1){
        if(spaceToMoveInBitBoard == initialSpaceInBitBoard+14){
            bitBoardToCheck[initialSpaceInBitBoard+7] = 0;
            printf("Jump Succesful\n");
        }
        if(spaceToMoveInBitBoard == initialSpaceInBitBoard+18){
            bitBoardToCheck[initialSpaceInBitBoard+9] = 0;
            printf("jump Succesful\n");
        }
        if(spaceToMoveInBitBoard == initialSpaceInBitBoard-14){
            bitBoardToCheck[initialSpaceInBitBoard-7] = 0;
            printf("Jump Succesful\n");
        }
        if(spaceToMoveInBitBoard == initialSpaceInBitBoard-18){
            bitBoardToCheck[initialSpaceInBitBoard-9] = 0;
            printf("jump Succesful\n");
        }
    }
    //double jump
    if(attemptingJump == 1){
        if(bitBoardToCheck[initialSpaceInBitBoard+27] == 1){
            if(checkifValidMoveRed(bitBoardToMove, bitBoardToCheck, initialSpaceInBitBoard+36, initialSpaceInBitBoard+27)){
                printBoard(bitBoardToMove, bitBoardToCheck, bitBoardQueen);
                printf("Double Jump!\n");
                moveQueen(bitBoardToMove, bitBoardToCheck, spaceToMoveInBitBoard, bitBoardQueen);
            }
        }
        if(bitBoardToCheck[initialSpaceInBitBoard+21] == 1){
            if(checkifValidMoveRed(bitBoardToMove, bitBoardToCheck, initialSpaceInBitBoard+28, initialSpaceInBitBoard+21)){
                printBoard(bitBoardToMove, bitBoardToCheck, bitBoardQueen);
                printf("Double Jump!\n");
                moveQueen(bitBoardToMove, bitBoardToCheck, spaceToMoveInBitBoard, bitBoardQueen);
            }
        }
        if(bitBoardToCheck[initialSpaceInBitBoard-27] == 1){
            if(checkifValidMoveBlack(bitBoardToMove, bitBoardToCheck, initialSpaceInBitBoard-36, initialSpaceInBitBoard-27)){
                printBoard(bitBoardToMove, bitBoardToCheck, bitBoardQueen);
                printf("Double Jump!\n");
                moveQueen(bitBoardToMove, bitBoardToCheck, spaceToMoveInBitBoard, bitBoardQueen);
            }
        }
        if(bitBoardToCheck[initialSpaceInBitBoard-21] == 1){
            if(checkifValidMoveBlack(bitBoardToMove, bitBoardToCheck, initialSpaceInBitBoard-28, initialSpaceInBitBoard-21)){
                printBoard(bitBoardToMove, bitBoardToCheck, bitBoardQueen);
                printf("Double Jump!\n");
                moveQueen(bitBoardToMove, bitBoardToCheck, spaceToMoveInBitBoard, bitBoardQueen);
            }
        }
    }
}



//move a piece
void movePieceRed(int bitBoardToMove[], int bitBoardToCheck[], int initialSpaceInBitBoard, int bitBoardQueen[]){
// initialize variables needed
    int checkValid = 0;
    int spaceToMoveInBitBoard;
    int attemptingJump = 0;
//check if piece exists at given location and will loop until valid location is entered
    if(initialSpaceInBitBoard == 64){
        while(checkValid == 0){
            printf("Select piece to move");
            printf("\nEnter Row Letter in lowercase and collum number with no spaces: ");
            char moveLetter;
            scanf(" %c", &moveLetter);
            int moveNumber;
            scanf("%d", &moveNumber);
            initialSpaceInBitBoard = convertMoveToBitBoard(moveLetter, moveNumber-1);
            checkValid = checkIfPieceExists(bitBoardToMove, initialSpaceInBitBoard);
            if(checkValid == 0){
                printf("Please enter a valid space\n");
            }
        }
    }
    //if attempting to move a queen switch to move queen function
    if(bitBoardQueen[initialSpaceInBitBoard] == 1){
        moveQueen(bitBoardToMove, bitBoardToCheck, initialSpaceInBitBoard, bitBoardQueen);
        return;
    }
    //check if piece wants to move to a valid location
    checkValid = 0;
    while(checkValid==0){
        printf("Select place to move");
        printf("\nEnter Row Letter in lowercase and collum number with no spaces: ");
        char moveLetter;
        scanf(" %c", &moveLetter);
        int moveNumber;
        scanf("%d", &moveNumber);
        spaceToMoveInBitBoard = convertMoveToBitBoard(moveLetter, moveNumber-1);
        checkValid = checkifValidMoveRed(bitBoardToMove, bitBoardToCheck, spaceToMoveInBitBoard, initialSpaceInBitBoard);
        if(checkValid==0){
            printf("Please enter a valid space\n");
        }
    }
    //check and see if attempting jump, used later for double jump
    if(spaceToMoveInBitBoard > initialSpaceInBitBoard + 9){
        attemptingJump=1;
    }
    //move piece
    bitBoardToMove[initialSpaceInBitBoard] = 0;
    bitBoardToMove[spaceToMoveInBitBoard] = 1;
    //if jumping delete correct piece
    if(attemptingJump == 1){
        if(spaceToMoveInBitBoard == initialSpaceInBitBoard+14){
            bitBoardToCheck[initialSpaceInBitBoard+7] = 0;
            printf("Jump Succesful\n");
        }
        if(spaceToMoveInBitBoard == initialSpaceInBitBoard+18){
            bitBoardToCheck[initialSpaceInBitBoard+9] = 0;
            printf("jump Succesful\n");
        }
    }
    //double jump
    if(attemptingJump == 1){
        if(bitBoardToCheck[initialSpaceInBitBoard+27] == 1){
            if(checkifValidMoveRed(bitBoardToMove, bitBoardToCheck, initialSpaceInBitBoard+36, initialSpaceInBitBoard+27)){
                printBoard(bitBoardToMove, bitBoardToCheck, bitBoardQueen);
                printf("Double Jump!\n");
                movePieceRed(bitBoardToMove, bitBoardToCheck, spaceToMoveInBitBoard, bitBoardQueen);
            }
        }
        if(bitBoardToCheck[initialSpaceInBitBoard+21] == 1){
            if(checkifValidMoveRed(bitBoardToMove, bitBoardToCheck, initialSpaceInBitBoard+28, initialSpaceInBitBoard+21)){
                printBoard(bitBoardToMove, bitBoardToCheck, bitBoardQueen);
                printf("Double Jump!\n");
                movePieceRed(bitBoardToMove, bitBoardToCheck, spaceToMoveInBitBoard, bitBoardQueen);
            }
        }
    }
}

void movePieceBlack(int bitBoardToMove[], int bitBoardToCheck[], int initialSpaceInBitBoard, int bitBoardQueen[]){
// initialize variables needed
    int checkValid = 0;
    int spaceToMoveInBitBoard;
    int attemptingJump = 0;
//check if piece exists at given location and will loop until valid location is entered
    if(initialSpaceInBitBoard == 64){
        while(checkValid == 0){
            printf("Select piece to move");
            printf("\nEnter Row Letter in lowercase and collum number with no spaces: ");
            char moveLetter;
            scanf(" %c", &moveLetter);
            int moveNumber;
            scanf("%d", &moveNumber);
            initialSpaceInBitBoard = convertMoveToBitBoard(moveLetter, moveNumber-1);
            checkValid = checkIfPieceExists(bitBoardToMove, initialSpaceInBitBoard);
            if(checkValid == 0){
                printf("Please enter a valid space\n");
            }
        }
    }
    //if attempting to move a queen switch to move queen function
    if(bitBoardQueen[initialSpaceInBitBoard] == 1){
        moveQueen(bitBoardToMove, bitBoardToCheck, initialSpaceInBitBoard, bitBoardQueen);
        return;
    }
    //check if piece wants to move to a valid location
    checkValid = 0;
    while(checkValid==0){
        printf("Select place to move");
        printf("\nEnter Row Letter in lowercase and collum number with no spaces: ");
        char moveLetter;
        scanf(" %c", &moveLetter);
        int moveNumber;
        scanf("%d", &moveNumber);
        spaceToMoveInBitBoard = convertMoveToBitBoard(moveLetter, moveNumber-1);
        checkValid = checkifValidMoveBlack(bitBoardToMove, bitBoardToCheck, spaceToMoveInBitBoard, initialSpaceInBitBoard);
        if(checkValid==0){
            printf("Please enter a valid space\n");
        }
    }
    //check and see if attempting jump, used later for double jump
    if(spaceToMoveInBitBoard < initialSpaceInBitBoard - 9){
        attemptingJump=1;
    }
    //move piece
    bitBoardToMove[initialSpaceInBitBoard] = 0;
    bitBoardToMove[spaceToMoveInBitBoard] = 1;
    //if jumping delete correct piece
    if(attemptingJump == 1){
        if(spaceToMoveInBitBoard == initialSpaceInBitBoard-14){
            bitBoardToCheck[initialSpaceInBitBoard-7] = 0;
            printf("Jump Succesful\n");
        }
        if(spaceToMoveInBitBoard == initialSpaceInBitBoard-18){
            bitBoardToCheck[initialSpaceInBitBoard-9] = 0;
            printf("jump Succesful\n");
        }
    }
    //double jump
    if(attemptingJump == 1){
        if(bitBoardToCheck[spaceToMoveInBitBoard-7] == 1){
            if(checkifValidMoveBlack(bitBoardToMove, bitBoardToCheck, initialSpaceInBitBoard-32, initialSpaceInBitBoard-14)){
                printBoard(bitBoardToCheck, bitBoardToMove, bitBoardQueen);
                printf("Double Jump!\n");
              
                movePieceBlack(bitBoardToMove, bitBoardToCheck, spaceToMoveInBitBoard, bitBoardQueen);
            }
        }
        if(bitBoardToCheck[spaceToMoveInBitBoard-9] == 1){
            if(checkifValidMoveBlack(bitBoardToMove, bitBoardToCheck, initialSpaceInBitBoard-28, initialSpaceInBitBoard-21)){
                printBoard(bitBoardToCheck, bitBoardToMove, bitBoardQueen);
                printf("Double Jump!\n");
                movePieceBlack(bitBoardToMove, bitBoardToCheck, spaceToMoveInBitBoard, bitBoardQueen);
            }
        }
    }
}
//check the board to see if any new queens need to be created for both sides
void createQueens(int bitBoardRed[],int bitBoardBlack[],int bitBoardQueen[]){
    for(int i = 55; i<64; i++){
        if(bitBoardRed[i]== 1){
            bitBoardQueen[i] =1;
        }
    }   
    for(int i = 0; i<8; i++){
        if(bitBoardBlack[i]== 1){
            bitBoardQueen[i] =1;
        }
    }
}
//check if opponent board is empty for win condition
int checkIfWin(int bitBoard[]){
    int checkIfHasPeice = 0;
    for(int i = 0; i < 64; i++){
        if(bitBoard[i] == 1){
            checkIfHasPeice = 1;
        }
    }
    if(checkIfHasPeice==0){
        return 1;
    }
    return 0;

}

