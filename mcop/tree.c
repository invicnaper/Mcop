/*
*
*   MCOP is a huffman compressor written in C
*   @author : hamza bourrahim
*
*/

#include "../include/mcop.h"
#include "../include/tree.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#endif

int frenchLetterFrequencies [27] = {81, 15, 28, 43, 128, 23, 20, 61, 71, 2, 1, 40, 24, 69, 76, 20, 1, 61, 64, 91, 28, 10, 24, 1, 20, 1, 130};

noeud * toHuffTree(list * l){
	/* tree convertion  for some performance*/

}
list * doManage(list * l, list * dest){
	if(!l || !dest)
		return NULL;

	manageList(l);

	return  doManage(l->pNext, dest);
}
list * manageList(list * src){
	/* TODO:  */
	int i;
	char info;
	list * newL = NULL;

	info = src->node->info;

	while(src != NULL){
		if(info < src->node->info){
			info = src->node->info;
			newL = addList(src, src->node->info, src->freq);
			src = src->pNext;
		}else{
			src = src->pNext;
		}

	}
	return newL;
}
void buildHuffmanTree(Node **tree){
    Node *temp;
    Node *array[27];
    int i, subTrees = 27;
    int smallOne,smallTwo;

    for (i=0;i<27;i++){
        array[i] = malloc(sizeof(Node));
        array[i]->value = frenchLetterFrequencies[i];
        array[i]->letter = i;
        array[i]->left = NULL;
        array[i]->right = NULL;
    }

    while (subTrees>1){
        smallOne=findSmaller(array,-1);
        smallTwo=findSmaller(array,smallOne);
        temp = array[smallOne];
        array[smallOne] = malloc(sizeof(Node));
        array[smallOne]->value=temp->value+array[smallTwo]->value;
        array[smallOne]->letter=127;
        array[smallOne]->left=array[smallTwo];
        array[smallOne]->right=temp;
        array[smallTwo]->value=-1;
        subTrees--;
    }

    *tree = array[smallOne];

return;
}

void fillTable(int codeTable[], Node *tree, int Code){
    if (tree->letter<27)
        codeTable[(int)tree->letter] = Code;
    else{
        fillTable(codeTable, tree->left, Code*10+1);
        fillTable(codeTable, tree->right, Code*10+2);
    }

    return;
}