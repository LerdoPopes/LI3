#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../Include/users.h"
#include "../Include/dates.h"

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
    enum method pay_method;
    char account_status;
    short trips;
    double total_spent;
    double total_spent_notip;
    unsigned short total_dist;
    short aval;
    short aval_m;
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
    struct user *us = malloc(sizeof(struct user));

    us->username = strdup(info[0]);
    us->name = strdup(info[1]);
    us->gender = *info[2];
    us->birth_date = calc_Date(info[3]);
    us->account_creation = calc_Date(info[4]);
    us->pay_method = info[5][1]; 
    us->account_status = info[6][0];
    us->aval = 0;
    us->total_dist = 0;
    us->total_spent = 0;
    us->total_spent_notip = 0;
    us->trips = 0;
    us->aval_m;
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

void *answer_q1_user(FILE *output,void *dbUsers, char *ID){
    DB_Users* db_users = (DB_Users*) dbUsers;
    gconstpointer id = (gconstpointer) ID;
    gpointer userp = g_hash_table_lookup(db_users->users_hashtable,id);
    User* user = (User*) userp;
    if(user){
        short Idade = idade(user->birth_date);
        double media = (double) (user->aval)/(user->trips);
        if(user->account_status == 'a' && user->trips != 0){
            fprintf(output,"%s;%c;%d;%.3f;%d;%.3f\n",user->name,user->gender,Idade,media,user->trips,user->total_spent);    
        }
        else if(user->account_status == 'a' && user->trips == 0){
            fprintf(output,"%s;%c;%d;%d;%d;%d\n",user->name,user->gender,Idade,0,user->trips,0);
        }   
    }
    fclose(output);
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
                for (j = i; j >= gap && (((users[j - gap]->total_dist)>temp->total_dist) || ((users[j - gap]->total_dist)==temp->total_dist && (users[j - gap]->last_trip_date)>temp->last_trip_date) || ((users[j - gap]->total_dist)==temp->total_dist && (users[j - gap]->last_trip_date)==temp->last_trip_date && (double)(users[j - gap]->aval)/(users[j - gap]->trips)>media)); j -= gap)
                    users[j] = users[j - gap];

                users[j] = temp;
            }
        }
        db_users->order = 1;
    }
}

int get_len_user(void* user_p){
    DB_users* users = (DB_users*) user_p;
    return users->len;
}

char* get_n_user(void* data, int i){
   DB_Users* users = (DB_Users*) data;
   char* username = strdup(users->users_array[i]->username);
   return username;
}

int user_get_idade(void* data, char* Username){
    DB_Users* db_users = (DB_Users*) data;
    gconstpointer id = (gconstpointer) Username;
    gpointer userp = g_hash_table_lookup(db_users->users_hashtable,id);
    User* user = (User*) userp;
    return idade(user->birth_date);
}

double user_get_avalm(void* data, char* Username){
    DB_Users* db_users = (DB_Users*) data;
    gconstpointer id = (gconstpointer) Username;
    gpointer userp = g_hash_table_lookup(db_users->users_hashtable,id);
    User* user = (User*) userp;
    double avalm = (double) user->aval/user->trips;
    return avalm;
}

int isUser(void* data, char* Username){
    DB_Users* db_users = (DB_Users*) data;
    gconstpointer id = (gconstpointer) Username;
    gpointer userp = g_hash_table_lookup(db_users->users_hashtable,id);
    User* user = (User*) userp;
    return (user != NULL);
}