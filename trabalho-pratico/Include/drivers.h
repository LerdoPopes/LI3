#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct driver Driver;

typedef struct data_base_drivers DB_drivers; 

void *process_driver(char** info); 

void *organize_driver(void** results);

void free_driver(void* driver);

double set_driver_stats(void* dbDrivers, void* dist, void* aval, void* id, void* tips, void* last_trip);

void print_driver(void* driversDB);

void *order_by_aval(void *dbDrivers);

int driver_get_len(void* driver_p);

int get_n_driver(void* data, int i);

char *driver_get_name(void* driver_p, int ID);

unsigned short driver_get_birth_date(void* driver_p, int ID);

char driver_get_gender(void* driver_p, int ID);

char *driver_get_car_class(void* driver_p, int ID);

char* driver_get_license_plate(void* driver_p, int ID);

char *driver_get_city(void* driver_p, int ID);

unsigned short driver_get_account_creation(void* driver_p, int ID);

char driver_get_account_status(void* driver_p, int ID);

int driver_get_total_dist(void *driver_p, int ID);

unsigned short driver_get_trips(void* driver_p, int ID);

unsigned short driver_get_aval(void* driver_p, int ID);

double driver_get_total_spent(void* driver_p, int ID);

double driver_get_aval_m(void* driver_p, int ID);

unsigned short last_trip_date(void* driver_p, int ID);

int isDriver(void* driver_p, int id);

int driver_get_idade(void* driver_p, int id);