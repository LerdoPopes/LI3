#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Include/drivers.h"

typedef struct driver {
    size_t id;
    char *name;
    char birth_date[sizeof("AAAA/MM/DD")];
    char gender;
    char *car_class;
    char license_plate[sizeof("00-00-AA")];
    char *city;
    char account_creation[sizeof("AAAA/MM/DD")];
    char account_status;
} Driver;

void *process_driver(char* const* info) {
    struct driver *dr = malloc(sizeof(struct driver));

    size_t size = sizeof("DD/MM/AAAA");

    dr->id = atol(info[0]);
    dr->name = strdup(info[1]);
    memmove(dr->birth_date, info[2], size);
    dr->gender = *info[3];
    dr->car_class = strdup(info[4]);
    memmove(dr->license_plate, info[5], size);
    dr->city = strdup(info[6]);
    memmove(dr->account_creation, info[7], size);
    dr->account_status = info[8][0];
    return dr;
}
