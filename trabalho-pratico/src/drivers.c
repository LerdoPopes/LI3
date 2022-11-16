#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/dates.h"
#include "../Include/drivers.h"

typedef struct driver {
    int id;
    char *name;
    short birth_date;
    char gender;
    char *car_class;
    char license_plate[sizeof("00-00-AA")];
    char *city;
    short account_creation;
    char account_status;
} Driver;

typedef struct data_base_drivers{
    void** drivers_array;
    GHashTable* drivers_hashtable;
    // GTree* drivers_tree;
} DB_drivers;

void *process_driver(char* const* info) {
    struct driver *dr = malloc(sizeof(struct driver));

    dr->id = atol(info[0]);
    dr->name = strdup(info[1]);
    dr->birth_date = calc_Date(info[2]);
    // memmove(dr->birth_date, info[2], size);
    dr->gender = *info[3];
    dr->car_class = strdup(info[4]);
    memmove(dr->license_plate, info[5], strlen(info[5]));
    dr->city = strdup(info[6]);
    dr->account_creation = calc_Date(info[7]);
    // memmove(dr->account_creation, info[7], size);
    dr->account_status = info[8][0];
    return dr;
}

void *organize_driver(void** results){
    GHashTable* gtable = g_hash_table_new(g_int_hash,g_str_equal);
    for (size_t i = 0; results[i]; i++)
    {
        Driver* driver = (Driver*) results[i];
        g_hash_table_insert(gtable,&(driver->id),driver);
    }
    DB_drivers* db_drivers = malloc(sizeof(DB_drivers));
    db_drivers->drivers_array = results;
    db_drivers->drivers_hashtable = gtable;
    return db_drivers;
}

void free_driver(void* driver){
    DB_drivers* db_drivers = (DB_drivers*) driver;
    for (size_t i = 0; db_drivers->drivers_array[i]; i++)
    {
        Driver* drivers = (Driver*) db_drivers->drivers_array[i];
        free(drivers->car_class);
        // free(drivers->license_plate);
        free(drivers->city);
        free(drivers->name);
        free(drivers);
    }
    GHashTable* gtable = (GHashTable*) db_drivers->drivers_hashtable;
    g_hash_table_destroy(gtable);
}
