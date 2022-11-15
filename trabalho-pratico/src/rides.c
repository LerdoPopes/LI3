#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/rides.h"

typedef struct ride {
    size_t id;
    short date;
    size_t driver; 
    char *user;
    char *city;
    size_t distance;
    size_t score_user;
    size_t score_driver;
    size_t tip;
    char *comment;
} Rides;

typedef struct data_base_rides{
    void** rides_array;
    GHashTable* rides_hashtable;
    // GTree* users_tree;
} DB_rides;

void *process_ride(char* const* info) {
    struct ride *ri = malloc(sizeof(struct ride));

    ri->id = atol(info[0]);
    ri->date = calc_Date(info[1]);
    // memmove(ri->date, info[1], strlen(info[1]));
    ri->driver = atol(info[2]);
    ri->user = strdup(info[3]);
    ri->city = strdup(info[4]);
    ri->distance = atol(info[5]);
    ri->score_user = atol(info[6]);
    ri->score_driver = atol(info[7]);
    ri->tip = atol(info[8]);
    ri->comment = strdup(info[9]);
    return ri;
}

void *organize_rides(void* gtablep,void* ridesp){
    Rides* rides = (Rides*) ridesp;
    if(gtablep == NULL){
        GHashTable* hashtable = g_hash_table_new(g_str_hash,g_str_equal);
        g_hash_table_insert(hashtable,&(rides->id),rides);
        return hashtable;
    }
    GHashTable* gtable = (GHashTable*) gtablep;
    g_hash_table_insert(gtable,&(rides->id),rides);
    return gtable;
}

void *arrange_rides(void* gtable,void** array){
    DB_rides* db_rides = malloc(sizeof(DB_rides));
    db_rides->rides_array = array;
    db_rides->rides_hashtable = (GHashTable*) gtable;
    return db_rides;
}

void free_rides(void* rides){
    DB_rides* db_rides = (DB_rides*) rides;
    for (size_t i = 0; db_rides->rides_array[i]; i++)
    {
        Rides* rides = (Rides*) db_rides->rides_array[i];
        free(rides->user);
        free(rides->city);
        free(rides->comment);
        free(rides);
    }
    GHashTable* gtable = (GHashTable*) db_rides->rides_hashtable;
    g_hash_table_destroy(gtable);
}