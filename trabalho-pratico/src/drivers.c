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
    short total_dist;
    short trips;
    short aval;
    float total_spent;
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
    dr->aval = 0;
    dr->total_dist = 0;
    dr->total_spent = 0;
    dr->trips = 0;
    return dr;
}

void *organize_driver(void** results, void* useless, void* useless2, void(useless3)(void*,void*,void*,void*,void*), void*(useless4)(void*,void*,void*,void*)){
    GHashTable* gtable = g_hash_table_new(g_int_hash,g_int_equal);
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
        free(drivers->city);
        free(drivers->name);
        free(drivers);
    }
    GHashTable* gtable = (GHashTable*) db_drivers->drivers_hashtable;
    g_hash_table_destroy(gtable);
    free(db_drivers);
}

void* set_driver_stats(void* dbDrivers, void* distp, void* avalp, void* id){
    DB_drivers* db_drivers = (DB_drivers*) dbDrivers;
    gconstpointer idp = (gconstpointer) id;
    gpointer driverp = g_hash_table_lookup(db_drivers->drivers_hashtable,idp);
    Driver* driver = (Driver*) driverp;
    short* dist = (short*) distp;
    short* aval = (short*)  avalp;
    driver->total_dist += *dist;
    driver->aval += *aval;
    driver->trips++;
    if(driver->car_class[0] == 'g' || driver->car_class[0] == 'G' ){
        driver->total_spent += (4+0.79*driver->total_dist); 
    }
    else if(driver->car_class[0] == 'p' || driver->car_class[0] == 'P' ){
        driver->total_spent += (5.2+0.94*driver->total_dist);
    }
    else{
        driver->total_spent += (3*0.62*driver->total_dist);
    }
    float* money = malloc(sizeof(float));
    *money = 1;
    return money;
}

void print_driver(void* driversDB){
    DB_drivers* db_drivers = (DB_drivers*) driversDB;
    //gconstpointer id = (gconstpointer) key;
    //gpointer guser = g_hash_table_lookup(db_drivers->drivers_hashtable,id);
    for (size_t i = 0; db_drivers->drivers_array[i]; i++)
    {
        Driver* driver = (Driver*) db_drivers->drivers_array[i];
        printf("%d,%s,%c,%u,%u,%.3f\n",driver->id,driver->name,driver->gender,driver->birth_date,driver->trips,driver->total_spent);
    }
    
    //Driver* driver = (Driver*) guser;
    //printf("%d,%s,%c,%u,%u\n",driver->id,driver->name,driver->gender,driver->birth_date,driver->account_creation);
}