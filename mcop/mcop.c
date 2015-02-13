/*
*
*	MCOP is a huffman compressor written in C
*	@author : hamza bourrahim
*
*/

#include "../include/mcop.h"
#include "../include/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#include <windows.h>
#endif


int main(int argc , char ** argv){
	huff huffman;     				/* init huffman struct */
	list * hufflist = NULL;  		/* List of huffman frequencies  */
	list * mHufflist = NULL;

	if(argc < 2){
		printf(M_ERROR "mcop need arguments\n");
		return 0;
	}

	parse(argc, argv);


	/* copy argv[1] to huffman.path */
	//huffman.path = (char *)malloc(sizeof(char));
	//strcpy(huffman.path, argv[1]);
	//hufflist = file_constructOccur(huffman);

	/* manage it */
	
	//hufflist = manageList(hufflist);

	/* print the list */
	//printList(hufflist);


	/* free list */
	//freeList(hufflist);

#ifdef _WIN32
	Sleep (5000 );
#endif

	return 0;
} 