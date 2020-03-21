#include"invertedIndex.h"
struct TfIdfRep {
    TfIdfList head;
    TfIdfList curr;
};
typedef struct TfIdfRep *tflist;
//Creates an empty tfidf list (not static since i use it in the retreive function)
tflist newTL();
//Creates and inserts a tfidf list node into the tfidf list
void insertTnode(tflist tlist,char *filename, double tfidfsum);
//Returns a tfidf list for a given word.
TfIdfList getTfIdf(FileList search_list,int D);
