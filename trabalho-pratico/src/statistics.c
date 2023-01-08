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




 void *organize_statistics(void* dbUsers, void* dbRides, void* dbDrivers){
     int n = get_len_ride(dbRides); 
         for(int i = 1; i <= n; i++){
            int driver_ID = ride_get_driver(dbRides,i);
            char *user = ride_get_user(dbRides,i);
            short date = ride_get_date(dbRides,i);
            char *city = ride_get_city(dbRides,i);
            double tip = ride_get_tip(dbRides,i);
            short distance = ride_get_distance(dbRides,i);
            short score_driver = ride_get_score_driver(dbRides,i);
            short score_user = ride_get_score_user(dbRides,i);
            double *money = (double *) set_driver_stats(dbDrivers,&distance,&score_driver,&driver_ID,&tip,&date);
            set_user_stats(dbUsers,&distance,&score_user,user,money,&date);

            free(money);
            free(city);
            free(user);
        }    
 }