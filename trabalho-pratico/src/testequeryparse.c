#define BUF 1024
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct querie{
    int line; //linha do ficheiro da query
    char queriex; //query a ser executada
    char comando[500]; //args
} querie;

void *parseQueries(FILE *queries){
    size_t numquerie = BUF;
    size_t current = 128;
    querie *all = calloc(numquerie, sizeof(querie)); //todas as querys
    //char *um = malloc(sizeof(char)*current); 
    char *str = (char *)malloc(sizeof(char)*numquerie);
    int i=1;
    for(; fgets(str,BUF,queries) != NULL;){
        querie* one = malloc(sizeof (querie));
        one->queriex = str[0];

        char *store[20] = { 0 };
        
        size_t j = 0;
        for(char *token = str, *aux = str; token != NULL; token = aux){ 
            token = strtok(aux," ");
            store[j++] = token;

        } 
        strcpy(one->comando,&store[1]);
        one->line = i;
        i++;

        all [i-1] = *one;

        if(i + 1 > BUF){
            all = realloc(all, (numquerie *= 2) * sizeof(querie));

        }
    }    
    all[i].line = 1;
    return all;

}

void q_printall(querie *all){
    int i = 0;
    printf("%d\n", all[i].line);
    while (all[i].line != 1){
        printf("indice: %d\n",all[i].line);
        printf("n: %c\n",all[i].queriex);
        printf("argument: %s\n",all[i].comando);
        printf("------------------------------------------------------------------\n");
        i++;
    }
    printf("done\n");

} 

void main(int argc,char **argv) {
    FILE * querys = fopen(argv[1], "r");
    void * monky = parseQueries(querys);
    q_printall(monky);
}