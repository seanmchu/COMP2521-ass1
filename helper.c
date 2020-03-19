#include"helper.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
//Compares two words alphabetically, returns -1 if w1 is before w2, 0 if equal, 1 if w1 is after w2
int alphacmp(char *w1, char*w2) {
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

