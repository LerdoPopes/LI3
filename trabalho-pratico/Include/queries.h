#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void query1(char *ID, void *dbDrivers, void *dbUsers, short i);

void query2(char *N, void *dbDrivers, short i);

void query3(char *ID, void *dbUsers, short i);

void* process_querie(char** info);

void* organize_querie(void** results, void* struct_drivers, void* struct_users, void(set_users_stats)(void*,void*,void*,void*,void*), void*(set_driver_stats)(void*,void*,void*,void*));

void print_queries(void* db_queries);
