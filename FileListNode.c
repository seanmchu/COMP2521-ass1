#include"FileListNode.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>


FileList newFnode (char *filename) {
    FileList n = malloc (sizeof(struct FileListNode));
    n->filename = filename;
    n->tf = 0;
    n->next = NULL;
    return n;
}
