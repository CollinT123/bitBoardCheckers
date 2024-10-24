#ifndef UTILITY_H
#define UTILITY_H

int checkIfPieceExists(int bitBoard[], int spaceToMove);
int checkIfQueen(int bitBoardQueen[], int pieceToCheck);
//Check if the move is valid. Able to check for occupied space and if move is in range and diagnol
int checkifValidMoveRed(int bitBoardToMove[], int bitBoardToCheck[], int spaceToMove, int pieceToMove);
int checkifValidMoveBlack(int bitBoardToMove[], int bitBoardToCheck[], int spaceToMove, int pieceToMove);
//establish boards
void initializeBoards(int bitBoardRed[], int bitBoardBlack[], int bitBoardQueen[]);
//printBoard
void printBoard(int bitBoardRed[], int bitBoardBlack[], int bitBoardQueen[]);
//convert letter and number to a space on bitBoard
int convertMoveToBitBoard(char moveLetter, int moveNumber);
//move a queen
void moveQueen(int bitBoardToMove[], int bitBoardToCheck[], int initialSpaceInBitBoard, int bitBoardQueen[]);
//move a piece
void movePieceRed(int bitBoardToMove[], int bitBoardToCheck[], int initialSpaceInBitBoard, int bitBoardQueen[]);
void movePieceBlack(int bitBoardToMove[], int bitBoardToCheck[], int initialSpaceInBitBoard, int bitBoardQueen[]);
void createQueens(int bitBoardRed[],int bitBoardBlack[],int bitBoardQueen[]);
int checkIfWin(int bitBoard[]);
#endif
