#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void* process_querie(char* const* info);

void* organize_querie(void** results, void* struct_drivers, void* struct_users, void(set_users_stats)(void*,void*,void*,void*,void*), void*(set_driver_stats)(void*,void*,void*,void*)){

void query1(char *ID, void *hash_drivers);