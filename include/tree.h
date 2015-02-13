/*
*
*	MCOP is a huffman compressor written in C
*	@author : hamza bourrahim
*
*/
#ifndef HTREE
#define HTREE

#include "mcop.h"
#include <math.h>

#define len(x) ((int)log10(x)+1)

struct node{
    int value;
    char letter;
    struct node *left,*right;
};

typedef struct node Node;

/* 81 = 8.1%, 128 = 12.8% and so on. The 27th frequency is the space. Source is Wikipedia */

noeud * toHuffTree(list * l);
list * manageList(list * src);
list * doManage(list * l, list* dest);
void buildHuffmanTree(Node **tree);
void fillTable(int codeTable[], Node *tree, int Code);
int findSmaller (Node *array[], int differentFrom);
void compressFile(FILE *input, FILE *output, int codeTable[]);
void decompressFile (FILE *input, FILE *output, Node *tree);
void invertCodes(int codeTable[],int codeTable2[]);

#endif