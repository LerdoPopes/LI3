#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/rides.h"

struct ride {
    int id;
    short date;
    size_t driver; 
    char *user;
    char *city;
    size_t distance;
    size_t score_user;
    size_t score_driver;
    size_t tip;
    char *comment;
};

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

void *organize_rides(void** results){
    GHashTable* gtable = g_hash_table_new(g_int_hash,g_str_equal);
    for (size_t i = 0; results[i]; i++)
    {
        Ride* rides = (Ride*) results[i];
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
        Ride* rides = (Ride*) db_rides->rides_array[i];
        free(rides->user);
        free(rides->city);
        free(rides->comment);
        free(rides);
    }
    GHashTable* gtable = (GHashTable*) db_rides->rides_hashtable;
    g_hash_table_destroy(gtable);
}

int ride_get_id(struct ride *r){
    return r->id;
}

short ride_get_date(struct ride *r){
    return r->date;
}

size_t ride_get_driver(struct ride *r){
    return r->driver;
}

char *ride_get_user(struct ride *r){
     char *User = (char *)malloc(255 * sizeof(char));
     strcpy(User,r->user);    
     return User;
}

char *ride_get_city(struct ride *r){
     char *cidade = (char *)malloc(255 * sizeof(char));
     strcpy(cidade,r->city);    
     return cidade;
}
size_t ride_get_distance(struct ride *r){
    return r->distance;
}

size_t ride_get_score_user(struct ride *r){
    return r->score_user;
}

size_t ride_get_score_driver(struct ride *r){
    return r->score_driver;
}

size_t ride_get_tip(struct ride *r){
    return r->tip;
}

char *ride_get_comment(struct ride *r){
     char *comentario = (char *)malloc(255 * sizeof(char));
     strcpy(comentario,r->comment);    
     return comentario;
}