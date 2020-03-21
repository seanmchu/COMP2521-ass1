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
#include<math.h>
//HELPERS
//Generates a BST without filelists.
static InvertedIndexBST generateEmptyBST(flhead f);
//Populates a BST's fileList Nodes with the FileList nodes.
static void populateBST(InvertedIndexBST t, flhead f);
//Prints the BST into the named file pointer
//This is a separate function from PrintInvertedIndex so I don't 
//      have to reopen the file pointer each time I recurse
static void InvertedIndexPrint(InvertedIndexBST tree,FILE *fp);
//Returns the fileList(head node) of a given word from the BST
static FileList getList (InvertedIndexBST t,char *word);

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

//Just calculate the tfidf of a word, add to list and return it [DONE]
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {
    //first, retreive the fileList from the IIBST
    FileList search_list = getList(tree,searchWord);
    if (search_list == NULL) return NULL;
    return getTfIdf(search_list,D);
}

TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {
    FileList search_list = NULL;
    tflist return_list = newTL();
    for (int i = 0; searchWords[i] != NULL; i++) {
        search_list = getList(tree,searchWords[i]);
        int list_size = listSize(search_list);
        double idf = getIDF(D,list_size);
        for (FileList curr = search_list;curr != NULL;curr = curr->next)
            insertTnode(return_list,curr->filename,idf * curr->tf);
    }
    return return_list->head;
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
            str = normaliseWord(str);
            t = insertInode(t,str);
            str = malloc(sizeof(char) * MAXWORDLENGTH);
        }
        fclose(fp);
        f->curr = f->curr->next;
    }
    f->curr = f->head;
    return t;
}

//Populates a BST's fileList Nodes with the FileList nodes.
static void populateBST(InvertedIndexBST t, flhead f) {
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

static FileList getList (InvertedIndexBST t,char *word) {
    //traverse infix and return filelist of the given word.
    if (t == NULL) return NULL;
    if (!strcmp(t->word,word)) return t->fileList;
    FileList left = getList(t->left,word);
    FileList right = getList(t->right,word);
    if(left != NULL) return left;
    if (right != NULL) return right;
    else return NULL;
}