/*
 * lab3DivingCompetitionSimulation.c
 * Diver competition lab. Generate scores for a random number of divers for 
 * 5 rounds and announce winners.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    int divers, i, j, k;
    const float scores[21] = {
        0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 
        5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10 };
    float judgeScores[7];
    float roundScore;

    /*
     * Chose and announce random number of divers
     */
    srand(time(NULL)); //to give a different seed
    divers = (rand() % 6) + 5;
    printf("There are %i divers in the competition.\n", divers);
    
    //initialize bestScores array
    float bestScores[divers+1]; //using indices [1,divers]
    for(i=1; i<divers; i++) //diver 1 is at index 1
        bestScores[i] = 0;



    /*
	 * Run competition
	 */
    //loop for each round
    for(i=1; i<=5; i++){ //i is the round number [1,rounds]
        printf("Round %i:\n", i);
        //loop for each diver
        for(j=1; j<=divers; j++){ //j is the diver number [1,divers]
            /*
             * Generate judge scores
             */
            for(k=0; k<7; k++){
                judgeScores[k] = scores[rand() % 21];
            }

            /*
             * Calculate diver score:
             */

            //Selection sort:
            int iMin, p;
            float tmp;
            for(k=0; k<7-1; k++){
                iMin = k;
                for(p=k+1; p<7; p++){
                    if(judgeScores[p] < judgeScores[iMin])
                        iMin = p;
                }
                tmp = judgeScores[k];
                judgeScores[k] = judgeScores[iMin];
                judgeScores[iMin] = tmp;
            }
            
            //add indices 2-4 (cancel highest and lowest scores)
            float roundScore = 0;
            for(k=2; k<=4; k++){
                roundScore += judgeScores[k];
            }

            //if diver's personal best, add to best score
            if(roundScore > bestScores[j])
                bestScores[j] = roundScore;
            
            /*
             * Display results of the round:
             */
            printf("Diver %i made her dive. Scores from judges are: ", j);
            for(k=0; k<7; k++){
                if(k==6)
                    printf("%g. ", judgeScores[k]);
                else
                    printf("%g, ", judgeScores[k]);
            }
            printf("Diver %i score is: %g\n", i, roundScore);
        }
    }

    /*
     * Print best scores
     */
    printf("\nBest Scores:\n");
    for(i=1; i<=divers; i++){
        if(i != divers)
            printf("%g, ", bestScores[i]);
        else
            printf("%g.\n", bestScores[i]);
    }

    /*
     * Find top 3 divers
     */
    int medalists[3] = {-5, -5, -5};
    int iMax;
    for(i=0; i<3; i++){
        iMax = j;
        for(j=1; j<=divers; j++){
           if(bestScores[j] > bestScores[iMax]){
                if(j != medalists[0] && j != medalists[1] 
                                     && j != medalists[2]){
                    iMax = j;
                }
            }
        }
        medalists[i] = iMax;
    }

    /*
     * Announce results
     */    
    printf("\nMedalists:\n");
    printf("Gold:   Diver %i with %g\n", medalists[0], bestScores[medalists[0]]);
    printf("Silver: Diver %i with %g\n", medalists[1], bestScores[medalists[1]]);
    printf("Bronze: Diver %i with %g\n", medalists[2], bestScores[medalists[2]]);
  

    return 0;
}
