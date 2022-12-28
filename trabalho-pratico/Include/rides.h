#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../Include/dates.h"

typedef struct ride Ride;

typedef struct data_base_rides DB_Rides;

void *process_ride(char** info);

void *organize_rides(void** results,int num_args, ... );

void free_rides(void* rides);

typedef struct ride Ride;





