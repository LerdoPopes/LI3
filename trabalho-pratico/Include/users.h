#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void *process_user(char* const* info);

void *organize_user(void** user);

void free_user(void* user);

void print_user(char* key, void* usersDB);

typedef struct user User;

char *user_get_username(struct user *u);

char *user_get_name(struct user *u);

char user_get_gender(struct user *u);

char user_get_birth_date(struct user *u);

short user_get_account_creation(struct user *u);

char user_get_account_status(struct user *u);

short user_get_idade(struct user *u,char *data_atual,char *birth_date);






