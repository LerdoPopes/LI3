#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rides.h"

void *process_ride(char* const* info) {
    struct ride *ri = malloc(sizeof(struct ride));

    ri->id = atol(info[0]);
    memmove(ri->date, info[1], strlen(info[1]));
    ri->driver = atol(info[2]);
    ri->user = strdup(info[3]);
    ri->city = strdup(info[4]);
    ri->distance = atol(info[5]);
    ri->score_user = atol(info[6]);
    ri->score_driver = atol(info[7]);
    ri->tip = atol(info[8]);
    ri->comment = strdup(info[9]);
    free(ri);
    return ri;
}