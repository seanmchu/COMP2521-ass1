#include"InvertedIndexBST.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
//compares two words alphabetically, returns -1 if w1 is before w2, returns 1 if w2 is before, 0 if they are the same
static int alphacmp(char *w1, char *w2);

//Creates and inserts a new IIBST node into the tree.
InvertedIndexBST insert(InvertedIndexBST t, char *word) {
    if (t == NULL) return newInode(word); //empty :)
    //we don't want doubles of the word in the IISBST
    else if (strcmp(t->word,word)){ //the words aren't equal
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

//makes a new IIBST node
InvertedIndexBST newInode(char *word) {
    InvertedIndexBST b = malloc (sizeof(struct InvertedIndexNode));
    b->word = word;
    b->fileList = NULL;
    b->left = NULL;
    b->right = NULL;
    return b;
}

