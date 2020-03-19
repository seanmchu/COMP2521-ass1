//Need to #include in the header file since I need access to the types
#include"invertedIndex.h"
struct FileListHead {
    FileList head;
    FileList curr;
};
typedef struct FileListHead *flhead;

//makes a new FL node
FileList newFnode (char *filename);
//Insert a new Fnode at end of FL, returns head of list (assuming head input)
void insertFnode(flhead n, char*filename);
