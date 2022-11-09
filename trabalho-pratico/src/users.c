#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "users.h"

void *process_user(char* const* info) 
{
    struct user *us = malloc(sizeof(struct user));

    us->username = strdup(info[0]);
    us->name = strdup(info[1]);
    us->gender = *info[2];
    memmove(us->birth_date, info[3], strlen(info[3]));
    memmove(us->account_creation, info[4], strlen(info[4]));
    
    free(us);
    return us;
}