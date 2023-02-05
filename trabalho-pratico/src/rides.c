#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <stdarg.h>
#include "../Include/rides.h"
#include "../Include/errors.h"

struct ride {
    int id;
    short date;
    int driver; 
    char *user;
    char *city;
    short distance;
    short score_user;
    short score_driver;
    double tip;
};

typedef struct data_base_rides{
    void** rides_array;
    GHashTable* rides_hashtable;
    int len;
} DB_rides;

 void *process_ride(char** info) {
     if(
        empty_error(info[0])
     || invalid_date(info[1])
     || empty_error(info[2]) 
     || empty_error(info[3])
     || empty_error(info[4])
     || invalid_Pint(info[5])
     || invalid_Pint(info[6])
     || invalid_Pint(info[7])
     || invalid_Pdouble(info[8])
    ){
        return NULL;
    }
    if(atoi(info[5]) == 0 || atoi(info[6]) == 0 || atoi(info[7]) == 0){
        return NULL;
    }
     struct ride *ri = malloc(sizeof(struct ride));
 
     ri->id = atol(info[0]);
     ri->date = calc_Date(info[1]);
     ri->driver = atoi(info[2]);
     ri->user = strdup(info[3]);
     ri->city = strdup(info[4]);
     ri->distance = atoi(info[5]);
     ri->score_user = atoi(info[6]);
     ri->score_driver = atoi(info[7]);
     ri->tip = atof(info[8]);
     return ri;
 }

void *organize_rides(void** results){
    GHashTable* gtable = g_hash_table_new(g_int_hash,g_str_equal);
    int i;
    for (i = 0; results[i]; i++)
    {
        Ride* rides = (Ride*) results[i];
        g_hash_table_insert(gtable,&(rides->id),rides);
    }
    DB_rides* db_rides = malloc(sizeof(DB_rides));
    db_rides->rides_array = results;
    db_rides->rides_hashtable = gtable;
    db_rides->len = i;
    return db_rides;
}

void free_rides(void* rides){
    DB_rides* db_rides = (DB_rides*) rides;
    for (size_t i = 0; db_rides->rides_array[i]; i++)
    {
        Ride* rides = (Ride*) db_rides->rides_array[i];
        free(rides->user);
        free(rides->city);
        free(rides);
    }
    GHashTable* gtable = (GHashTable*) db_rides->rides_hashtable;
    g_hash_table_destroy(gtable);
    free(db_rides->rides_array);
    free(db_rides);
}

int ride_get_driver(void *ride_p, int ID){
    DB_rides* rides = (DB_rides*) ride_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer ridep = g_hash_table_lookup(rides->rides_hashtable, id);
    Ride* ride = (Ride*) ridep;
    return ride->driver;
}

char *ride_get_user(void *ride_p, int ID, char* dest,int* size){
    DB_rides* rides = (DB_rides*) ride_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer ridep = g_hash_table_lookup(rides->rides_hashtable, id);
    Ride* ride = (Ride*) ridep;
    while(*size <= strlen(ride->user)){
        dest = realloc(dest,(*size*=2));
    }
    memmove(dest,ride->user,strlen(ride->user)+1);
    dest[strlen(ride->user)] = '\0';
    return dest;
}

char *ride_get_city(void *ride_p, int ID,char* dest, int* size){
    DB_rides* rides = (DB_rides*) ride_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer ridep = g_hash_table_lookup(rides->rides_hashtable, id);
    Ride* ride = (Ride*) ridep;
    while(*size <= strlen(ride->city)){
        dest = realloc(dest,(*size*=2));
    }
    memmove(dest,ride->city,strlen(ride->city)+1);
    dest[strlen(ride->city)] = '\0';
    return dest;
}

short ride_get_distance(void *ride_p,int ID){
    DB_rides* rides = (DB_rides*) ride_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer ridep = g_hash_table_lookup(rides->rides_hashtable, id);
    Ride* ride = (Ride*) ridep;
    return ride->distance;
}

short ride_get_score_user(void *ride_p, int ID){
    DB_rides* rides = (DB_rides*) ride_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer ridep = g_hash_table_lookup(rides->rides_hashtable, id);
    Ride* ride = (Ride*) ridep;
    return ride->score_user;
}

short ride_get_score_driver(void *ride_p, int ID){
    DB_rides* rides = (DB_rides*) ride_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer ridep = g_hash_table_lookup(rides->rides_hashtable, id);
    Ride* ride = (Ride*) ridep;
    return ride->score_driver;
}

double ride_get_tip(void *ride_p, int ID){    
    DB_rides* rides = (DB_rides*) ride_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer ridep = g_hash_table_lookup(rides->rides_hashtable, id);
    Ride* ride = (Ride*) ridep;
    return ride->tip;
}

int get_len_ride(void* ride_p){
    DB_rides* rides = (DB_rides*) ride_p;
    return rides->len;
}

int ride_get_idArray(void *ride_p, int i){
    DB_rides* rides = (DB_rides*) ride_p;
    Ride* ride = (Ride*) rides->rides_array[i];
    return ride->id;
}

short ride_get_date(void* rides_p, int Id){
   DB_rides* rides = (DB_rides*) rides_p;
   gconstpointer id = (gconstpointer)&Id;
   gpointer ridep = g_hash_table_lookup(rides->rides_hashtable, id);
   Ride* ride = (Ride*) ridep;
   return ride->date;
}

int isRide(void* ride_p, int ID){
    DB_rides* rides = (DB_rides*) ride_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(rides->rides_hashtable, id);
    Ride *driver = (Ride*) driverp;
    return (driver != NULL);
}
