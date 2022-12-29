#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/rides.h"
#include "../Include/dates.h"
#include "../Include/queries.h"
#include <ctype.h>
#include <math.h>


struct city{

char *name;
double total_money;
double total_money_notip;

};




void *organize_statistics(void* dbUsers, void* dbRides, void* dbDrivers)
{
    int lenRide = get_len_ride(dbRides);    
        for(int i = 0; i < lenRide; i++){

        }

}