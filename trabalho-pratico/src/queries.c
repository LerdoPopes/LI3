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

void* process_query(char** save){
    char** save2 = malloc(12*sizeof(char*));
    size_t i = 0;
    for(; save[i]; i++)
    {
        save2[i] = strdup(save[i]);
    }
    save2[i] = NULL;
    return save2;
}

void free_queries(void** queries_p){
    char*** queries = (char***) queries_p;
    for(int i = 0; queries[i] != NULL;i++){
        for (size_t j = 0; queries[i][j] != NULL ; j++)
        {
            free(queries[i][j]);
        }
        
        free(queries[i]);
    }
    free(queries);
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
        int id = atoi(ID);
        if(isDriver(dbDrivers,id))
        {
            if (driver_get_accStats(dbDrivers,id) == 'a' && driver_get_trips(dbDrivers,id) != 0)
            {
                fprintf(resultado, "%s;%c;%d;%.3f;%d;%.3f\n", driver_get_name(dbDrivers,id), driver_get_gender(dbDrivers,id), driver_get_idade(dbDrivers,id), driver_get_avalm(dbDrivers,id), driver_get_trips(dbDrivers,id), driver_get_totalSpent(dbDrivers,id));
            }
            else if (driver_get_accStats(dbDrivers,id) == 'a' && driver_get_trips(dbDrivers,id) == 0)
            {
                fprintf(resultado, "%s;%c;%d;%d;%d;%d\n", driver_get_name(dbDrivers,id), driver_get_gender(dbDrivers,id), driver_get_idade(dbDrivers,id), 0, 0, 0);
            }
        }
    }







    else{
        if(isUser(dbUsers,ID)){
            char* user = user_get_name(dbUsers,ID);
            if(user_get_accStatus(dbUsers,user) == 'a' && user_get_trips(dbUsers,user) != 0){
                fprintf(resultado,"%s;%c;%d;%.3f;%d;%.3f\n",user,user_get_gender(dbUsers,ID),user_get_idade(dbUsers,ID),user_get_avalm(dbUsers,ID),user_get_trips(dbUsers,ID),user_get_totalspent(dbUsers,ID));
            }
            else if(user_get_accStatus(dbUsers,user) == 'a' && user_get_trips(dbUsers,user) == 0){
                fprintf(resultado,"%s;%c;%d;%d;%d;%d\n",user,user_get_gender(dbUsers,ID),user_get_idade(dbUsers,ID),0,0,0);
            } 
        }
    }
    fclose(resultado);
}

void query2(char* N, void *dbDrivers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");   
    int n = atoi(N);
    int len = get_len_driver(dbDrivers);
    order_by_aval(dbDrivers);
    for (size_t i = len-1; i>len-n-1; i--)
    {
        int id = get_n_id(dbDrivers,i);
        if(user_get_accStatus(dbDrivers,id) != 'a'){
            n++;
        }
        else{
            fprintf(resultado,"%d;%s;%d\n",id,driver_get_name(dbDrivers,id),get_driver_avalm(dbDrivers,id));
        }        
    }
    fclose(resultado);
}


void query3(char *Num, void *dbUsers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");
    int n = atoi(Num);
    int len = get_len_user(dbUsers);
    order_by_dist(dbUsers);
    for (size_t i = len-1; i>len-n-1; i--)
    {
        char* User = get_n_username(dbUsers,i);
        if(user_get_accStatus(dbUsers,User) != 'a'){
            n++;
        }
        else{
            fprintf(resultado,"%s;%s;%d\n",User,user_get_name(dbUsers,User),get_user_totalDist(dbUsers,User));
        }        
    }
    fclose(resultado);
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