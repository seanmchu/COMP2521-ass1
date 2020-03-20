#include"helper.h"
#include"invertedIndex.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
//Compares two words alphabetically, returns -1 if w1 is before w2, 0 if equal, 1 if w1 is after w2
int alphacmp(char *w1, char*w2) {
    if (!strcmp(w1,w2)){
        return 0;
    } 
    int w1after = -1;
    for (int i = 0; i < strlen(w1); i++) {
        if (w1[i] > w2[i]){
            w1after = 1;
            break;
        } else if (w1[i] < w2[i]) {
            break;
        }
    }
    return w1after;
}

//Calculates and returns the Term frequency of a given file
double getTf(char *filename, char *word) {
    double tf = 0;
    double words_found = 0;
    double total_words = 0;
    FILE *fp = fopen(filename,"r");
    if (fp == NULL) return 0;
    char str[100];
    char *result;
    while(fscanf(fp,"%s",str) != EOF) {
        result = normaliseWord(str);
        if (!strcmp(word,result)) {
            words_found++;
        }
        total_words++;
    }
    if (total_words != 0) tf = words_found/total_words;
    return tf;
}
