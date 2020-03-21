#include"FileListNode.h"
#include"helper.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
//makes a new file list node
static FileList newFnode (char *filename);

FileList newFnode (char *filename) {
    if (filename == NULL) return NULL;
    FileList n = malloc (sizeof(struct FileListNode));
    n->filename = filename;
    n->tf = 0;
    n->next = NULL;
    return n;
}

flhead newFL() {
    flhead f = malloc(sizeof(struct FileListRep));
    f->head = NULL;
    f->curr = NULL;
    return f;
}

void insertFnode(flhead n,char *filename,double tf) {
    FileList nn = newFnode(filename);
    nn->tf = tf;
    if (n->head == NULL) {
        n->head = nn;
        n->curr = nn;
        return;
    } else {
        if (alphacmp(filename,n->head->filename) == -1) {
            nn->next = n->head;
            n->head = nn;
            return;
        }
        FileList curr = n->head;
        while(curr->next != NULL) {
            //prevent making doubles
            if (!strcmp(filename,curr->filename)) return;
            if (alphacmp(filename,curr->filename) == 1 && alphacmp(filename,curr->next->filename) == - 1){
                nn->next = curr->next;
                curr->next = nn;
                return;
            }
            curr = curr->next;
        }
        //Final possible case is that curr->next is NULL;
        curr->next = nn;
        return;
    }
}

flhead gen_read_fl(char *collectionFilename) {
    FILE *fp = fopen(collectionFilename,"r");
    flhead f = newFL();
    char *str = malloc(sizeof(char)* 100);
    while (fscanf(fp,"%s",str) != EOF) {
        insertFnode(f,str,0);
        f->curr = f->head;
        //we malloc new strings so we don't keep changing the string in the original node
        str = malloc(sizeof(char)*100);
    }
    fclose(fp);
    return f;
}