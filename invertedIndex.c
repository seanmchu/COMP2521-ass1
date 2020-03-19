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

//#DEFINES
#define MAXWORDLENGTH 30


//HELPER FUNCTIONS
static InvertedIndexBST generateEmptyBST(FileList fl);
static void populateBST(InvertedIndexBST t, FileList fl);
static double getTf(char *filename, char *word);
//Gameplan (Part 1):
//Check through all files, normalising all words in the read process.
//Form IIBST
//Then print via infix order after each possible word

int main (int argv, char **argc) {
    for (int i = 1; i < argv; i++) {
        printf("%s\n", normaliseWord(argc[i]));
    }
    InvertedIndexBST t = generateInvertedIndex("collection.txt");
    printInvertedIndex(t);
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
    FILE *collection = fopen(collectionFilename,"r");
    //now, for each file here, we add it to a FileList
    FileList fl = NULL;
    char filename[MAXWORDLENGTH];
    while (fscanf(collection,"%s",filename)) {
        insertFnode(fl,filename);
    }
    //Now, we have a list of files we need to read to generate the IIBST
    //for each word, we need an IIBST node and a FileList.
    //We first generate the IIBST nodes, then for each node, we generate the corresponding FL.
    InvertedIndexBST t = generateEmptyBST(fl);
    populateBST(t,fl);
    return t;
}
//Traverse the tree via infix order and print
void printInvertedIndex(InvertedIndexBST tree) {
    FILE *fp = fopen("invertedIndex.txt","a");
    if (tree == NULL) {
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
}
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {
    return NULL;
}
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {
    return NULL;
}

//HELPER FUNCTIONS

//Generates an IIBST with Filelist values set to NULL
InvertedIndexBST generateEmptyBST(FileList fl) {
    InvertedIndexBST t = NULL;
    char *str = malloc (sizeof(char) * MAXWORDLENGTH);
    for (FILE *fp; fp = fopen(fl->filename,"r"); fl = fl->next) { //for each file
        while (fscanf(fp,"%s",str)) { //for every word (str)
            strcpy(str,normaliseWord(str));
            t = insertInode(t,str); //won't make doubles, always returns root of tree
        }
    }
    free(str);
    return t;
}


//Populates a BST's fileList Nodes with the FileList nodes.
void populateBST(InvertedIndexBST t, FileList fl) {
    //We will traverse in infix order by default.
    if (t == NULL) return;
    populateBST(t->left,fl);
    FileList ff = NULL;
    while (fl) { // generate the fl for the given word
        if (getTf(fl->filename,t->word)) { //if the term frequency is not 0
            insertFnode(ff,fl->filename);
        }
        fl = fl->next;
    }
    t->fileList = ff;
    populateBST(t->right,fl);
}

//Calculates and returns the Term frequency of a given file
static double getTf(char *filename, char *word) {
    FILE *fp = fopen(filename,"r");
    double match_count = 0;
    double word_count = 0;
    double tf = 0;
    char *read = malloc(sizeof(char) * MAXWORDLENGTH);
    while (fscanf(fp,"%s",read)) {
        strcpy(read,normaliseWord(read));
        if (!strcmp(read,word)) {
            match_count++;
        }
        word_count++;
    }
    free(read);
    if (word_count != 0) tf = match_count / word_count;
    return tf;
}