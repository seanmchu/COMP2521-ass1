//Comp2521 assignment 1: information retreival
//Written by Sean Morota Chu (z5259673), started 19/03/2020 - completed xx/03/2020
//#INCLUDES
#include"invertedIndex.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
//Gameplan (Part 1):
//Check through all files, normalising all words in the read process.
//Form IIBST
//Then print via infix order after each possible word

int main (int argv, char **argc) {
    for (int i = 1; i < argv; i++) {
        printf("%s\n", normaliseWord(argc[i]));
    }
    return 0;
}

char *normaliseWord(char *str){
    //remove leading whitespace (move pointer forward)
    while (*str == ' ') str++;
    //remove trailing whitespace (replace with null terminators >:) )
    int i = strlen(str) - 1;
    while (str[i] == ' ' && i >= 0) {
        str[i] = '\0';
        i--;
    }
    //make everything lowercase
    for (int i = 0; i < strlen(str); i++) str[i] = tolower(str[i]);
    //Replace punctuation mark at the end of the word with a null byte
    char *last = strchr(str,'\0');
    last--;
    if (*last == '?'|| *last == '.' || *last == ',' || *last == ';') *last = '\0';
    return str;
}

//A tree ordered alphabetically lol
//First- open the file of files
//Next- for every file in the file of files, insert a new node for every word (will be fixed for doubles)
//Then -scan through to generate fl nodes and their tf's, then insert into the fl alphabetically. (for each IIBST node)
//Then return.
//Do as much as possible recursively as to avoid time complexity.
InvertedIndexBST generateInvertedIndex(char *collectionFilename){
    FILE *f = fopen(collectionFilename, "r");
    if (!f) return NULL; //fopen fails
    return NULL;

}
//Traverse the tree via infix order and print
void printInvertedIndex(InvertedIndexBST tree) {

    return;
}
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {
    return NULL;
}
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {
    return NULL;
}
