#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/rides.h"

typedef struct ride {
    int id;
    short date;
    int driver; 
    char *user;
    char *city;
    short distance;
    short score_user;
    short score_driver;
    float tip;
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

void *organize_rides(void** results, void* struct_drivers, void* struct_users, void(set_users_stats)(void*,void*,void*,void*,void*), void*(set_driver_stats)(void*,void*,void*,void*)){
    GHashTable* gtable = g_hash_table_new(g_int_hash,g_str_equal);
    for (size_t i = 0; results[i]; i++)
    {
        Rides* rides = (Rides*) results[i];
        short dist = rides->distance;
        short score_u = rides->score_user;
        short score_d = rides->score_driver;
        int id = rides->driver;
        char* username = strdup(rides->user);
        void* money = set_driver_stats(struct_drivers,&dist,&score_d,&id);
        set_users_stats(struct_users,&dist,&score_u,username,money);
        free(money);
        free(username);
        g_hash_table_insert(gtable,&(rides->id),rides);
    }
    DB_rides* db_rides = malloc(sizeof(DB_rides));
    db_rides->rides_array = results;
    db_rides->rides_hashtable = gtable;
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