#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <stdarg.h>
#include "../Include/rides.h"

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
    char *comment;
};

typedef struct data_base_rides{
    void** rides_array;
    GHashTable* rides_hashtable;
    int len;
} DB_rides;

void *process_ride(char** info) {
    struct ride *ri = malloc(sizeof(struct ride));

    ri->id = atol(info[0]);
    ri->date = calc_Date(info[1]);
    // memmove(ri->date, info[1], strlen(info[1]));
    ri->driver = atoi(info[2]);
    ri->user = strdup(info[3]);
    ri->city = strdup(info[4]);
    ri->distance = atoi(info[5]);
    ri->score_user = atoi(info[6]);
    ri->score_driver = atoi(info[7]);
    ri->tip = atof(info[8]);
    ri->comment = strdup(info[9]);
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
        free(rides->comment);
        free(rides);
    }
    GHashTable* gtable = (GHashTable*) db_rides->rides_hashtable;
    g_hash_table_destroy(gtable);
    free(db_rides->rides_array);
    free(db_rides);
}

short ride_get_date(void* rides_p, int Id){
    DB_rides* rides = (DB_rides*) rides_p;
    gconstpointer id = (gconstpointer)&Id;
    gpointer ridep = g_hash_table_lookup(rides->rides_hashtable, id);
    Ride* ride = (Ride*) ridep;
    return ride->date;
}

int ride_get_driver(void *ride_p, int ID){
    DB_rides* rides = (DB_rides*) ride_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer ridep = g_hash_table_lookup(rides->rides_hashtable, id);
    Ride* ride = (Ride*) ridep;
    return ride->driver;
}

char *ride_get_user(void *ride_p, int ID){
    DB_rides* rides = (DB_rides*) ride_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer ridep = g_hash_table_lookup(rides->rides_hashtable, id);
    Ride* ride = (Ride*) ridep;
    char *User = strdup(ride->user);    
    return User;
}

char *ride_get_city(void *ride_p, int ID){
    DB_rides* rides = (DB_rides*) ride_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer ridep = g_hash_table_lookup(rides->rides_hashtable, id);
    Ride* ride = (Ride*) ridep;
    char *City = strdup(ride->city);    
    return City;
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

