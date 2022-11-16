#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Include/dates.h"

void *process_ride(char* const* info);

void *organize_rides(void** results);

void free_rides(void* rides);