//Need to #include in the header file since I need access to the types
#include"invertedIndex.h"
struct FileListRep {
    FileList head;
    FileList curr;
};
typedef struct FileListRep *flhead;

//makes a new file list node
FileList newFnode (char *filename);
//Creates an empty file list
flhead newFL();
//Insert a new Fnode at end of FL, returns head of list (assuming head input)
void insertFnode(flhead n, char*filename,double tf);
//Generates a file list from the collection file
flhead gen_read_fl(char *collectionFilename);
