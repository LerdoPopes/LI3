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

void* set_driver_stats(void* dbDrivers, void* dist, void* aval, void* id, void* tips, void* last_trip);

void print_driver(void* driversDB);

void *answer_q1_driver(FILE *output,void *dbDrivers, char *ID);

void *order_by_aval(void *dbDrivers);

int get_n_driver(void* data, int i);

double driver_get_avalm(void* driver_p, int id);

int driver_get_idade(void* driver_p, int id);

int isDriver(void* driver_p, int id);