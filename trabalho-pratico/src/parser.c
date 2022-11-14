#define BUF 1024

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void *parser(FILE *to_parse, char const*rest, void* (*parse_func)(char* const*), void*(*organize_func)(void* , void*), void*(arrange_func)(void*, void**))
{
    size_t current = 128;
    void **result = malloc(sizeof(void*) * current);
    void *hashtable = NULL;
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
        hashtable = organize_func(hashtable, result[i-1]);
    }
    result[i] = NULL;
    void* final = arrange_func(hashtable,result);

    return final;
}


