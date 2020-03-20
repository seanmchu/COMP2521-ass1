#include"invertedIndex.h"
#include"tests.h"
#include"helper.h"
#include"InvertedIndexBST.h"
#include"FileListNode.h"
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
//Test functions not tested in given test file
void main(){
    run_tests();
}


void run_tests(){
    printf("Running tests\n");
    printf("Running alphacmp tests\n");
    test_alphacmp();
    printf("alphacmp tests successful\n");   
    printf("Running newInode tests\n");
    test_newInode();
    printf("newInode tests done\n");
    printf("Running insertInode tests\n");
    test_insertInode();
    printf("insertInode tests done\n");
    printf("Running newFnode tests\n");
    test_newFnode();
    printf("newFnode tests done\n");
    printf("Running newFL tests\n");
    test_newFL();
    printf("newFL tests done\n");
    printf("Running insertFnode tests\n");
    test_insertFnode();
    printf("insertFnode tests done\n");
    printf("Running gen_read_fl tests\n");
    test_gen_read_fl();
    printf("gen_read_fl tests done\n");
    printf("Tests done\n");

}

static void test_alphacmp(){
    assert (alphacmp("hello","hello") == 0);
    assert(alphacmp("a","b") == -1);
    assert(alphacmp("b","a") == 1);
    assert(alphacmp("abaaa","abaaaa") == -1);
    assert(alphacmp("aaaa","baa") == -1);
    assert(alphacmp("planets","mixed") == 1);
}

static void test_newInode(){
    InvertedIndexBST b = newInode("hello");
    //printf("%s\n",b->word);
    assert (!strcmp(b->word,"hello"));
    assert (!strcmp(b->word,"hello"));
    InvertedIndexBST b2 = newInode("HELLO");
    assert (!strcmp(b2->word,"hello"));
    InvertedIndexBST b3 = newInode("HELLO???");
    assert(!strcmp(b3->word,"hello??"));
    free(b);
    free(b2);
    free(b3);
}
static void test_insertInode() {
    InvertedIndexBST root = NULL;
    root = insertInode(root,"Hello");
    //printf("root is %s\n",root->word);
    assert (!strcmp(root->word,"hello"));
    root = insertInode(root,"helloo");
    root = insertInode(root,"hello");
    assert (!strcmp(root->word,"hello"));
    assert (!strcmp(root->right->word,"helloo"));
    root = insertInode(root,"hella");
    assert(!strcmp(root->left->word,"hella"));
    assert (!root->left->left);
    assert (!root->right->right);
    assert(!root->left->right);
    assert(!root->right->left);
    free(root->right);
    free(root->left);
    free(root);
    InvertedIndexBST root2 = NULL;
    root2 = insertInode(root2,"Mars");
    root2 = insertInode(root2,"Has");
    root2 = insertInode(root2,"long");
    root2 = insertInode(root2,"been");
    root2 = insertInode(root2,"the");
    assert(!strcmp(root2->word,"mars"));
}


static void test_newFnode(){
    FileList n = newFnode("hello");
    assert (!strcmp(n->filename,"hello"));
    free(n);
}

static void test_newFL(){
    flhead f = newFL();
    f->head = newFnode("Hello");
    f->curr = newFnode("Goodbye");
    assert(!strcmp(f->head->filename,"Hello"));
    assert(!strcmp(f->curr->filename,"Goodbye"));
    free(f->curr);
    free(f->head);
    free(f);
}
static void test_insertFnode(){
    flhead f = newFL();
    insertFnode(f,"b",0);
    assert(!strcmp(f->head->filename,"b"));
    assert(!strcmp(f->curr->filename,"b"));
    insertFnode(f,"c",0);
    assert(!strcmp(f->head->filename,"b"));
    assert(!strcmp(f->curr->filename,"b"));
    f->curr = f->curr->next;
    assert(!strcmp(f->curr->filename,"c"));
    insertFnode(f,"a",0);
    assert(!strcmp(f->head->filename,"a"));
    assert(!strcmp(f->curr->filename,"c"));
}


static void test_gen_read_fl() {
    flhead f = gen_read_fl("collection.txt");
    f->curr = f->head;
    assert(!strcmp(f->head->filename,"file11.txt"));
    assert(!strcmp(f->head->next->filename,"file21.txt"));
}
static void test_generateEmptyBST(){
}
static void test_populateBST(){

}