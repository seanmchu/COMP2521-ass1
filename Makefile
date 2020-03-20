CC = gcc

all:testfile test_Ass1

testfile: invertedIndex.c FileListNode.c InvertedIndexBST.c  Tfidf.c helper.c tests.c 
	gcc -o testfile invertedIndex.c FileListNode.c InvertedIndexBST.c Tfidf.c helper.c tests.c 

test_Ass1: test_Ass1.c invertedIndex.c FileListNode.c InvertedIndexBST.c  Tfidf.c helper.c 
	gcc -o test_Ass1 test_Ass1.c invertedIndex.c FileListNode.c InvertedIndexBST.c Tfidf.c helper.c 