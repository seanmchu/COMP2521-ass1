//Need to #include in the header file since I need access to the types
#include"invertedIndex.h"
//makes a new FL node
FileList newFnode (char *filename);
//Insert a new Fnode at end of FL, returns head of list (assuming head input)
FileList insertFnode(FileList n, char*filename);
