#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Include/dates.h"

void *process_ride(char** info);

void *organize_rides(void** results, void* struct_drivers, void* struct_users, void(set_users_stats)(void*,void*,void*,void*,void*), void*(set_driver_stats)(void*,void*,void*,void*));

void free_rides(void* rides);

typedef struct ride Ride;

int ride_get_id(struct ride *r);

short ride_get_date(struct ride *r);

size_t ride_get_driver(struct ride *r);

char *ride_get_user(struct ride *r);

char *ride_get_city(struct ride *r);

size_t ride_get_distance(struct ride *r);

size_t ride_get_score_user(struct ride *r);

size_t ride_get_score_driver(struct ride *r);

size_t ride_get_tip(struct ride *r);

char *ride_get_comment(struct ride *r);



