//Comp2521 assignment 1: information retreival
//Written by Sean Morota Chu (z5259673), started 19/03/2020 - completed xx/03/2020
//#INCLUDES
#include"invertedIndex.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
//HELPER FUNCTIONS
static InvertedIndexBST newInode(char *word);
static FileList newFnode (char *filename);
static InvertedIndexBST insert(InvertedIndexBST t, char *word);
static int alphacmp(char *w1, char *w2);


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
InvertedIndexBST generateInvertedIndex(char *collectionFilename){
    FILE f = fopen(collectionFilename, "r");
    if (!f) return NULL; //fopen fails
    
}
//Traverse the tree via infix order and print
void printInvertedIndex(InvertedIndexBST tree) {

    return;
}
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {
    return;
}
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {
    return;
}

//HELPER FUNCTIONS

//makes a new IIBST node
static InvertedIndexBST newInode(char *word) {
    InvertedIndexBST b = malloc (sizeof(struct InvertedIndexNode));
    b->word = word;
    b->fileList = NULL;
    b->left = NULL;
    b->right = NULL;
    return b;
}

//makes a new FL node
static FileList newFnode (char *filename) {
    FileList n = malloc (sizeof(struct( FileListNode)));
    n->filename = filename;
    n->tf = 0;
    n->next = NULL;
    return n;
}

static InvertedIndexBST insert(InvertedIndexBST t, char *word) {
    if (t == NULL) return newInode(word); //empty :)
    //we don't want doubles of the word in the IISBST
    else if (strcmp(t->word,word){ //the words aren't equal
        if (alphacmp(t->word,word) > 0) insert(t->left,word);
        else if (alphacmp(t->word,word) < 0) insert (t->right,word);
    } else {//word is already in use
        return t;
    }
}

//Compares two words alphabetically, returns -1 if w1 is before w2, 0 if equal, 1 if w1 is after w2
static int alphacmp(char *w1, char*w2) {
    if (!strcmp(w1,w2)) return 0;
    int w1after = -1;
    for (int i = 0; i < strlen(w1); i++) {
        if (w1[i] > w2[i]){
            w1after = 1;
            break;
        }
        if (i == strlen(w2) - 1) {
            w1after = 1;
            break;
        } 
    }
    return w1after;

}