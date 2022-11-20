#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/dates.h"
#include "../Include/drivers.h"

struct driver{
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
    short aval_m;
    short last_trip_date;
} ;


struct data_base_drivers{
    void** drivers_array;
    GHashTable* drivers_hashtable;
    // GTree* drivers_tree;
};

void *process_driver(char** info) {
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
    dr->aval_m = 0;
    dr->last_trip_date = 0;
    return dr;
}

void *organize_driver(void** results, void* useless, void* useless2, void(useless3)(void*,void*,void*,void*,void*,void*), void*(useless4)(void*,void*,void*,void*,void*,void*)){
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

void* set_driver_stats(void* dbDrivers, void* distp, void* avalp, void* id, void* tips, void* last_tripp){
    DB_drivers* db_drivers = (DB_drivers*) dbDrivers;
    gconstpointer idp = (gconstpointer) id;
    gpointer driverp = g_hash_table_lookup(db_drivers->drivers_hashtable,idp);
    Driver* driver = (Driver*) driverp;
    short* dist = (short*) distp;
    short* aval = (short*)  avalp;
    short* last_trip = (short*) last_tripp;
    driver->total_dist += *dist;
    driver->aval += *aval;
    driver->trips++;
    if(*last_trip>driver->last_trip_date){
        driver->last_trip_date = *last_trip;
    }
    float* tip = (float*) tips;
    float* money = malloc(sizeof(float));
    if(driver->car_class[0] == 'g' || driver->car_class[0] == 'G' ){
        driver->total_spent += (4+0.79*(*dist)+(*tip)); 
        *money = (4+0.79*(*dist)+(*tip));
    }
    else if(driver->car_class[0] == 'p' || driver->car_class[0] == 'P' ){
        driver->total_spent += (5.2+0.94*(*dist)+(*tip));
        *money = (5.2+0.94*(*dist)+(*tip));
    }
    else{
        driver->total_spent += (3.25*0.62*(*dist)+(*tip));
        *money = (3.25+0.62*(*dist)+(*tip));
    }
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

char *driver_get_license_plate(struct driver *d){
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

void *answer_q1_driver(FILE *output,void *dbDrivers, char *ID){
    int Id = atoi(ID);
    DB_drivers* db_drivers = (DB_drivers*) dbDrivers;
    gconstpointer id = (gconstpointer) &Id;
    gpointer driverp = g_hash_table_lookup(db_drivers->drivers_hashtable,id);
    Driver* driver = (Driver*) driverp;
    printf("%p",driver);
    short Idade = idade(driver->birth_date);
    double media = (driver->aval)/(driver->trips);
    if(driver->account_status = 'a'){
        fprintf(output,"%s;%c;%d;%.3f;%d;%.3f\n",driver->name,driver->gender,Idade,media,driver->trips,driver->total_spent);//avaliacao_media,numero_viagens,total_gasto);    
    }
    fclose(output);     
}

// short driver_get_idade(struct driver *d,char *data_atual,char *birth_date){
//      d->idade = idade(data_atual,birth_date);
//      return d->idade;
// }


