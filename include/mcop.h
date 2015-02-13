/*
*
*	MCOP is a huffman compressor written in C
*	@author : hamza bourrahim
*
*/

#ifndef HMCOP
#define HMCOP

#include <stdio.h>

extern int verbose_present;

/* for colors under linux */
#ifdef linux
	#define M_ERROR 	"[\033[31mError\033[0m] "
	#define M_ACTION 	"[\033[36mAction\033[0m] "
	#define M_OK 		"[\033[32mOk\033[0m] "
	#define M_DEBUG	    "[\033[33mDebug\033[0m] "
#endif

#ifdef _WIN32 
    #define M_ERROR     "[Error] "
    #define M_ACTION    "[Action] "
    #define M_OK        "[Ok] "
    #define M_DEBUG     "[Debug] "
#endif


/*  SUPPORT RECURSION */

#ifdef MCOP_REC
    #define M_REC 1
#endif

/* for win32 */

typedef struct sNoeud{
    char info;
    struct sNoeud * sAG;
    struct snoeud * sAD;
}noeud;
 
typedef struct sList{
    noeud * node; 			/* noeud d'arbe ==> info si le noeud 
    							n'a pas de fils */
    int freq;
    struct sList * pNext;
}list;
 
typedef struct sHuff{
    list * hufflist;		/* List of huffman frequencies  */
    unsigned char tab[256];
    char * path;
    /* add list */
}huff;
 
list * file_constructOccur(huff huffman);
void constructOccur(char * string);
int isPresent(huff huffman, char c, int last);
list * addList(list * l, char c, int nb);
list * printList(list * l);
list * freeList(list * l);
void parse(int argc, char ** argv);
int startCompression(char * path);

#endif