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

void *order_by_dist(void *dbUsers);

int get_len_user(void* user_p);

char* get_n_user(void* data, int i);

double user_get_avalm(void* data, char* Username);

int  user_get_idade(void* data, char* Username);

int isUser(void* data, char* Username);