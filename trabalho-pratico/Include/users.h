enum method {
    cash = 'a',
    credit_card = 'r',
    debit_card = 'e'
};

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
    enum method pay_method;
    char account_status;
} User;

void *process_user(char* const* info);