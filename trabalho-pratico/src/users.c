#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Include/users.h"
#include "../Include/dates.h"

enum method {
    cash = 'a',
    credit_card = 'r',
    debit_card = 'e'
};

typedef struct user {
    char *username;
    char *name;
    char gender;
    short birth_date;
    short account_creation;
    enum method pay_method;
    char account_status;
} User;

typedef struct data_base_users{
    void** users_array;
    GHashTable* users_hashtable;
    // GTree* users_tree;
} DB_users;

void *process_user(char* const* info) 
{
    struct user *us = malloc(sizeof(struct user));

    us->username = strdup(info[0]);
    us->name = strdup(info[1]);
    us->gender = *info[2];
    us->birth_date = calc_Date(info[3]);
    //printf("%s\n",info[3]);
    //char *bla = malloc(sizeof("11/11/1111"));
    us->account_creation = calc_Date(info[4]);
    //memmove(bla, info[3], strlen(info[3]));
    // memmove(us->account_creation, info[4], strlen(info[4]));
    us->pay_method = info[5][1]; 
    us->account_status = info[6][0]; //Para print disto, tem que se verificar a letra e dar print ao status com essa primeria letra 
    // printf("%s %s %c %s %s %s %c\n",us->username,us->name,us->birth_date,us->account_creation,us->pay_method,us->account_status);
    // free(bla);
    return us;
}

void *organize_user(void* gtablep,void* userp){
    User* user = (User*) userp;
    if(gtablep == NULL){
        GHashTable* hashtable = g_hash_table_new(g_str_hash,g_str_equal);
        g_hash_table_insert(hashtable,user->username,user);
        return hashtable;
    }
    GHashTable* gtable = (GHashTable*) gtablep;
    g_hash_table_insert(gtable,user->username,user);
    return gtable;
}

void *arrange_user(void* gtable,void** array){
    DB_users* db_users = malloc(sizeof(DB_users));
    db_users->users_array = array;
    db_users->users_hashtable = (GHashTable*) gtable;
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
}

void print_user(char* key, void* usersDB){
    DB_users* db_users = (DB_users*) usersDB;
    gconstpointer user_name = (gconstpointer) key;
    gpointer guser = g_hash_table_lookup(db_users->users_hashtable,user_name);
    User* user = (User*) guser;
    printf("%s,%s,%c,%u,%u\n",user->username,user->name,user->gender,user->birth_date,user->account_creation);
}