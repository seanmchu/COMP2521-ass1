CC = gcc

all:test_Ass1

testfile: invertedIndex.c FileListNode.c InvertedIndexBST.c  Tfidf.c helper.c tests.c 
	gcc -o -Wall -Werror testfile invertedIndex.c FileListNode.c InvertedIndexBST.c Tfidf.c helper.c tests.c -lm

test_Ass1: test_Ass1.c invertedIndex.c FileListNode.c InvertedIndexBST.c  Tfidf.c helper.c 
	gcc -Wall -Werror -std=c11 -o test_Ass1 test_Ass1.c invertedIndex.c FileListNode.c InvertedIndexBST.c Tfidf.c helper.c -lm 