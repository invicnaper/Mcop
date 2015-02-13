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

list * file_constructOccur(huff huffman){
    int count[256] = { 0 };
    int k;
    list * tmp = NULL;
    FILE *fp = fopen(huffman.path, "r");
    int c;

    if(!fp){
        printf(M_ERROR "can't found the file '%s' \n",huffman.path);
    }else{
        while((c=fgetc(fp))) {

            if(c == EOF) break;

            count[c]+=1;
        }

        for(k=0; k<256; k++) {
            if(count[k] > 0) {
                /* add to list */
                tmp = addList(tmp, k, count[k]);
            }
        }
        fclose(fp);
    }
    return tmp;
}
int isPresent(huff huffman, char c, int last){
    /* check if c is present and return 1 */
    int i;
    for(i = last+2 ;i<256; i+=2){
        if(huffman.tab[i] == c){
            return 1;
        }
    }
    return 0;
}
int getPos(huff huffman, char c){
    /* return pos */
    int i;
    for(i = 0 ;i<256; i++){
        if(huffman.tab[i] == c){
            return i;
        }
    }
}
list * addList(list * l, char c, int nb){
    list * tmp = NULL;
    noeud * node = NULL;
    tmp = (list *)malloc(sizeof(list));
    node = (noeud *)malloc(sizeof(noeud));

    if(!tmp){
        printf(M_ERROR "can't create the list\n");
    }else{
        tmp->node = node;
        node->info = c;
        tmp->freq = nb;
        tmp->pNext = l;
    }

    return tmp;
}
list * printList(list * l){
    if(!l)
        return NULL;


    printf(M_ACTION "%c => %d\n",l->node->info, l->freq);

    return printList(l->pNext);
}
list * freeList(list * l){
    if(!l)
        return NULL;

    free(l);

    return freeList(l->pNext);
}
void tolist(huff huffman){
    /* create list from tab */
 
    return ;
}
/*finds and returns the small sub-tree in the forrest*/
int findSmaller (Node *array[], int differentFrom){
    int smaller;
    int i = 0;

    while (array[i]->value==-1)
        i++;
    smaller=i;
    if (i==differentFrom){
        i++;
        while (array[i]->value==-1)
            i++;
        smaller=i;
    }

    for (i=1;i<27;i++){
        if (array[i]->value==-1)
            continue;
        if (i==differentFrom)
            continue;
        if (array[i]->value<array[smaller]->value)
            smaller = i;
    }

    return smaller;
}
void compressFile(FILE *input, FILE *output, int codeTable[]){
    char bit, c, x = 0;
    int n,length,bitsLeft = 8;
    int originalBits = 0, compressedBits = 0;

    while ((c=fgetc(input))!=10){
        originalBits++;
        if (c==32){
            length = len(codeTable[26]);
            n = codeTable[26];
        }
        else{
            length=len(codeTable[c-97]);
            n = codeTable[c-97];
        }

        while (length>0){
            compressedBits++;
            bit = n % 10 - 1;
            n /= 10;
            x = x | bit;
            bitsLeft--;
            length--;
            if (bitsLeft==0){
                fputc(x,output);
                x = 0;
                bitsLeft = 8;
            }
            x = x << 1;
        }
    }

    if (bitsLeft!=8){
        x = x << (bitsLeft-1);
        fputc(x,output);
    }

    if(verbose_present){
        printf(M_ACTION "Original bits = %d\n",originalBits*8);
        printf(M_ACTION"Compressed bits = %d\n",compressedBits);
        printf(M_ACTION"Saved %.2f%% of memory\n",((float)compressedBits/(originalBits*8))*100);    
    }
        
    printf(M_OK "file compressed \n");
    printf("~~~output.txt\n");

    return;
}
void decompressFile (FILE *input, FILE *output, Node *tree){
    Node *current = tree;
    char c,bit;
    char mask = 1 << 7;
    int i;

    while ((c=fgetc(input))!=EOF){

        for (i=0;i<8;i++){
            bit = c & mask;
            c = c << 1;
            if (bit==0){
                current = current->left;
                if (current->letter!=127){
                    if (current->letter==26)
                        fputc(32, output);
                    else
                        fputc(current->letter+97,output);
                    current = tree;
                }
            }

            else{
                current = current->right;
                if (current->letter!=127){
                    if (current->letter==26)
                        fputc(32, output);
                    else
                        fputc(current->letter+97,output);
                    current = tree;
                }
            }
        }
    }

    printf(M_OK "file decompressed \n");
    printf("~~~decompress.txt\n");

    return;
}


void invertCodes(int codeTable[],int codeTable2[]){
    int i, n, copy;

    for (i=0;i<27;i++){
        n = codeTable[i];
        copy = 0;
        while (n>0){
            copy = copy * 10 + n %10;
            n /= 10;
        }
        codeTable2[i]=copy;
    }

    return;
}