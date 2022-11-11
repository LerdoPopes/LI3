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
    us->pay_method = info[5][1]; 
    us->account_status = info[6][0]; //Para print disto, tem que se verificar a letra e dar print ao status com essa primeria letra 
    // printf("%s %s %c %s %s %s %c\n",us->username,us->name,us->birth_date,us->account_creation,us->pay_method,us->account_status);
    free(us);
    return us;
}