/*
 * Lab 5
 * Kimberly Orr
 * Date: 4/19/18
 * Checked off: 4/26/18 
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 * Shifts the given char (decipher passes -1*shift value)
 */
char change (char ltr, int shift){
    unsigned char new = ltr + shift;
    if(new > 'z'){
        new = new - 26;
    }
    else if(new < 'a'){
        new = new + 26;
    }
    return new;
}

/*
 * main
 */
int main (int argc, char * argv[]){
    char* action;
    int shift;
    char string[81];
    int i;

    //Check command line args
    if (argc != 3){
        printf("Incorrect number of arguments.\n");
        printf("Correct usage: l5 [action] [shift_value]\n");
        return 1;
    }
    else if(strcmp(argv[1],"c") != 0 && strcmp(argv[1],"d") != 0){
        printf("Incorrect arguments.\n");
        printf("The first argument must be 'c'ipher or 'd'ecipher.\n");
        printf("Correct usage: l5 [action] [shift_value]\n");
        return 1;
    }
    else if(atoi(argv[2]) < -10 || atoi(argv[2]) > 10){
        printf("Incorrect argument.\n");
        printf("The second argument must be an integer between -10 and 10.\n");
        printf("Correct usage: l5 [action] [shift_value]\n");
        return 1;
    }
    else{
        action = argv[1];
        shift = atoi(argv[2]);
    }

    //get string from user
    printf("Please enter a string to be (de)ciphered (max 80 characters)\n");
    fgets(string, 81, stdin);
    
    //string to lowercase
    for(i=0; string[i]; i++){
        string[i] = tolower(string[i]);
    }

    //cipher or decipher
    for(i=0; string[i]; i++){
        if(string[i] < 'a' || string[i] > 'z'){
            string[i] = string[i];
        }
        else{
            if(strcmp(action,"c") == 0){                //cipher
                string[i] = change(string[i], shift);
            }
            else if(strcmp(action,"d") == 0){           //decipher
                string[i] = change(string[i], -1*shift);
            }
            else{
                printf("There was an error.\n");
                return 1;
            }
        }
    }

    //print (de)ciphered string
    printf("%s\n", string);

    return 0;
}
