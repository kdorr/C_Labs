/*
 * l4.c
 * Program to simulate Memory Game.
 * Author: Kimberly Orr
 * Date: 4/12/18
 * Checked off: 4/19/18 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[4][5];
int cardVals[4][5];
/*int cardVals[4][5] = {{0, 0, 1, 1, 2}, {2, 3, 3, 4, 4}, {5, 5, 6, 6, 7},
                      {7, 8, 8, 9, 9}};  //for debugging */


/*
 * Randomly populates cardVals with 2 sets of cards (numbered 0-9)
 */ 
void createBoard(){
    srand(time(NULL));
    int i, j, r;
    int counters[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    _Bool isPlaced = 0;

    for(i=0; i<4; i++){
        for(j=0; j<5; j++){
            isPlaced = 0;
            while(isPlaced == 0){
                r = rand() % 10;
                if(counters[r] < 2){
                    cardVals[i][j] = r;
                    counters[r]++;
                    isPlaced = 1;
                }
            }
        }
    }
}

/*
 * Prints the board (formatted correctly)
 */
void printBoard(){
    int i, j;
    printf("  | 0 1 2 3 4\n");
    printf("-------------\n");
    for(i=0; i<4; i++){
        printf("%i | ", i);
        for(j=0; j<5; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

/*
 * Checks user input. Checks for 0<=r<=4, 0<=c<=3, and not previously chosen.
 */
_Bool isValidInput(r1, c1, r2, c2){
    _Bool isValid = 0;
    if(r1 >= 0 && r1 <= 3 && r2 >= 0 && r2 <= 3){    //check rows in bounds
        if(c1 >= 0 && c1 <= 4 && c2 >= 0 && c2 <= 4){//check cols in bounds
            if(board[r1][c1] == 'x' && board[r2][c2] == 'x'){
                isValid = 1;
            }
        }
    }
    return isValid; 
}

/*
 * Checks to see if the game is ended
 */
_Bool isGameEnded(){
    int i, j;
    for(i=0; i<4; i++){
        for(j=0; j<5; j++){
            if(board[i][j] == 'x'){
                return 0;
            }
        }
    }
    return 1;
}

/*
 * Reveals the two chosen cards
 */
void showCards(int r1, int c1, int r2, int c2){
    board[r1][c1] = cardVals[r1][c1] + '0';
    board[r2][c2] = cardVals[r2][c2] + '0';
}

/*
 * Changes unmatched cards back to 'x's
 */
void changeBack(int r1, int c1, int r2, int c2){
    board[r1][c1] = 'x';
    board[r2][c2] = 'x';
}

/*
 * Checks if the chosen cards are matches
 */
_Bool isMatch(int r1, int c1, int r2, int c2){ //define args
    if(cardVals[r1][c1] == cardVals[r2][c2]){
        board[r1][c1] = ' ';
        board[r2][c2] = ' ';
        return 1;
    }
    else{
        return 0;
    }
}

/*
 * Main
 */
int main(void){
    int playerTurn = 0; //p1 = 0, p2 = 1
    int i, j, r1, c1, r2, c2;
    int points[2] = {0,0};
    _Bool stillTurn = 0;
    char ans;

    srand(time(NULL));
    
    // Prepare board
    for(i=0; i<4; i++)
        for(j=0; j<5; j++)
            board[i][j] = 'x';
    // Prepare cardVals (shuffled board)
    createBoard();

 /*
  * Play game
  */
    while(!isGameEnded()){
        do{
            printBoard();

            //choose card
            printf("Player %i, choose 2 cards:\n", playerTurn+1);
            printf("Card 1 (r c):\n");
            scanf("%i %i", &r1, &c1);
            printf("Card 2 (r c):\n");
            scanf("%i %i", &r2, &c2);
            
            //check input and play game if valid
            if(isValidInput(r1, c1, r2, c2) == 0){
                printf("You chose an invalid card. You forfeit your turn.\n");
                stillTurn = 0;
                playerTurn = ((playerTurn+1) % 2); //playerTurn is 0 and 1
            }
            else{ //input is valid

                //show cards (change board & print)
                showCards(r1, c1, r2, c2);
                printBoard();

                //player chose a match
                if(isMatch(r1, c1, r2, c2)){      //cards match
                    //add point to current player
                    points[playerTurn]++;
                    printf("Match!\n");

                    //display points
                    printf("Player 1: %i points\n", points[0]);
                    printf("Player 2: %i points\n\n", points[1]);
                    stillTurn = 1;
                }
                else{                             //cards don't match
                    //change board back to xs
                    changeBack(r1, c1, r2, c2);

                    //wait for keystroke and print many newlines
                    printf("Next player ready? (y/n)\n");
                    scanf(" %c", &ans);

                    // handle the fact that I gave an option nicely:
                    if(ans == 'y' || ans == 'Y'){
                        for(i=0; i<40; i++)
                            printf("\n");
                    }
                    else{
                        printf("Too bad. It's the next player's turn.");
                        for(i=0; i<40; i++)
                            printf("\n");
                    }
                    
                    //change turns
                    stillTurn = 0;
                    playerTurn = ((playerTurn+1) % 2); //playerTurn is 0 and 1
                }
            }
        } while(stillTurn && !isGameEnded());
    }

 /*
  * Game ended. Declare winner.
  */
    if(points[0] > points[1]){
        printf("Game over! Player 1 wins!\n");
    }
    else if(points[0] == points[1]){
        printf("Game over! It's a tie!\n");
    }
    else if(points[0] < points[1]){
        printf("Game over! Player 2 wins!\n");
    }
    else{
        printf("Game over! Something went wrong with the scoring.\n");
    }

    return 0;
}
