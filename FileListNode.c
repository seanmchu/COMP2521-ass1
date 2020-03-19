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

FileList insertFnode(FileList n,char *filename) {
    //if FL is empty, make new head
    if (!n) {
        FileList nn = newFnode(filename);
        return nn;
    }
    else {
        FileList nn = newFnode(filename);
        n->next = nn;
        return n;
    }
}