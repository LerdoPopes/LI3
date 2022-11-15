//enum status{
//    active = 'a', 
//    inactive = 'i'
//};

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void *process_driver(char* const* info); 

void *organize_driver(void* gtable,void* driver);

void *arrange_driver(void* gtable,void** array);

void free_driver(void* driver);

