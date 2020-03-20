//Comp2521 assignment 1: information retreival
//Written by Sean Morota Chu (z5259673), started 19/03/2020 - completed xx/03/2020
//#INCLUDES
#include"invertedIndex.h"
#include"InvertedIndexBST.h"
#include"FileListNode.h"
#include"helper.h"
#include"Tfidf.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
//HELPERS
//Generates a BST without filelists.
InvertedIndexBST generateEmptyBST(flhead f);
//Populates a BST's fileList Nodes with the FileList nodes.
void populateBST(InvertedIndexBST t, flhead f);

//Gameplan (Part 1):
//Check through all files, normalising all words in the read process.
//Form IIBST
//Then print via infix order after each possible word

//Done and works, DON'T TOUCH
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
    for (int j = 0; j < strlen(str); j++) str[j] = tolower(str[j]);
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
    //Generate list of files in collection file
    printf("Generating fileList\n");
    flhead f = gen_read_fl(collectionFilename);
    //make a BST out of it
    printf("Generating BST\n");
    InvertedIndexBST t = generateEmptyBST(f);
    printf("Populating BST\n");
    populateBST(t,f);
    return t;
}
//Traverse the tree via infix order and print
void printInvertedIndex(InvertedIndexBST tree) {
    /*FILE *fp = fopen("invertedIndex.txt","a");
    if (tree == NULL) {
        perror("tree is empty");
        return;
    }
    printInvertedIndex(tree->left);
    fprintf(fp,"%s ",tree->word);
    FileList fl = tree->fileList;
    while (fl != NULL) {
        fprintf(fp,"%s ",fl->filename);
        fl = fl->next;
    }
    printInvertedIndex(tree->right);
    */
}
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {
    return NULL;
}
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {
    return NULL;
}

//Helper functions

InvertedIndexBST generateEmptyBST(flhead f) {
    f->curr = f->head;
    InvertedIndexBST t = NULL;
    //Open all files in filelist
    while (f->curr != NULL) {
        FILE *fp = fopen(f->curr->filename,"r");
        char *str= malloc(sizeof(char) * MAXWORDLENGTH);
        //Try to insert for every word in filelist (note, will not double up on nodes with each word)
        //If a word is already in the tree, nothing will happen
        while(fscanf(fp,"%s",str) != EOF) {
            t = insertInode(t,str);
            printf("%s has become %s\n",str,t->word);
            str = malloc(sizeof(char) * MAXWORDLENGTH);
        }
        f->curr = f->curr->next;
    }
    f->curr = f->head;
    if (t == NULL) {
        printf("Empty tree\n");
    }
    else printf("%s\n",t->word);
    return t;
}

//Populates a BST's fileList Nodes with the FileList nodes.
void populateBST(InvertedIndexBST t, flhead f) {
    //Traverse infix order
    if (t == NULL) return;
    populateBST(t->left,f);
    flhead ff = newFL();
    f->curr = f->head;
    double tf = 0;
    while(f->curr != NULL) {
        tf = getTf(f->curr->filename,t->word);
        if (tf != 0) {
            insertFnode(ff,f->curr->filename,tf);
        }
        f->curr = f->curr->next;
    }
    t->fileList = ff->head;
    populateBST(t->right,f);
}
