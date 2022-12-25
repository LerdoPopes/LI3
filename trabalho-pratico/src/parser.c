#define BUF 1024

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

//typedef struct querie{
//    int line; //linha do ficheiro da query
//    char queriex; //query a ser executada
//    char comando[500]; //arguments
//} querie;

void *parser(FILE *to_parse, 
char const*rest,  
void* (*parse_func)(char**), 
void* (organize_func)(void **, int, .../*void * , void *, void (*)(void *, void *, void *, void *, void *,void*), void * (*)(void *, void *, void *, void *,void*,void*)*/), 
int num_args_xtra,
...
/*void* struct_drivers, 
void* struct_users,
void(set_users_stats)(void*,void*,void*,void*, void*,void*), 
void*(set_driver_stats)(void*,void*,void*,void*, void*,void*)*/)
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
    if(num_args_xtra == 0){
        return organize_func(result,num_args_xtra);
    }
    va_list args;
    va_start(args, num_args_xtra);
    void * struct_drivers = va_arg(args,void*);
    void * struct_users = va_arg(args,void*);
    void (*set_users_stats)(void *, void *, void *, void *, void *, void *) = va_arg(args,void (*)(void *, void *, void *, void *, void *, void *));
    void* (*set_driver_stats)(void *, void *, void *, void *, void *, void *) = va_arg(args,void *(*)(void *, void *, void *, void *, void *, void *));
    va_end(args);
    return organize_func(result,num_args_xtra,struct_drivers,struct_users,set_users_stats,set_driver_stats);

}









void** parse_querie(FILE *to_parse, void* (process)(char**))
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



//void q_printall(void **all){
//    int i;
//    for(i=0;all[i];i++){
//        char** save = (char**) all[i];
//        for (size_t j = 0; save[j]; j++)
//        {
//            printf("%s\n",save[j]);
//        }
//    
//    }
//    printf("done\n");
//
//} 
//
//void main(int argc,char **argv) {
//    FILE * querys = fopen("./input.txt", "r");
//    void ** monky = parser(querys);
//    q_printall(monky);
//}

//  void* (organize_func2)(void** ,void* , void*, void*, void*), void* struct_drivers, void* struct_users, void*(set_users_stats)(void*,void*), void*(set_driver_stats)(void*,void*)