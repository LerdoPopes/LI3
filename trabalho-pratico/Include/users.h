#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void *process_user(char* const* info);

void *organize_user(void** user);

void free_user(void* user);

void print_user(char* key, void* usersDB);