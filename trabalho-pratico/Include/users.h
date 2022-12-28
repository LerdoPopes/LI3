#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <stdarg.h>

typedef struct user User;

typedef struct data_base_users DB_Users;

void *process_user(char** info);

void *organize_user(void** results);

void free_user(void* user);

void print_user(void* key, void* usersDB);

void set_user_stats(void* dbUsers, void* dist, void* aval, void* username, void* money ,void* last_trip);

void *answer_q1_user(FILE *output,void *dbUsers, char *ID);

void *answer_q3_user(FILE *output, void *dbUsers, short N);
