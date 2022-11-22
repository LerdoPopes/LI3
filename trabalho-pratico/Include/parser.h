#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// #include "../Include/dates.h"

void *parser(FILE *to_parse, char const*rest,  void* (*parse_func)(char**), void* (organize_func)(void **, void *, void *, void (*)(void *, void *, void *, void *, void *,void*), void * (*)(void *, void *, void*, void *, void *,void*)), void* struct_drivers, void* struct_users, void(set_users_stats)(void*,void*,void*,void*, void*,void*), void*(set_driver_stats)(void*,void*,void*,void*, void*,void*));

void* process_querie(char** save);

void** parse_querie(FILE *to_parse)


//void *parseQueries(FILE *queries);

//void q_printall(Querys *all);
