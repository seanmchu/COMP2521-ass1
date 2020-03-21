//Need to #include in the header file since I need access to the types
#include"invertedIndex.h"
struct FileListRep {
    FileList head;
    FileList curr;
};
typedef struct FileListRep *flhead;

//Creates an empty file list
flhead newFL();
//Creates and inserts an Fnode into a file list
void insertFnode(flhead n, char*filename,double tf);
//Generates a file list from the collection file
flhead gen_read_fl(char *collectionFilename);
