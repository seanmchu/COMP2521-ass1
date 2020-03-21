#include"invertedIndex.h"
//Compares two words alphabetically, returns 1 if w1 is after, -1 if w2 is after,
//returns 0 if they are the same word
int alphacmp(char *w1, char *w2);
//Returns the tf of a given file for a given word
double getTf(char *filename, char *word);
//Returns the size of the list
int listSize(FileList f);
//Returns idf of a given file for a given word
double getIDF(int total_documents,int relevant_documents);

