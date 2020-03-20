#include"InvertedIndexBST.h"
#include"helper.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
//compares two words alphabetically, returns -1 if w1 is before w2, returns 1 if w2 is before, 0 if they are the same


//Creates and inserts a new IIBST node into the tree.
InvertedIndexBST insertInode(InvertedIndexBST t, char *word) {
    if (t == NULL) return newInode(word); //empty :)
    //we don't want doubles of the word in the IISBST
    if (!word) return t;
    else if (strcmp(t->word,word)){ //the words aren't equal
        if (alphacmp(t->word,word) > 0) t->left = insertInode(t->left,word);
        else if (alphacmp(t->word,word) < 0) t->right = insertInode (t->right,word);
    }
    //return the root
    return t;
}


//makes a new IIBST node
InvertedIndexBST newInode(char *word) {
    InvertedIndexBST b = malloc (sizeof(struct InvertedIndexNode));
    char str[100];
    strcpy(str,word);
    char *str1 = malloc(sizeof(char) * 100);
    str1 = normaliseWord(str);
    printf("inside func1 %s\n",str1);
    printf("inside func2 %s\n",str1);
    b->word = str1;
    b->fileList = NULL;
    b->left = NULL;
    b->right = NULL;
    return b;
}