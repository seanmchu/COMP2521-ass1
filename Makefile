CC = gcc

invertedIndex: invertedIndex.c FileListNode.c InvertedIndexBST.c 
	gcc -o invertedIndex invertedIndex.c FileListNode.c InvertedIndexBST.c 