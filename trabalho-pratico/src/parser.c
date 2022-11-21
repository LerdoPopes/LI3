#define BUF 1024

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct querie{
    int line; //linha do ficheiro da query
    char queriex; //query a ser executada
    char comando[500]; //arguments
} querie;

void *parser(FILE *to_parse, 
char const*rest,  
void* (*parse_func)(char**), 
void* (organize_func)(void **, void *, void *, void (*)(void *, void *, void *, void *, void *,void*), void * (*)(void *, void *, void *, void *,void*,void*)), 
void* struct_drivers, 
void* struct_users,
void(set_users_stats)(void*,void*,void*,void*, void*,void*), 
void*(set_driver_stats)(void*,void*,void*,void*, void*,void*))
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
    }
    result[i] = NULL;
    return organize_func(result,struct_drivers,struct_users,set_users_stats,set_driver_stats);
}

//  void* (organize_func2)(void** ,void* , void*, void*, void*), void* struct_drivers, void* struct_users, void*(set_users_stats)(void*,void*), void*(set_driver_stats)(void*,void*)