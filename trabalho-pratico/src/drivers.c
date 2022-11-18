#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/dates.h"
#include "../Include/drivers.h"

typedef struct driver{
    int id;
    char *name;
    short birth_date;
    char gender;
    char *car_class;
    char license_plate[sizeof("00-00-AA")];
    char *city;
    short account_creation;
    char account_status;
    short idade;
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

int driver_get_id(struct driver *d){
    return d->id;
}

char *driver_get_name(struct driver *d){
     char *nome = (char *)malloc(255 * sizeof(char));
     strcpy(nome,d->name);    
     return nome;
}

char driver_get_birth_date(struct driver *d){
    return d->birth_date;
}

char driver_get_gender(struct driver *d){
    return d->gender;
}

char *driver_get_car_class(struct driver *d){
     char *classe = (char *)malloc(255 * sizeof(char));
     strcpy(classe,d->car_class);    
     return classe;
}

char driver_get_license_plate(struct driver *d){
    return d->license_plate;
}

char *driver_get_city(struct driver *d){
     char *cidade = (char *)malloc(255 * sizeof(char));
     strcpy(cidade,d->city);    
     return cidade;
}

short driver_get_account_creation(struct driver *d) {
    return d->account_creation;
}

char driver_get_account_status(struct driver *d) {
    return d->account_status;
}


char *get_name_driver(void *hash_drivers, const void *key){
    GHashTable* gtable = (GHashTable*) hash_drivers;
    struct driver *driver = g_hash_table_lookup(gtable,key);
    char *nome = (char *)malloc(255 * sizeof(char));
    strcpy(nome,driver->name);
    return nome;
}

short get_birth_date_driver(void *hash_drivers, const void *key){
    GHashTable* gtable = (GHashTable*) hash_drivers;
    struct driver *driver = g_hash_table_lookup(gtable,key);
    return driver->birth_date;
}

char get_gender_driver(void *hash_drivers, const void *key){
    GHashTable* gtable = (GHashTable*) hash_drivers;
    struct driver *driver = g_hash_table_lookup(gtable,key);
    return driver->gender;    
}

short get_idade_driver(void *hash_drivers, const void *key,char *data_atual,char *birth_date){
    GHashTable* gtable = (GHashTable*) hash_drivers;
    struct driver *driver = g_hash_table_lookup(gtable,key);
    driver->idade = idade(data_atual,birth_date);
    return driver->idade;
}

char get_account_status_driver(void *hash_drivers, const void *key){
    GHashTable* gtable = (GHashTable*) hash_drivers;
    struct driver *driver = g_hash_table_lookup(gtable,key);
    return driver->account_status;
}