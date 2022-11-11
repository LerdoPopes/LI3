//enum status{
//    active = 'a', 
//    inactive = 'i'
//};

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct driver {
    size_t id;
    char *name;
    char birth_date[sizeof("AAAA/MM/DD")];
    char gender;
    char *car_class;
    char license_plate[sizeof("00-00-AA")];
    char *city;
    char account_creation[sizeof("AAAA/MM/DD")];
    char account_status;
} Driver;

void *process_driver(char* const* info); 

// int is_active(char* const* info);

// char *set_account_status(int dr,const void* info);

