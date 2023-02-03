#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../Include/users.h"
#include "../Include/dates.h"
#include "../Include/errors.h"

enum method {
    cash = 'a',
    credit_card = 'r',
    debit_card = 'e'
};

struct user{
    char *username;
    char *name;
    char gender;
    unsigned short birth_date;
    short account_creation;
    char account_status;
    short trips;
    double total_spent;
    unsigned short total_dist;
    short aval;
    unsigned short last_trip_date;
};

typedef struct data_base_users{
    User** users_array;
    GHashTable* users_hashtable;
    int len;
    int order;
} DB_users;

void *process_user(char** info) 
{
    if(invalid_date(info[3]) 
       || invalid_date(info[4])
       || empty_error(info[0])
       || empty_error(info[1])
       || empty_error(info[2])
       || invalid_accStats(info[6])
       || empty_error(info[5])
    ){
        return NULL;
    }
    struct user *us = malloc(sizeof(struct user));

    us->username = strdup(info[0]);
    us->name = strdup(info[1]);
    us->gender = *info[2];
    us->birth_date = calc_Date(info[3]);
    us->account_creation = calc_Date(info[4]);
    us->account_status = tolower(info[6][0]);
    us->aval = 0;
    us->total_dist = 0;
    us->total_spent = 0;
    us->trips = 0;
    us->last_trip_date = 0;
    return us;
}

void *organize_user(void** results){
    GHashTable* gtable = g_hash_table_new(g_str_hash,g_str_equal);
    int i;
    for (i = 0; results[i]; i++)
    {
        User* user = (User*) results[i];
        g_hash_table_insert(gtable,user->username,user);  
    }
    DB_users* db_users = malloc(sizeof(DB_users));
    db_users->users_array = (User**) results;
    db_users->users_hashtable = gtable;
    db_users->len=i;
    db_users->order = 0;
    return db_users;
}

void free_user(void* user){
    DB_users* db_users = (DB_users*) user;
    for (size_t i = 0; db_users->users_array[i]; i++)
    {
        User* users = (User*) db_users->users_array[i];
        free(users->username);
        free(users->name);
        free(users);
    }
    GHashTable* gtable = (GHashTable*) db_users->users_hashtable;
    g_hash_table_destroy(gtable);
    free(db_users->users_array);
    free(db_users);
}

void print_user(void* key, void* usersDB){
    DB_users* db_users = (DB_users*) usersDB;
    gconstpointer user_name = (gconstpointer) key;
    gpointer guser = g_hash_table_lookup(db_users->users_hashtable,user_name);
    User* user = (User*) guser;
    printf("%s,%s,%c,%u,%u\n",user->username,user->name,user->gender,user->birth_date,user->account_creation);
}


void set_user_stats(void* dbUsers, void* distp, void* avalp, void* username, void* moneyp ,void* last_tripp){
    DB_users* db_users = (DB_users*) dbUsers;
    gpointer userp = g_hash_table_lookup(db_users->users_hashtable,username);
    User* user = (User*) userp;
    unsigned short* dist = (unsigned short*) distp;
    short* aval = (short*) avalp;
    unsigned short* last_trip = (unsigned short*) last_tripp;
    double* money = (double*) moneyp;
    if(*last_trip>user->last_trip_date){
        user->last_trip_date = *last_trip;
    }
    user->total_dist += *dist;
    user->aval += *aval;
    user->trips++;
    user->total_spent += *money;
}


void *order_by_dist(void *dbUsers)
{
    DB_users *db_users = (DB_users *)dbUsers;
    User **users = db_users->users_array;
    int n = db_users->len;
    if (db_users->order != 1){
        for (int gap = n/2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i += 1)
            {
                User* temp = users[i];
                double media = (double) (temp->aval)/(temp->trips);

                int j;           
                for (j = i; j >= gap 
                && (((users[j - gap]->total_dist)>temp->total_dist) 
                || ((users[j - gap]->total_dist)==temp->total_dist && (users[j - gap]->last_trip_date)>temp->last_trip_date) 
                || ((users[j - gap]->total_dist)==temp->total_dist && (users[j - gap]->last_trip_date)==temp->last_trip_date && (strcmp(users[j - gap]->username,temp->username)<=0))); j -= gap)
                    users[j] = users[j - gap];

                users[j] = temp;
            }
        }
        db_users->order = 1;
    }
}

char* get_n_user(void* data, int i,char* dest, int *size){
   DB_Users* users = (DB_Users*) data;
    while(*size <= strlen(users->users_array[i]->username)){
        dest = realloc(dest,(*size*=2));
     }
    memmove(dest,users->users_array[i]->username,strlen(users->users_array[i]->username)+1);
    dest[strlen(users->users_array[i]->username)] = '\0';
    return dest;
}

int isUser(void* data, char* Username){
    DB_Users* db_users = (DB_Users*) data;
    gconstpointer id = (gconstpointer) Username;
    gpointer userp = g_hash_table_lookup(db_users->users_hashtable,id);
    User* user = (User*) userp;
    return (user != NULL);
}

char *user_get_name(void* user_p, char* ID, char* dest, int* size){
    DB_users* users = (DB_users*) user_p;
    gconstpointer id = (gconstpointer)ID;
    gpointer userp = g_hash_table_lookup(users->users_hashtable, id);
    User* user = (User*) userp;
    while(*size <= strlen(user->name)){
        dest = realloc(dest,(*size*=2));
     }
    memmove(dest,user->name,strlen(user->name)+1);
    dest[strlen(user->name)] = '\0';
    return dest;

}

char user_get_gender(void* user_p, char*ID){
    DB_users* users = (DB_users*) user_p;
    gconstpointer id = (gconstpointer)ID;
    gpointer userp = g_hash_table_lookup(users->users_hashtable, id);
    User* user = (User*) userp;
    char GEnder = user->gender;
    return GEnder;

}

unsigned short user_get_birth_date(void* user_p, char*ID){
    DB_users* users = (DB_users*) user_p;
    gconstpointer id = (gconstpointer)ID;
    gpointer userp = g_hash_table_lookup(users->users_hashtable, id);
    User* user = (User*) userp;
    return user->birth_date;

}

short user_get_account_creation(void *user_p, char*ID){
    DB_users* users = (DB_users*) user_p;
    gconstpointer id = (gconstpointer)ID;
    gpointer userp = g_hash_table_lookup(users->users_hashtable, id);
    User* user = (User*) userp;
    return user->account_creation;
}

char user_get_account_status(void* user_p, char*ID){
    DB_users* users = (DB_users*) user_p;
    gconstpointer id = (gconstpointer)ID;
    gpointer userp = g_hash_table_lookup(users->users_hashtable, id);
    User* user = (User*) userp;
    char Account_Status = user->account_status;
    return Account_Status;
    
}

short user_get_trips(void *user_p, char*ID){
    DB_users* users = (DB_users*) user_p;
    gconstpointer id = (gconstpointer)ID;
    gpointer userp = g_hash_table_lookup(users->users_hashtable, id);
    User* user = (User*) userp;
    return user->trips;
}

double user_get_total_spent(void* user_p, char*ID){
    DB_users* users = (DB_users*) user_p;
    gconstpointer id = (gconstpointer)ID;
    gpointer userp = g_hash_table_lookup(users->users_hashtable, id);
    User *user = (User*) userp;
    return user->total_spent;

}

unsigned short user_get_total_dist(void* user_p, char*ID){
    DB_users* users = (DB_users*) user_p;
    gconstpointer id = (gconstpointer)ID;
    gpointer userp = g_hash_table_lookup(users->users_hashtable, id);
    User* user = (User*) userp;
    return user->total_dist;

}

short user_get_aval(void *user_p, char*ID){
    DB_users* users = (DB_users*) user_p;
    gconstpointer id = (gconstpointer)ID;
    gpointer userp = g_hash_table_lookup(users->users_hashtable, id);
    User* user = (User*) userp;
    return user->aval;
}

double user_get_aval_m(void* data, char* Username){
    DB_Users* db_users = (DB_Users*) data;
    gconstpointer id = (gconstpointer) Username;
    gpointer userp = g_hash_table_lookup(db_users->users_hashtable,id);
    User* user = (User*) userp;
    double aval_m = (double) user->aval/user->trips;
    return aval_m;
}

unsigned short user_get_last_trip_date(void* user_p, char*ID){
    DB_users* users = (DB_users*) user_p;
    gconstpointer id = (gconstpointer)ID;
    gpointer userp = g_hash_table_lookup(users->users_hashtable, id);
    User* user = (User*) userp;
    return user->last_trip_date;

}


int user_get_idade(void* data, char* Username){
    DB_Users* db_users = (DB_Users*) data;
    gconstpointer id = (gconstpointer) Username;
    gpointer userp = g_hash_table_lookup(db_users->users_hashtable,id);
    User* user = (User*) userp;
    return idade(user->birth_date);
}

int get_len_user(void* user_p){
    DB_users* users = (DB_users*) user_p;
    return users->len;
}