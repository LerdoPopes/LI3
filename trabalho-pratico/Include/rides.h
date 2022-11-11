#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// #include "../Include/dates.h"

typedef struct ride {
    size_t id;
    char date[sizeof("AAAA/MM/DD")];
    size_t driver; 
    char *user;
    char *city;
    size_t distance;
    size_t score_user;
    size_t score_driver;
    size_t tip;
    char *comment;
} Ride;

void *process_ride(char* const* info);