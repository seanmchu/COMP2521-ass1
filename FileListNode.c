#include"FileListNode.h"
#include"helper.h"
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

//Inserts a node at the correct position alphabetically in the list, returns the head of the list.
FileList insertFnode(FileList n,char *filename) {
    //if FL is empty, make new head
    FileList nn = newFnode(filename);
    if (!n) {
        return nn;
    }
    //Otherwise, we insert alphabetically
    FileList curr = n;
    while (curr) { //Move to alphabetically correct spot
        if (alphacmp(filename,curr->filename) > 0) {
                curr = curr->next;
        } else {
            break;
        }
    }
    if (curr->next) { //If we aren't at the end of the list (found alphabetical spot)
        nn->next = curr->next;
        curr->next = nn;
        return n;
    } else { //If we reached the end of the list
        curr->next = nn;
        return n;
    }   
}