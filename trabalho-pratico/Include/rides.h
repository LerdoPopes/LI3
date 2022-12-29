#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../Include/dates.h"

typedef struct ride Ride;

typedef struct data_base_rides DB_Rides;

void *process_ride(char** info);

void *organize_rides(void** results);

void free_rides(void* rides);

int get_len_ride(void* ride_p);

char *ride_get_user(void *ride_p, int ID);
