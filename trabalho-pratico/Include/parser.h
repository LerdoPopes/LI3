#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
// #include "../Include/dates.h"

void *parser(FILE *to_parse, 
char const*rest,  
void* (*parse_func)(char**), 
void* (organize_func)(void **,int , ...), 
...
/*void* struct_drivers, 
void* struct_users, 
void(set_users_stats)(void*,void*,void*,void*, void*,void*), 
void*(set_driver_stats)(void*,void*,void*,void*, void*,void*)*/);

void** parse_querie(FILE *to_parse, void* (process)(char**));

