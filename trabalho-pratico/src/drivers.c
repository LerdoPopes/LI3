#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "drivers.h"

void *process_driver(char* const* info) {
    struct driver *dr = malloc(sizeof(struct driver));

    dr->id = atol(info[0]);
    dr->name = strdup(info[1]);
    memmove(dr->birth_date, info[2], strlen(info[2]));
    dr->gender = *info[3];
    dr->car_class = strdup(info[4]);
    memmove(dr->license_plate, info[5], strlen(info[5]));
    dr->city = strdup(info[6]);
    memmove(dr->account_creation, info[7], strlen(info[7]));
    // set_account_status(dr->account_status, info[8]);
    free(dr);
    return dr;
}

// char *set_account_status(int dr,const void* info)
// {
//     if(is_active(info)) dr = active;
//     dr == inactive;
// }

// int is_active(char* const* info)
// {
//     if(*info[1] == "active") return 1;
//     return 0;
// }