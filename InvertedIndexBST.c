#include"InvertedIndexBST.h"
#include"helper.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
//Creates and inserts a new IIBST node into the tree.
InvertedIndexBST insertInode(InvertedIndexBST t, char *word) {
    if (t == NULL) return newInode(word); //empty :)
    if (!word) return t; //Null word
    word = normaliseWord(word);
    if (strcmp(t->word,word)){ //the words aren't equal
        if (alphacmp(t->word,word) > 0) t->left = insertInode(t->left,word);
        else if (alphacmp(t->word,word) < 0) t->right = insertInode (t->right,word);
    }
    //return the root
    return t;
}


//makes a new IIBST node
InvertedIndexBST newInode(char *word) {
    InvertedIndexBST b = malloc (sizeof(struct InvertedIndexNode));
    char *str = malloc(sizeof(char) * 100);
    strcpy(str,word);
    str = normaliseWord(str);
    b->word = str;
    b->fileList = NULL;
    b->left = NULL;
    b->right = NULL;
    return b;
}