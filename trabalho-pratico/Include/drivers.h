#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void *process_driver(char* const* info); 

void *organize_driver(void** results);

void free_driver(void* driver);

typedef struct driver Driver;

int driver_get_id(struct driver *d);

char *driver_get_name(struct driver *d);

char driver_get_birth_date(struct driver *d);

char driver_get_gender(struct driver *d);

char *driver_get_car_class(struct driver *d);

char *driver_get_license_plate(struct driver *d);

char *driver_get_city(struct driver *d);

short driver_get_account_creation(struct driver *d);

char driver_get_account_status(struct driver *d);

short driver_get_idade(struct driver *d,char *data_atual,char *birth_date);