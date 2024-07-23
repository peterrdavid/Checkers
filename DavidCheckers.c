/******************************************************************
This is to certify that this project is my own work, based on my
personal efforts in studying and applying the concepts learned. I
have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and
debugged by my own efforts. I further certify that I have not
copied in part or whole or otherwise plagiarized the work of other
students and/or persons.
Peter Jan B. David, DLSU ID# 12275395
******************************************************************/

/*
Description: This program is a simplified version of the two-player game, Checkers.
Programmed by: David, Peter Jan B. - S20B
Last modified: December 5, 2022
Version: 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayHeader(void);
void displayMenu(void);
int displayPlay(int nScore);
void displayScores(int nScore, int* nScoreA, int* nScoreB);
int displayQuit(int nQuitChoice);
void displayCongrats(char cWinner);
void displayBoard(int nBoardValues[8][8]);
int displayPieces(int nSymbol);
int countPieces(int nBoardValues[8][8]);
void swapPieces(int nBoardValues[8][8], int nP1Num, int cP1Char, int nP2Num, int cP2Char);
int checkMove(int nBoardValues[8][8], int nPlayer, int nP1Num, int cP1Char, int nP2Num, int cP2Char);
int movePiece(int nBoardValues[8][8], int nP1Num, int cP1Char, int nP2Num, int cP2Char);

int main()
{
    displayMenu();

    return 0;
}

/*  This function displays the header.
*/
void
displayHeader()
{
    printf("\n");
    printf("%23s\n", "Checkers");
    printf("%28s\n", "(Simplified Ver.)");
    printf("\n");
    printf("%s%s%s%s\n","----------", "----------","----------","----------");
}

/*  This function displays the menu containing 3 choices: Play, View Scores, and Quit.
*/
void
displayMenu()
{
    int nMenuChoice;
    int nQuitChoice = 1;
    int nQuit;
    int nBack;
    int nStop = 1;
    int nAddScore = 0;
    int nScore = 0;
    
    int nScoreA = 0;
    int nScoreB = 0;
    
    // do-while loop to keep the game going until the user decides to stop it
    do
    {
        system("clear");
        displayHeader();
        
        printf("\n");
        printf("%20s\n", "[1] Play");
        printf("%27s\n", "[2] View Scores");
        printf("%20s\n", "[3] Quit");
        printf("\n");
        
        printf("%s%s%s%s\n","----------", "----------","----------","----------");
        
        printf("Enter choice: ");
        scanf("%d", &nMenuChoice);
        
        system("clear");
        
        // switch-case statement to choose from the options given
        switch(nMenuChoice)
        {
            // If user input is 1, the Play page will be displayed
            case 1:
                nAddScore = displayPlay(nScore);
                break;
            // If user input is 2, the View Scores page will be displayed
            case 2:
                displayScores(nAddScore, &nScoreA, &nScoreB);
                nAddScore = 0;
                break;
            // If user input is 3, the Quit page will be displayed
            case 3:
                nQuit = displayQuit(nQuitChoice);
                if(nQuit == 2)
                    nStop = 0; // nStop is set to 0 to terminate the do-while loop
                break;
            // If user input is none of the above, this will be displayed
            default:
                printf("INVALID INPUT!\n");
                printf("Enter any key to go back... ");
                scanf("%d", &nBack);
        }
            
    }while(nStop > 0);
    
    // This will be displayed if the user decides to stop the game, causing the entire program to end
    printf("Program terminates.\n");
}

/*  This function displays the Play page––where the gameplay happens.
    Precondition: nScore is equal to 0
    @param nScore
    @return 1 if PLAYER A wins or 2 if PLAYER B wins
*/
int
displayPlay(int nScore)
{
    char cPlayer1, cPlayer2;
    int nStart;
    
    // The numbers are stored inside an 8x8 array to locate the pieces easily
    int nBoardValues[8][8] =
    {
        {0, 2, 0, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 0, 2, 0},
        {0, 2, 0, 2, 0, 2, 0, 2},
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1},
        {3, 0, 3, 0, 3, 0, 3, 0},
        {0, 3, 0, 3, 0, 3, 0, 3},
        {3, 0, 3, 0, 3, 0, 3, 0}
    };
    
    int nP1Num, nP2Num;
    char cP1Char, cP2Char;
    int nRandomNumber;
    int nStopper = 1000;
    int nStop;
    int nStop1;
    int nStop2;
    int j, i;
    int nMoveValue;
    char cWinner;
    int nCount;
    int nP1Score, nP2Score;
    
    nScore = 0;
    
    displayHeader();
    
    printf("%29s\n", "Welcome to Checkers!");
    printf("\n");
    
    // srand() and rand() to generate numbers and randomize who gets to move first in the game
    srand((unsigned int)time(NULL));
    nRandomNumber = rand();
    
    // If the random number is an even number, PLAYER A goes first
    if(nRandomNumber % 2 == 0)
    {
        printf("%34s", "[PLAYER A], you get BLACK (X)\n");
        printf("%34s", "[PLAYER B], you get WHITE (O)\n");
        // Assign PLAYER A to player 1 and PLAYER B to player 2
        cPlayer1 = 'A';
        cPlayer2 = 'B';
        nP1Score = 1;
        nP2Score = 2;
        printf("\n");
        printf("PLAYER %c, you're the first to move.", cPlayer1);
    }
    
    // If the random number is an odd number, PLAYER B goes first
    else
    {
        printf("%34s", "[PLAYER A], you get WHITE (O)\n");
        printf("%34s", "[PLAYER B], you get BLACK (X)\n");
        // Assign PLAYER B to player 1 and PLAYER A to player 2
        cPlayer1 = 'B';
        cPlayer2 = 'A';
        nP1Score = 2;
        nP2Score = 1;
        printf("\n");
        printf("[PLAYER %c], you're the first to move.", cPlayer1);
    }
    
    printf("\n");
    
    printf("Let's begin! Enter any key to start... ");
    scanf("%d", &nStart);
    
    // for loop so PLAYER A and PLAYER B can take turns in making moves until one of them wins
    for(j = 0; j < nStopper; j++)
    {
        nStop = 1000;
        nStop1 = 100;
        nStop2 = 100;
        
        // FIRST PLAYER
        if(nStop != 1)
        {
            system("clear");
            displayHeader();
            displayBoard(nBoardValues); // This displays the checkerboard
            nCount = countPieces(nBoardValues); // This displays the remaining pieces left
            
            // This will execute if the first player has 0 pieces
            if(nCount == 1)
            {
                cWinner = cPlayer2;
                displayCongrats(cWinner);
                nStopper = 0;
                nStop = 1;
                nStop1 = 0;
                nScore = nP2Score;
            }
            
            // This for loop will only stop if the first player has succesfully moved a piece
            for(i = 0; i < nStop1; i++)
            {
                cWinner = cPlayer1;
                
                // Get the input of the piece to be moved
                printf("[PLAYER %c]'s Turn\n", cPlayer1);
                printf("Move: ");
                scanf("%d%c", &nP1Num, &cP1Char);
                
                // This will execute if the user surrenders
                if(nP1Num == 9)
                {
                    cWinner = cPlayer2;
                    displayCongrats(cWinner);
                    nStopper = 1;
                    nStop = 1;
                    nStop1 = 0;
                    nScore = nP2Score;
                }
                
                if(nStopper != 1)
                {
                    // Get the input of the landing position
                    printf("To: ");
                    scanf("%d%c", &nP2Num, &cP2Char);
                    
                    // This checks if the landing position is allowed and if the piece belongs to the user
                    nMoveValue = checkMove(nBoardValues, 2, nP1Num - 1, cP1Char - 'A', nP2Num - 1 ,cP2Char - 'A');
                    
                    switch(nMoveValue)
                    {
                        // This will execute the piece belongs to the user and the landing position is allowed
                        case 0:
                            // This function will move the piece
                            movePiece(nBoardValues, nP1Num - 1, cP1Char - 'A', nP2Num - 1 ,cP2Char - 'A');
                            nStop1 = 0;
                            // If the piece has reached the end row of the opposite side, this will be executed
                            if(nBoardValues[7][0] == 2 || nBoardValues[7][2] == 2 || nBoardValues[7][4] == 2 || nBoardValues[7][6] == 2 || nBoardValues[0][1] == 3 || nBoardValues[0][3] == 3 || nBoardValues[0][5] == 3 || nBoardValues[0][7] == 3)
                            {
                                displayCongrats(cWinner);
                                nStopper = 1;
                                nStop = 1;
                                nStop1 = 0;
                                nScore = nP1Score;
                            }
                            break;
                        // This will execute the piece does not belong to the user and the landing position is illegal
                        case 1:
                            // Thus the user will be asked to make a move again
                            printf("Please try again.\n");
                            nStop1 = 100;
                    }
                }
            }
        }
        
        // SECOND PLAYER
        
        if(nStop != 1)
        {
            system("clear");
            displayHeader();
            displayBoard(nBoardValues); // This displays the checkerboard
            nCount = countPieces(nBoardValues); // This displays the remaining pieces left
            
            // This will execute if the first player has 0 pieces
            if(nCount == 1)
            {
                cWinner = cPlayer1;
                displayCongrats(cWinner);
                nStopper = 0;
                nStop = 1;
                nStop2 = 0;
                nScore = nP1Score;
            }
            
            // This for loop will only stop if the second player has succesfully moved a piece
            for(i = 0; i < nStop2; i++)
            {
                cWinner = cPlayer2;
                
                // Get the input of the piece to be moved
                printf("[PLAYER %c]'s Turn\n", cPlayer2);
                printf("Move: ");
                scanf("%d%c", &nP1Num, &cP1Char);
                
                // This will execute if the user surrenders
                if(nP1Num == 9)
                {
                    cWinner = cPlayer1;
                    displayCongrats(cWinner);
                    nStopper = 1;
                    nStop = 1;
                    nStop2 = 0;
                    nScore = nP1Score;
                }
                
                if(nStopper != 1)
                {
                    // Get the input of the landing position
                    printf("To: ");
                    scanf("%d%c", &nP2Num, &cP2Char);
                    
                    // This checks if the landing position is allowed and if the piece belongs to the user
                    nMoveValue = checkMove(nBoardValues, 3, nP1Num - 1, cP1Char - 'A', nP2Num - 1 ,cP2Char - 'A');
                    
                    switch(nMoveValue)
                    {
                        // This will execute the piece belongs to the user and the landing position is allowed
                        case 0:
                            // This function will move the piece
                            movePiece(nBoardValues, nP1Num - 1, cP1Char - 'A', nP2Num - 1 ,cP2Char - 'A');
                            nStop2 = 0;
                            // If the piece has reached the end row of the opposite side, this will be executed
                            if(nBoardValues[7][0] == 2 || nBoardValues[7][2] == 2 || nBoardValues[7][4] == 2 || nBoardValues[7][6] == 2 || nBoardValues[0][1] == 3 || nBoardValues[0][3] == 3 || nBoardValues[0][5] == 3 || nBoardValues[0][7] == 3)
                            {
                                displayCongrats(cWinner);
                                nStopper = 0;
                                nStop = 1;
                                nStop2 = 0;
                                nScore = nP2Score;
                            }
                            break;
                        // This will execute the piece does not belong to the user and the landing position is illegal
                        case 1:
                            // Thus the user will be asked to make a move again
                            printf("Please try again.\n");
                            nStop2 = 100;
                    }
                }
            }
        }
    }
    return nScore;
}

/*  This function displays the View Scores page––the scores of PLAYER A and B.
    Precondition: nScore is equal to 0
    @param nScore - the player who won the round
    @param nScoreA - the score of PLAYER A
    @param nScoreB - the score of PLAYER B
*/
void
displayScores(int nScore, int* nScoreA, int* nScoreB)
{
    int nBack;
    
    displayHeader();
    printf("\n");
    printf("%22s\n", "SCORES");
    printf("\n");
    
    // If PLAYER A wins a round, +1 is added to the score
    if(nScore == 1)
        *nScoreA += 1;
    
    // If PLAYER B wins a round, +1 is added to the score
    if(nScore == 2)
        *nScoreB += 1;

    printf("%24s%d\n", "PLAYER A: ", *nScoreA);
    printf("%24s%d\n", "PLAYER B: ", *nScoreB);
    printf("\n");
    printf("%s%s%s%s\n","----------", "----------","----------","----------");
    printf("Enter any key to go back the menu... ");
    scanf("%d", &nBack);
}

/*  This function displays the Quit page, asking the players of their certainty of quitting.
    Precondition: nQuitChoice is equal to 1
    @param nQuitChoice - the decision of the players
    @return 2 if they want to quit the game, otherwise 1
*/
int
displayQuit(int nQuitChoice)
{
    int nChoice, nBack;
    
    system("clear");
    displayHeader();
    printf("\n");
    
    printf("%35s\n","Are you sure you want to quit?");
    printf("%28s\n","[1] Yes   [2] No\n");
    printf("%s%s%s%s\n","----------", "----------","----------","----------");
    printf("Enter choice: ");
    scanf("%d", &nChoice);
    
    // If the user chooses yes, the game will be terminated
    if(nChoice == 1)
        nQuitChoice = 2;
    // If the user chooses no, it will go back to the menu
    else if(nChoice == 2)
        nQuitChoice = 1;
    // If the user enters an invalid answer, this will be shown
    else
    {
        printf("INVALID INPUT!\n");
        printf("Enter any key to go back... ");
        scanf("%d", &nBack);
    }
    
    return nQuitChoice;
}

/*  This function displays the congratulation screen of the winning player.
    Precondition: cWinner is either 'A' or 'B'
    @param cWinner - the winning player
*/
void
displayCongrats(char cWinner)
{
    int nBack;
    
    system("clear");
    displayHeader();
    printf("\n");
    printf("%23s", "WINNER\n");
    printf("%31s%c!\n", "Congratulations, PLAYER ", cWinner);
    printf("\n");
    printf("%s%s%s%s\n","----------", "----------","----------","----------");
    printf("Enter any key to go back to the menu... ");
    scanf("%d", &nBack);
}

/*  This function displays the checker board.
    @param nBoardValues - the numbers inside of the checkerboard
*/
void
displayBoard(int nBoardValues[8][8])
{
    int nRow, nColumn;
    
    printf("Enter [9] to surrender the game... \n");
    printf("%s%s%s%s\n","----------", "----------","----------","----------");
    
    printf("\n");
    printf("    +---+---+---+---+---+---+---+---+\n");
    
    // for loop to set the row and locate each piece of the checkboard
    for(nRow = 0; nRow < 8; ++nRow)
    {
        printf("  %d |", nRow + 1);
        // for loop to set the column and locate each piece of the checkboard
        for (nColumn = 0; nColumn < 8; ++nColumn)
            printf(" %c |", displayPieces(nBoardValues[nRow][nColumn])); // This function displays the symbols of the checkboard
        printf("\n");
        printf("    +---+---+---+---+---+---+---+---+");
        printf("\n");
    }
    printf("      A   B   C   D   E   F   G   H\n");
}

/*  This function displays the pieces of the checkerboard.
    Precondition: nSymbol is equal to any of the 4 numbers: 1, 2, 3, and 0
    @param nSymbol - the number to be represented by symbols
    @return '.' if empty space, 'X' if black piece, 'O' if white piece, otherwise ' '
*/
int
displayPieces(int nSymbol)
{
    switch(nSymbol)
    {
        // If the number in the array is 1, this will be the symbol shown
        case 1:
            return '.';
            break;
        // If the number in the array is 2, this will be the symbol shown
        case 2:
            return 'X';
            break;
        // If the number in the array is 3, this will be the symbol shown
        case 3:
            return 'O';
            break;
        // If the number in the array is 0, this will be the symbol shown
        default:
            return ' ';
    }
    return 0;
}

/*  This function displays the remaining pieces of the black and white pieces.
    @param nBoardValues - the numbers inside of the checkerboard to be counter and checked
    @return 1 if one of the players's pieces have all been captured, otherwise 0
*/
int
countPieces(int nBoardValues[8][8])
{
    int nRow, nColumn;
    int nCounter2 = 0;
    int nCounter3 = 0;
    int nCount = 0;
    
    // for loop to locate the row of each piece in the checkerboard
    for(nRow = 0; nRow < 8; ++nRow)
    {
        // for loop to locate the column of each piece in the checkherboard
        for (nColumn = 0; nColumn < 8; ++nColumn)
        {
            // If 'X' is found, +1 will be added to the piece count
            if(nBoardValues[nRow][nColumn] == 2)
                nCounter2++;
            // If 'O' is found, +1 will be added to the piece count
            if(nBoardValues[nRow][nColumn] == 3)
                nCounter3++;
        }
    }
    
    // If there are no 'X' or 'O' in the checkerboard, nCount will be set to 1
    if(nCounter2 == 0 || nCounter3 == 0)
        nCount = 1;

    printf("\n");
    printf("%30s%d\n", "BLACK (X) Piece Count: ", nCounter2);
    printf("%30s%d\n", "WHITE (O) Piece Count: ", nCounter3);
    printf("\n");
    
    return nCount;
}

/*  This function swaps the values inside of the array or the checkerboard, allowing the pieces to move.
    Precondition: the difference of nP1Num and nP2Num is 1 or -1, the difference of cP1Char and cP2Char is 2 or -2, and the position of the piece is landing to is equal to 1
    @param nBoardValues - the numbers inside of the checkerboard to be counter and checked
    @param nP1Num - the y position of the piece
    @param cP1Char - the x position of the piece
    @param nP2Num - the y position where the piece will land
    @param cP2Char - the x position where the piece will land
*/
void
swapPieces(int nBoardValues[8][8], int nP1Num, int cP1Char, int nP2Num, int cP2Char)
{
    int nSwap;
    
    // This formula swaps the values inside of the array
    nSwap = nBoardValues[nP1Num][cP1Char];
    nBoardValues[nP1Num][cP1Char] = nBoardValues[nP2Num][cP2Char];
    nBoardValues[nP2Num][cP2Char] = nSwap;
}

/*  This function checks if the landing place of the piece is not allowed.
    @param nBoardValues - the numbers inside of the checkerboard to be counter and checked
    @param nPlayer - the player making a move
    @param nP1Num - the y position of the piece
    @param cP1Char - the x position of the piece
    @param nP2Num - the y position where the piece will land
    @param cP2Char - the x position where the piece will land
    @return 1 if the move is illegal, otherwise 0
*/
int
checkMove(int nBoardValues[8][8], int nPlayer, int nP1Num, int cP1Char, int nP2Num, int cP2Char)
{
    int nMoveValue = 0;
    int nStopper = 0;
    
    // If the player tries to use the opponent's piece, this will be displayed
    if(nPlayer == 2)
    {
        if(nBoardValues[nP1Num][cP1Char] != 2)
        {
            printf("ILLEGAL MOVE! That's not your piece.\n");
            nMoveValue = 1;
            nStopper = 1;
        }
    }
    
    // If the player tries to use the opponent's piece, this will be displayed
    if(nPlayer == 3)
    {
        if(nBoardValues[nP1Num][cP1Char] != 3)
        {
            printf("ILLEGAL MOVE! That's not your piece.\n");
            nMoveValue = 1;
            nStopper = 1;
        }
    }
    
    // If the player tries to move to an occupied space, this will be displayed
    if(nStopper == 0)
    {
        if(nBoardValues[nP2Num][cP2Char] != 1 && nBoardValues[nP2Num][cP2Char] != 0)
        {
            printf("ILLEGAL MOVE! You can only move to an empty space.\n");
            nMoveValue = 1;
            nStopper = 1;
        }
    }
    
    // If the player tries to move vertically or horizontally, this will be displayed
    if(nStopper == 0)
    {
        if(nBoardValues[nP2Num][cP2Char] == 0 || cP1Char - cP2Char == 0)
        {
            printf("ILLEGAL MOVE! You can only move diagonally.\n");
            nMoveValue = 1;
            nStopper = 1;
        }
    }
    
    // If the player tries to move the other direction, this will be displayed
    if(nStopper == 0)
    {
        if(nPlayer == 2)
        {
            if(nP1Num >= nP2Num)
            {
                printf("ILLEGAL MOVE! You can only move down.\n");
                nMoveValue = 1;
                nStopper = 1;
            }
        }
    }
    
    // If the player tries to move the other direction, this will be displayed
    if(nStopper == 0)
    {
        if(nPlayer == 3)
        {
            if(nP1Num <= nP2Num)
            {
                printf("ILLEGAL MOVE! You can only move up.\n");
                nMoveValue = 1;
                nStopper = 1;
            }
        }
    }

    return nMoveValue;
}

/*  This function allows the pieces in the checkerboard move space and capture the opponent's piece.
    Precondition: the landing position of the piece is allowed
    @param nBoardValues - the numbers inside of the checkerboard to be counter and checked
    @param nP1Num - the y position of the piece
    @param cP1Char - the x position of the piece
    @param nP2Num - the y position where the piece will land
    @param cP2Char - the x position where the piece will land
    @return 0 if the piece was able to move in the checkerboard
*/
int
movePiece(int nBoardValues[8][8], int nP1Num, int cP1Char, int nP2Num, int cP2Char)
{
    int nMoveValue = 0;
    int nJumpRow, nJumpColumn;
    
    // This is the formula to check if the landing position is allowed
    if(nP1Num - nP2Num == 1 || nP1Num - nP2Num == -1)
    {
        if(cP1Char - cP2Char == 1 || cP1Char - cP2Char == -1)
        {
            // If it is, this will be executed
            swapPieces(nBoardValues, nP1Num, cP1Char, nP2Num, cP2Char);
            nMoveValue = 0;
        }
    }
    
    // This is the formula to check if the landing position is allowed
    if(nP1Num - nP2Num == 2 || nP1Num - nP2Num == -2)
    {
        if(cP1Char - cP2Char == 2 || cP1Char - cP2Char == -2)
        {
            // This is the formula to check if the landing position is a capture move
            if(nP1Num < nP2Num)
                nJumpRow = nP1Num + 1;
            else
                nJumpRow = nP1Num - 1;
            
            if(cP1Char < cP2Char)
                nJumpColumn = cP1Char + 1;
            else
                nJumpColumn = cP1Char - 1;
 
            nBoardValues[nJumpRow][nJumpColumn] = 1;
            
            // If it is, this will be executed
            swapPieces(nBoardValues, nP1Num, cP1Char, nP2Num, cP2Char);
            
            nMoveValue = 0;
        }
    }
    
    return nMoveValue;
}
