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

short ride_get_date(void* rides_p, int Id);

int ride_get_driver(void *ride_p, int ID);

char *ride_get_user(void *ride_p, int ID, char* dest, int* size);

char *ride_get_city(void *ride_p, int ID, char* dest, int* size);

short ride_get_distance(void *ride_p,int ID);

short ride_get_score_driver(void *ride_p, int ID);

short ride_get_score_user(void *ride_p, int ID);

double ride_get_tip(void *ride_p, int ID);

char *ride_get_comment(struct ride *r);

int get_len_ride(void* rides_p);

int ride_get_idArray(void *ride_p, int i);

int isRide(void* ride_p, int ID);

//int get_len_ride(void* ride_p);

