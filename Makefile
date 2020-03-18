CC = gcc

invertedIndex: invertedIndex.c FileListNode.c InvertedIndexBST.c  Tfidf.c
	gcc -o invertedIndex invertedIndex.c FileListNode.c InvertedIndexBST.c Tfidf.c 