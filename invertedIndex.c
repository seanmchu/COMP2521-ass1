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
static InvertedIndexBST generateEmptyBST(flhead f);
//Populates a BST's fileList Nodes with the FileList nodes.
static void populateBST(InvertedIndexBST t, flhead f);
//Prints the BST into the named file pointer
//This is a separate function from PrintInvertedIndex so I don't 
//      have to reopen the file pointer each time I recurse
static void InvertedIndexPrint(InvertedIndexBST tree,FILE *fp);

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

//Generate an invertedIndex BST, alphabetically ordered by word. [DONE]
InvertedIndexBST generateInvertedIndex(char *collectionFilename){
    //Generate list of files in collection file
    flhead f = gen_read_fl(collectionFilename);
    //make a BST out of it
    InvertedIndexBST t = generateEmptyBST(f);
    //Populate the BST with filelists
    populateBST(t,f);
    //Return generated tree
    return t;
}

//Traverse the tree via infix order and print tree word and filenames [DONE]
void printInvertedIndex(InvertedIndexBST tree) {
    if (tree == NULL) perror("empty tree provided");
    FILE *fp = fopen("invertedIndex.txt","w");
    if (!fp) perror("fopen failed");
    InvertedIndexPrint(tree,fp);
    fclose(fp);
    
}
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {
    return NULL;
}
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {
    return NULL;
}

//Helper functions

static InvertedIndexBST generateEmptyBST(flhead f) {
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
            str = malloc(sizeof(char) * MAXWORDLENGTH);
        }
        f->curr = f->curr->next;
    }
    f->curr = f->head;
    return t;
}

//Populates a BST's fileList Nodes with the FileList nodes.
static void populateBST(InvertedIndexBST t, flhead f) {
    //Traverse infix order
    if (t == NULL) return;
    //if (t->left != NULL) printf("Current node %s, moving left to %s\n",t->word,t->left->word);
    populateBST(t->left,f);
    flhead ff = newFL();
    f->curr = f->head;
    double tf = 0;
    //Look through the entire filelist and generate tf for each, then add to node if tf > 0
    while(f->curr != NULL) {
        tf = getTf(f->curr->filename,t->word);
        if (tf != 0) {
            //printf("Inserting file %s for node %s with %f frequency\n",f->curr->filename,t->word,tf);
            insertFnode(ff,f->curr->filename,tf);
        }
        f->curr = f->curr->next;
    }
    t->fileList = ff->head;
    
    /*if (t->right != NULL) printf("Current node :%s, moving right to %s\n",t->word,t->right->word);
    else printf("Reached end of right at %s\n",t->word);
    */
    populateBST(t->right,f);
}

static void InvertedIndexPrint(InvertedIndexBST tree,FILE *fp) {
    if (tree == NULL) return;
    InvertedIndexPrint(tree->left,fp);
    fprintf(fp,"%s ",tree->word);
    FileList fl = tree->fileList;
    while (fl != NULL) {
        fprintf(fp,"%s ",fl->filename);
        fl = fl->next;
    }
    fprintf(fp,"\n");
    InvertedIndexPrint(tree->right,fp);
}