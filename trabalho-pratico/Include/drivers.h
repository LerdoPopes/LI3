#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct driver Driver;

typedef struct data_base_drivers DB_drivers; 

void *process_driver(char* const* info); 

void *organize_driver(void** results, void* useless, void* useless2, void(useless3)(void*,void*,void*,void*,void*), void*(useless4)(void*,void*,void*,void*));

void free_driver(void* driver);

void* set_driver_stats(void* dbDrivers, void* dist, void* aval, void* id);

void print_driver(void* driversDB);

int driver_get_id(struct driver *d);

char *driver_get_name(struct driver *d);

char driver_get_birth_date(struct driver *d);

char driver_get_gender(struct driver *d);

char *driver_get_car_class(struct driver *d);

char *driver_get_license_plate(struct driver *d);

char *driver_get_city(struct driver *d);

short driver_get_account_creation(struct driver *d);

char driver_get_account_status(struct driver *d);

// short driver_get_idade(struct driver *d,char *data_atual,char *birth_date);

void *answer_q1_driver(FILE *output,void *dbDrivers, char *ID);


