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

void *order_by_dist(void *dbUsers);

char* get_n_user(void* data, int i);

int isUser(void* data, char* Username);

char *user_get_name(void* user_p, char* ID);

char user_get_gender(void* user_p, char* ID);

unsigned short user_get_birth_date(void* user_p, char* ID);

short user_get_account_creation(void *user_p, char* ID);

char user_get_pay_method(void* user_p, char* ID);

char user_get_account_status(void* user_p, char* ID);

short user_get_trips(void *user_p, char* ID);

double user_get_total_spent(void* user_p, char* ID);

double user_get_total_spent_notip(void* user_p, char* ID);

unsigned short user_get_total_dist(void* user_p, char* ID);

short user_get_aval(void *user_p, char* ID);

double user_get_aval_m(void* data, char* Username);

unsigned short user_get_last_trip_date(void* user_p, char* ID);

int user_get_idade(void* data, char* Username);

int get_len_user(void* user_p);

char *user_get_username(void* user_p, char* ID);