#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void **parser(FILE *to_parse, char *rest, void* (*parse_func)(char* const*));
