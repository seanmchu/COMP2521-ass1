#include"helper.h"
#include"invertedIndex.h"
#include<math.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

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
    fclose(fp);
    return tf;
}

int listSize(FileList f) {
    int size = 0;
    for (FileList curr = f; curr != NULL; curr = curr->next) size++;
    return size;
}

double getIDF(int total_documents,int relevant_documents) { 
    return log10((double)total_documents/relevant_documents);
}
