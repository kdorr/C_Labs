/*
 * Lab 6: program to count the words.
 * Author: Kimberly Orr
 * Date: 4/26/18
 * Turned in: 5/3/18 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Struct for node in a linked list: contains a word and its count
struct wc {
    struct wc *next;  //Point to next struct wc in a linked list
    char *wrd;        //Word being counted
    int count;        //Count for that word
};

/*
 * Creates a new node at the beginning of the list.
 */
struct wc * makeNewNode(struct wc *head, char *str){
    struct wc *newnode;
    char *newword = malloc(strlen(str) + 1);
    strcpy(newword, str);
    newnode = malloc(sizeof(struct wc));

    if(newnode != NULL){
        newnode->wrd = newword;
        newnode->count = 1;
        newnode->next = head;
    }
    return newnode;
}

/*
 * Returns a pointer to a string that does not contain punctuation.
 */
char * strip_punc(char str[]){
    int i, j=0;
    char * newStr = (char *) calloc (sizeof(char), strlen(str)+1);
    for(i=0; str[i]!='\0'; i++){
        if(isalpha(str[i])){
            *(newStr+j) = tolower(str[i]);
            j++;
        }
    }
    return newStr;
}

/*
 * Searches list for the given word. Increments count of the word if found and
 * adds a new node to the list if the word is not found.
 */
struct wc * searchList(struct wc *head, char str[]){
    _Bool found = 0;
    struct wc *p;
    p = head;
    
    char *strPtr = strip_punc(str); //strip punctuation

    //search for word in list
    while(p != NULL && found != 1){
        if(strcmp(p->wrd, strPtr) == 0){
            p->count++;
            found = 1;
        }
        p=p->next;
    }
    //create new node if word isn't found
    if(found != 1){
        head = makeNewNode(head, strPtr);
    }
    
    free(strPtr);

    return head;
}

/*
 * Main
 */
int main (void){
    FILE *fp;
    char buff[255];
    int i;
    struct wc *head, *p;
    head = NULL;

    //Read file
    fp = fopen("Alice_Ch1.txt", "r");
    while(fscanf(fp, "%s", buff)==1){
        head = searchList(head, buff);
    }
    fclose(fp);

    //Print list
    for(p = head; p != NULL; p = p->next){
        printf("%s: %i\n", p->wrd, p->count);
    }

    //Free space
    for(p = head; p != NULL; p = head){
        head = head->next;
        free(p);
    }

    return 0;
}
