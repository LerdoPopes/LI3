#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../Include/dates.h"

void *process_ride(char** info);

void *organize_rides(void** results);

void free_rides(void* rides);

typedef struct ride Ride;
