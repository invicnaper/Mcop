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
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#endif

int verbose_present;

void parse(int argc, char ** argv){
	int i = 0;
	char c;
	c= argv[1][1]; /* the 0 is - */

	/* check for verbose */

	if(strcmp(argv[argc-1], "--verbose") == 0){
		verbose_present = 1;
	}else{
		verbose_present = 0;
	}

	/* first arg must be a command , so checking it out */

	if(strlen(argv[1]) > 2){
		printf(M_ERROR "'%s' must be a param , check -h\n",argv[1]);
		return ;
	}

	switch(c){
		case 'c':
			/* compress, check if argv[2] is present */
			if(argv[2] != NULL && !strstr(argv[2],"--verbose")){
				startCompression(argv[2]);
			}else{
				printf(M_ERROR "please give us file to compress\n");
			}
			break;
		case 'd':
			/* decompress */
			if(argv[2] != NULL &&!strstr(argv[2],"--verbose")){
				startDeCompression(argv[2]);
			}else{
				printf(M_ERROR "please give us file to compress\n");
			}
			break;
		case 'r':
			/* recur , check if type is set or not */
			if(!argv[2]){
				printf(M_ERROR "please set a type file\n");
				return ;
			}
			if(strcmp(argv[2], "--type") == 0 && argv[3] != NULL){
				if(!strstr(argv[3],"--verbose")){
					recur(argv[3]);
				}else{
					printf(M_ERROR "please set a type file\n");
				}
			}else{
				/* all files */
			}
			break;
		case 'h':	
			/*  help */
			break;
		default:
			printf(M_ERROR "Unknown param '%c' please check -h for help\n", c);
			break;
	}

	return ;
}	

int startCompression(char * path){
	Node *tree;
    int codeTable[27], codeTable2[27];
    int compress;
    FILE *input, *output;
    buildHuffmanTree(&tree);

    fillTable(codeTable, tree, 0);

    invertCodes(codeTable,codeTable2);

    input = fopen(path, "r");
    //printf("%s \n",path);
    output = fopen("output.txt","w");

    if(!input){
    	printf(M_ERROR "can't found the file '%s'\n",path);
    	return 0;
    }else{
    	if(verbose_present == 1)
    		printf(M_ACTION "compressing '%s'\n", path);
    	compressFile(input,output,codeTable2);
    }

       // decompressFile(input,output, tree);

    return 0;

}
int startDeCompression(char * path){
	Node *tree;
    int codeTable[27], codeTable2[27];
    int compress;
    FILE *input, *output;
    buildHuffmanTree(&tree);

    fillTable(codeTable, tree, 0);

    invertCodes(codeTable,codeTable2);

    input = fopen(path, "r");
    output = fopen("decompress.txt","w");

    if(!input){
    	printf(M_ERROR "can't found the file '%s'\n",path);
    	return 0;
    }else{
    	if(verbose_present == 1)
    		printf(M_ACTION "decompressing '%s'\n", path);
    	decompressFile(input,output, tree);
    }


    return 0;

}
#ifdef MCOP_REC
int recur(char* type){
	char cmd[200];
	char s[200];
	int nb_files;
	FILE * fp;
	if(verbose_present){
		printf(M_ACTION "Checking for MCOP_REC on gcc ..\n");
		printf(M_OK "MCOP_REC is set on gcc\n");
		printf(M_ACTION "compressing all '%s' files\n", type);
	}
	/* create a tmp file for ls */
#ifdef linux
	sprintf(cmd,"ls *.%s >> /tmp/mcopls.txt\n",type);
	system(cmd);
	/* open the file */
	fp = fopen("/tmp/mcopls.txt", "rb");
	if(!fp){
		printf(M_ERROR "error while reading tmp file \n");
	}else{
		if(verbose_present)
			printf(M_ACTION "reading all '%s' files\n",type);
		printf("~Files \n\n");
		while(fgets(s, 200, fp) != NULL){
			printf("~~~%s \n",s);
			/* compress every file */
			startCompression(s);
			nb_files ++;
		}
		if(nb_files == 0)
			printf(M_ERROR "no files \n");
	}

	/* delete the tmp file */
	system("rm /tmp/mcopls.txt");
#endif
#ifdef _WIN32
	printf(M_ERROR "not yet implemented for windows\n")
#endif

	return 0;

}
#else
int recur(char* type){
	printf(M_ERROR "you should add MCOP_REC to gcc for using -r option\n");
}
#endif