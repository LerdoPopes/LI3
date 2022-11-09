#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct user {
    char *username;
    char *name;
    char gender;
    char birth_date[sizeof("AAAA/MM/DD")];
    char account_creation[sizeof("AAAA/MM/DD")];
    // enum method pay_method;
    // enum status account_status;
} User;

void *process_user(char* const* info);