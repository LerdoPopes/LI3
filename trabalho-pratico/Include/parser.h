#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// #include "../Include/dates.h"

void *parser(FILE *to_parse, char *rest, void* (*parse_func)(char* const*), void*(*organize_func)(void**), void*(arrange_func)(void*, void**));
