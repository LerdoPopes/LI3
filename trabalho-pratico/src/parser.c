#define BUF 1024

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

void *parser(FILE *to_parse, 
char const*rest,  
void* (*parse_func)(char**), 
void* (organize_func)(void **))
{
    size_t current = 128;
    void **result = malloc(sizeof(void*) * current);
    size_t i = 0;
    char skip = 0;
    
    for(char buf[BUF] = { 0 }; fgets(buf, BUF, to_parse) != NULL;)
    {
        if(skip == 0)
        {
            skip++;
            continue;
        }
        char *save[12] = { 0 };
        
        size_t j = 0;
        for(char *token = buf, *aux = buf; token != NULL; token = aux) {
            token = strsep(&aux, rest);
            save[j++] = token;
        }

        if(i + 1 == current) { 
            result = realloc(result, (current *= 2) * sizeof(void*)); 
        }
        result[i++] = parse_func(save); 
        if(result[i-1] == NULL){
            i--;
        }
    }
    result[i] = NULL;
    return organize_func(result);
}



void** parse_query(FILE *to_parse, void* (process)(char**))
{
size_t current = 64;
    void **result = malloc(sizeof(void*) * current);
    size_t i = 0;
    
    for(char buf[BUF] = { 0 }; fgets(buf, BUF, to_parse) != NULL;)
    {
        char *save[12] = { 0 };
        
        size_t j = 0;
        for(char *token = buf, *aux = buf; token != NULL; token = aux) {
            token = strsep(&aux, " \n\r");
            save[j++] = token;
        }

        if(i + 1 == current) { 
            result = realloc(result, (current *= 2) * sizeof(void*)); 
        }
        save[j] = NULL;
        result[i++] = process(save);
    }
    result[i] = NULL;
    return result;
}

