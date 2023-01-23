#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <stdarg.h>
#include "../Include/dates.h"
#include "../Include/drivers.h"
#include "../Include/errors.h"

struct driver
{
    int id;
    char *name;
    unsigned short birth_date;
    char gender;
    char *car_class;
    char license_plate[sizeof("00-00-AA")];
    char *city;
    unsigned short account_creation;
    char account_status;
    int total_dist;
    unsigned short trips;
    unsigned short aval;
    double total_spent;
    double aval_m;
    unsigned short last_trip_date;
};

struct data_base_drivers
{
    Driver **drivers_array;
    GHashTable *drivers_hashtable;
    int order;
    int len;
};

void *process_driver(char **info)
{
    if(
        empty_error(info[0])
    && empty_error(info[1]) 
    && invalid_date(info[2])
    && empty_error(info[3])
    && invalid_carClass(info[4])
    && empty_error(info[5])
    && empty_error(info[6])
    && invalid_date(info[7])
    )
    {
        return NULL;
    }
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

void *organize_driver(void **results)
{
    GHashTable *gtable = g_hash_table_new(g_int_hash, g_int_equal);
    int i;
    for (i = 0; results[i]; i++)
    {
        Driver *driver = (Driver *)results[i];
        g_hash_table_insert(gtable, &(driver->id), driver);
    }
    DB_drivers *db_drivers = malloc(sizeof(DB_drivers));
    db_drivers->drivers_array = (Driver**)results;
    db_drivers->drivers_hashtable = gtable;
    db_drivers->order = 0;
    db_drivers->len = i;
    return db_drivers;
}

void free_driver(void *driver)
{
    DB_drivers *db_drivers = (DB_drivers *)driver;
    for (size_t i = 0; db_drivers->drivers_array[i]; i++)
    {
        Driver *drivers = (Driver *)db_drivers->drivers_array[i];
        free(drivers->car_class);
        free(drivers->city);
        free(drivers->name);
        free(drivers);
    }
    GHashTable *gtable = (GHashTable *)db_drivers->drivers_hashtable;
    g_hash_table_destroy(gtable);
    free(db_drivers->drivers_array);
    free(db_drivers);
}

void *set_driver_stats(void *dbDrivers, void *distp, void *avalp, void *id, void *tips, void *last_tripp)
{
    DB_drivers *db_drivers = (DB_drivers *)dbDrivers;
    gconstpointer idp = (gconstpointer)id;
    gpointer driverp = g_hash_table_lookup(db_drivers->drivers_hashtable, idp);
    Driver *driver = (Driver *)driverp;
    unsigned short *dist = (unsigned short *)distp;
    unsigned short *aval = (unsigned short *)avalp;
    unsigned short *last_trip = (unsigned short *)last_tripp;
    driver->total_dist += *dist;
    driver->aval += *aval;
    driver->trips++;
    if (*last_trip > driver->last_trip_date)
    {
        driver->last_trip_date = *last_trip;
    }
    double *tip = (double *)tips;
    double *money = malloc(sizeof(double));
    if (driver->car_class[0] == 'g' || driver->car_class[0] == 'G')
    {
        driver->total_spent += (4 + 0.79 * (*dist) + (*tip));
        *money = (4 + 0.79 * (*dist) + (*tip));
    }
    else if (driver->car_class[0] == 'p' || driver->car_class[0] == 'P')
    {
        driver->total_spent += (5.2 + 0.94 * (*dist) + (*tip));
        *money = (5.2 + 0.94 * (*dist) + (*tip));
    }
    else
    {
        driver->total_spent += (3.25 + 0.62 * (*dist) + (*tip));
        *money = (3.25 + 0.62 * (*dist) + (*tip));
    }
    return money;
}

void print_driver(void *driversDB)
{
    DB_drivers *db_drivers = (DB_drivers *)driversDB;
    // gconstpointer id = (gconstpointer) key;
    // gpointer guser = g_hash_table_lookup(db_drivers->drivers_hashtable,id);
    for (size_t i = 0; db_drivers->drivers_array[i]; i++)
    {
        Driver *driver = (Driver *)db_drivers->drivers_array[i];
        printf("%d,%s,%c,%u,%u,%.3f\n", driver->id, driver->name, driver->gender, driver->birth_date, driver->trips, driver->total_spent);
    }

    // Driver* driver = (Driver*) guser;
    // printf("%d,%s,%c,%u,%u\n",driver->id,driver->name,driver->gender,driver->birth_date,driver->account_creation);
}

void *answer_q1_driver(FILE *output, void *dbDrivers, char *ID)
{
    int Id = atoi(ID);
    DB_drivers *db_drivers = (DB_drivers *)dbDrivers;
    gconstpointer id = (gconstpointer)&Id;
    gpointer driverp = g_hash_table_lookup(db_drivers->drivers_hashtable, id);
    Driver *driver = (Driver *)driverp;
    if (driver)
    {
        unsigned short Idade = idade(driver->birth_date);
        double media = (double)(driver->aval) / (driver->trips);
        if (driver->account_status == 'a' && driver->trips != 0)
        {
            fprintf(output, "%s;%c;%d;%.3f;%d;%.3f\n", driver->name, driver->gender, Idade, media, driver->trips, driver->total_spent);
        }
        else if (driver->account_status == 'a' && driver->trips == 0)
        {
            fprintf(output, "%s;%c;%d;%d;%d;%d\n", driver->name, driver->gender, Idade, 0, driver->trips, 0);
        }
    }
    fclose(output);
}

void *order_by_aval(void *dbDrivers)
{
    DB_drivers *db_drivers = (DB_drivers *)dbDrivers;
    Driver **drivers = db_drivers->drivers_array;
    // qsort(drivers, 10000, sizeof(Driver *), comparador);
    int n = db_drivers->len;
    if (db_drivers->order != 1){
        for (int gap = n/2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i += 1)
            {
                Driver* temp = drivers[i];
                double media = (double) (temp->aval)/(temp->trips);

                int j;           
                for (j = i; j >= gap && ((double)(drivers[j - gap]->aval)/(drivers[j - gap]->trips)>media || ((double)(drivers[j - gap]->aval)/(drivers[j - gap]->trips)==media && (drivers[j - gap]->last_trip_date)>temp->last_trip_date)); j -= gap)
                    drivers[j] = drivers[j - gap];

                drivers[j] = temp;
            }
        }
        db_drivers->order = 1;
    }
}


//struct driver
//{
//    int id;
//    char *name;
//    unsigned short birth_date;
//    char gender;
//    char *car_class;
//    char license_plate[sizeof("00-00-AA")];
//    char *city;
//    unsigned short account_creation;
//    char account_status;
//    int total_dist;
//    unsigned short trips;
//    unsigned short aval;
//    double total_spent;
//    double aval_m;
//    unsigned short last_trip_date;
//};

int driver_get_len(void* driver_p){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    return drivers->len;
}

int get_n_driver(void* data, int i){
   DB_drivers* drivers = (DB_drivers*) data;
   int id = drivers->drivers_array[i]->id;
   return id;

}

char *driver_get_name(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver* driver = (Driver*) driverp;
    char *Name = strdup(driver->name);
    return Name;

}

unsigned short driver_get_birth_date(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver* driver = (Driver*) driverp;
    return driver->birth_date;

}



char driver_get_gender(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver* driver = (Driver*) driverp;
    char Gender = driver->gender;
    return Gender;

}

char *driver_get_car_class(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver* driver = (Driver*) driverp;
    char *Car_Class = strdup(driver->car_class);
    return Car_Class;

}

char* driver_get_license_plate(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver* driver = (Driver*) driverp;
    char* License_plate = strdup(driver->license_plate);
    return License_plate;

}

char *driver_get_city(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver* driver = (Driver*) driverp;
    char *City = strdup(driver->city);
    return City;

}

unsigned short driver_get_account_creation(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver* driver = (Driver*) driverp;
    return driver->account_creation;

}




char driver_get_account_status(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver* driver = (Driver*) driverp;
    char Account_Status = driver->account_status;
    return Account_Status;
    
}

int driver_get_total_dist(void *driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver *driver = (Driver*) driverp;
    return driver->total_dist;

}

unsigned short driver_get_trips(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver* driver = (Driver*) driverp;
    return driver->trips;

}

unsigned short driver_get_aval(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver* driver = (Driver*) driverp;
    return driver->aval;

}

double driver_get_total_spent(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver *driver = (Driver*) driverp;
    return driver->total_spent;

}


double driver_get_aval_m(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver *driver = (Driver*) driverp;
    double aval_m = (double) driver->aval/driver->trips;
    return aval_m;

}

unsigned short last_trip_date(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver* driver = (Driver*) driverp;
    return driver->last_trip_date;

}

int driver_get_idade(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver *driver = (Driver*) driverp;
    return idade(driver->birth_date);

}

int isDriver(void* driver_p, int ID){
    DB_drivers* drivers = (DB_drivers*) driver_p;
    gconstpointer id = (gconstpointer)&ID;
    gpointer driverp = g_hash_table_lookup(drivers->drivers_hashtable, id);
    Driver *driver = (Driver*) driverp;
    return (driver != NULL);

}

