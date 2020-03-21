#include"Tfidf.h"
#include"helper.h"
#include<stdlib.h>
#include<string.h>

//Removes a node from a Tfidf list
static void delTnode(tflist t,TfIdfList del_node);
//Creates a new tfidf list node
static TfIdfList newTnode(char *filename, double tfidfsum);

tflist newTL() {
    tflist new_tlist = malloc(sizeof(struct TfIdfRep));
    new_tlist->head = NULL;
    new_tlist->curr = NULL;
    return new_tlist;
}

TfIdfList newTnode(char *filename, double tfidfsum) {
    TfIdfList new_tnode = malloc(sizeof(struct TfIdfNode));
    new_tnode->filename = filename;
    new_tnode->tfIdfSum = tfidfsum;
    new_tnode->next = NULL;
    return new_tnode;
}


//I could do this recursively, but it doesn't actually save any time, so I did it iteratively, which is easier
//and less likely to make mistakes in placing the head.
void insertTnode(tflist tlist,char *filename, double tfidfsum) {
    //Order by descending order of tfidf, if tfidf is equal, ascending order alphabetically
    TfIdfList new_node = newTnode(filename,tfidfsum);
    if (tlist->head == NULL) {
        tlist->head = new_node;
        tlist->curr = new_node; 
        return;
    } else {
        //Case 0:filename is already existant
        //We sum the tfidf values, and reinsert the node.
        for (TfIdfList curr = tlist->head;curr != NULL; curr = curr->next) {
            if (!strcmp(curr->filename,new_node->filename)) {
                double tempsum = curr->tfIdfSum + new_node->tfIdfSum;
                delTnode(tlist,curr);
                insertTnode(tlist,filename,tempsum);
                return;
            }
        }
        //Case 1: new head
        if (new_node->tfIdfSum >= tlist->head->tfIdfSum) { 
            //new head because tfidf is bigger, or equal and alphabetically before
            if (new_node->tfIdfSum > tlist->head->tfIdfSum ||
                alphacmp(new_node->filename,tlist->head->filename) == -1) {
                new_node->next = tlist->head;
                tlist->head = new_node;
                return;
            }
        }
        //Case 2:insert in middle
        TfIdfList curr = tlist->head;
        while (curr->next != NULL) {
            //Check if new node is before curr->next
            if (new_node->tfIdfSum >= curr->next->tfIdfSum) {
                if (new_node->tfIdfSum > curr->next->tfIdfSum ||
                alphacmp(new_node->filename,curr->next->filename) == -1) {
                    new_node->next = curr->next;
                    curr->next = new_node;
                    return;
                }
            }
            curr = curr->next;
        }
        //Case 3:insert at end
        curr->next = new_node;
        return;

    }
}

TfIdfList getTfIdf(FileList search_list, int D) {
    int list_size = listSize(search_list);
    double idf = getIDF(D,list_size);
    tflist TL = newTL();
    for (FileList curr = search_list; curr != NULL; curr = curr->next) 
        insertTnode(TL,curr->filename,idf * curr->tf);
    return TL->head;
}

//Deletes a Tnode, static since only used in insertTnode
static void delTnode(tflist t, TfIdfList del_node) {
    if (t->head == NULL) return;
    if (t->head == del_node) {
        t->head = del_node->next;
        if (t->curr == t->head) {
            t->curr = del_node->next;
        }
        return;
    } else {
        for (TfIdfList curr = t->head; curr->next != NULL; curr = curr->next) {
            if (curr->next == del_node) {
                curr->next = del_node->next;
                return;
            }
        }
        return;
    }
}