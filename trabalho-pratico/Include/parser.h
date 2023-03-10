#ifndef PARSER_H
#define PARSER_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
// #include "../Include/dates.h"

void *parser(FILE *to_parse, 
char const*rest,  
void* (*parse_func)(char**), 
void* (organize_func)(void **), 
...
/*void* struct_drivers, 
void* struct_users, 
void(set_users_stats)(void*,void*,void*,void*, void*,void*), 
void*(set_driver_stats)(void*,void*,void*,void*, void*,void*)*/);

void** parse_query(FILE *to_parse, void* (process)(char**));

#endif