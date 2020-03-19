//Need to #include in the header file since I need access to the types
#include"invertedIndex.h"
//Creates a new IIBST node
InvertedIndexBST newInode(char *word);
//Creates and inserts a new IIBST node sorted alphabetically
InvertedIndexBST insertInode(InvertedIndexBST t, char *word);
