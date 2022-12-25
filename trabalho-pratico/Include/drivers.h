#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct driver Driver;

typedef struct data_base_drivers DB_drivers; 

void *process_driver(char** info); 

void *organize_driver(void** results, int num_args, ...);

void free_driver(void* driver);

void* set_driver_stats(void* dbDrivers, void* dist, void* aval, void* id, void* tips, void* last_trip);

void print_driver(void* driversDB);

void *answer_q1_driver(FILE *output,void *dbDrivers, char *ID);

void *answer_q2_driver(FILE *output,void *dbDrivers, short N);

int comparador(const void *a, const void *b);

