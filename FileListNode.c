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
void insertFnode(flhead n,char *filename) {
    //if FL is empty, make new head
    FileList nn = newFnode(filename);
    if (!n->head) {
        printf("added %s to the list VIA HEAD\n",filename);
        n->head = nn;
        n->curr = nn;
    }
    //Otherwise, we insert alphabetically
    FileList curr = n->curr;
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
        printf("added %s to the list, %s is head\n",curr->filename,n->head->filename);
    } else { //If we reached the end of the list
        curr->next = nn;
        printf("added %s to the list, %s is head\n",curr->filename,n->head->filename);
    }   
}