#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Include/dates.h"

void *process_ride(char* const* info);

void *organize_rides(void* gtablep,void* ridesp);

void *arrange_rides(void* gtable,void** array);

void free_rides(void* rides);