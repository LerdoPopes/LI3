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

void* process_querie(char** save){
    char** save2 = malloc(12*sizeof(char*));
    size_t i = 0;
    for(; save[i]; i++)
    {
        save2[i] = strdup(save[i]);
    }
    save2[i] = NULL;
    return save2;
}

void answer_queries(void** input, void* USERS, void* DRIVERS){
    char*** INPUT = (char***) input;
    for(short i = 0, j = 1; INPUT[i] != NULL;i++,j++){
         switch(atoi(INPUT[i][0])){
             case(1):                                              
                 query1(INPUT[i][1],DRIVERS,USERS,j);
                 break;
             case(2):
                 query2(INPUT[i][1],DRIVERS,j);
                 break;
             case(3):
                 query3(INPUT[i][1],USERS,j);
                 break;
         }
    }
}

void query1(char *ID, void *dbDrivers, void *dbUsers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");    
    if(isdigit(ID[0])){
        answer_q1_driver(resultado,dbDrivers,ID);
    }
    else{
        answer_q1_user(resultado,dbUsers,ID);
    }
}

void query2(char* N, void *dbDrivers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");    
        answer_q2_driver(resultado,dbDrivers,atoi(N));
    }

void query3(char *N, void *dbUsers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");    
        answer_q3_user(resultado,dbUsers,atoi(N));
    }


void answer_q4(FILE* input,char *city,void *db_rides, void *db_drivers){
    DB_Rides* dbRides = (DB_Rides*) db_rides;
    DB_drivers* dbDrivers = (DB_Drivers*) db_drivers;
    GHashTable* dbdrivers = dbDrivers->drivers_hashtable;
    Ride** rides = dbRides->rides_array;
    int n_rides = 0;
    double total = 0.0;
    int n = dbRides->len;
    for(int i = 0; i < n; i++){
        Ride* ride = rides[i]; 
        if(strcmp(get_ride_city(rides[i]),city) == 0){
            Driver *driver = g_hash_table_lookup(db_drivers, get_driver_id(rides[i]));

        }
    }
}

// void answer_q4(FILE* input,char *city,void *db_rides, void *db_drivers){
//     DB_Rides* dbRides = (DB_Rides*) db_rides;
//     GHashTable* dbrides = dbRides->rides_hashtable;
//     DB_Drivers* dbDrivers = (DB_Drivers*) db_drivers;
//     GHashTable* dbdrivers = dbDrivers->drivers_hashtable;
//     double total_price = 0.0;
//     int n_rides = 0;
//     GHashTableIter iter;
//     gpointer key, value;
//     g_hash_table_iter_init(&iter, db_rides);
//     while (g_hash_table_iter_next(&iter, &key, &value)) {
//         Ride *ride = value;
//         if (strcmp(ride_get_city(ride), city) == 0) {
//             Driver *driver = g_hash_table_lookup(db_drivers, get_driver_id(driver));
//             if(driver == NULL) printf("Driver não encontrado\n");
//             if (driver != NULL) {
//                 double price = 0.0;
//             }
//         }
//     }
// }