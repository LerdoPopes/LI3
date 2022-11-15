#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/dates.h"
#include "../Include/drivers.h"

typedef struct driver {
    size_t id;
    char *name;
<<<<<<< HEAD
    short birth_date;
=======
    char birth_date[sizeof("AAAA/MM/DD")];
>>>>>>> e67494dfd7acf79cd7d412f148abc5e60cbd85cc
    char gender;
    char *car_class;
    char license_plate[sizeof("00-00-AA")];
    char *city;
<<<<<<< HEAD
    short account_creation;
    char account_status;
} Driver;

typedef struct data_base_drivers{
    void** drivers_array;
    GHashTable* drivers_hashtable;
    // GTree* drivers_tree;
} DB_drivers;


=======
    char account_creation[sizeof("AAAA/MM/DD")];
    char account_status;
} Driver;

>>>>>>> e67494dfd7acf79cd7d412f148abc5e60cbd85cc
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
<<<<<<< HEAD

void *organize_driver(void* gtablep,void* driverp){
    Driver* driver = (Driver*) driverp;
    if(gtablep == NULL){
        GHashTable* hashtable = g_hash_table_new(g_str_hash,g_str_equal);
        g_hash_table_insert(hashtable,&(driver->id),driver);
        return hashtable;
    }
    GHashTable* gtable = (GHashTable*) gtablep;
    g_hash_table_insert(gtable,&(driver->id),driver);
    return gtable;
}

void *arrange_driver(void* gtable,void** array){
    DB_drivers* db_drivers = malloc(sizeof(DB_drivers));
    db_drivers->drivers_array = array;
    db_drivers->drivers_hashtable = (GHashTable*) gtable;
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
=======
>>>>>>> e67494dfd7acf79cd7d412f148abc5e60cbd85cc
