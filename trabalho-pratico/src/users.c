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

struct user{
    char *username;
    char *name;
    char gender;
    short birth_date;
    short account_creation;
    enum method pay_method;
    char account_status;
    short trips;
    float total_spent;
    short total_dist;
    short aval;
};

typedef struct data_base_users{
    void** users_array;
    GHashTable* users_hashtable;
    // GTree* users_tree;
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
    us->account_status = info[6][0]; //Para print disto, tem que se verificar a letra e dar print ao status com essa primeria letra 
    us->aval = 0;
    us->total_dist = 0;
    us->total_spent = 0;
    us->trips = 0;
    return us;
}

void *organize_user(void** results, void* useless, void* useless2, void(useless3)(void*,void*,void*,void*,void*), void*(useless4)(void*,void*,void*,void*)){
    GHashTable* gtable = g_hash_table_new(g_str_hash,g_str_equal);
    // g_hash_table_insert(hashtable,user->username,user);
      for (size_t i = 0; results[i]; i++)
    {
        User* user = (User*) results[i];
        g_hash_table_insert(gtable,user->username,user);  
    }
    DB_users* db_users = malloc(sizeof(DB_users));
    db_users->users_array = results;
    db_users->users_hashtable = gtable;
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

void print_user(void* key, void* usersDB){
    DB_users* db_users = (DB_users*) usersDB;
    gconstpointer user_name = (gconstpointer) key;
    gpointer guser = g_hash_table_lookup(db_users->users_hashtable,user_name);
    User* user = (User*) guser;
    printf("%s,%s,%c,%u,%u\n",user->username,user->name,user->gender,user->birth_date,user->account_creation);
}


void set_user_stats(void* dbUsers, void* distp, void* avalp, void* username, void* moneyp){
    DB_users* db_users = (DB_users*) dbUsers;
    gpointer userp = g_hash_table_lookup(db_users->users_hashtable,username);
    User* user = (User*) userp;
    short* dist = (short*) distp;
    short* aval = (short*) avalp;
    float* money = (float*) moneyp;
    user->total_dist += *dist;
    user->aval += *aval;
    user->trips++;
    user->total_spent += *money;
}

char *user_get_username(struct user *u){
     char *user_nome = (char *)malloc(255 * sizeof(char));
     strcpy(user_nome,u->username);    
     return user_nome;
}

char *user_get_name(struct user *u){
     char *nome = (char *)malloc(255 * sizeof(char));
     strcpy(nome,u->name);    
     return nome;
}

char user_get_gender(struct user *u){
    return u->gender;
}

char user_get_birth_date(struct user *u){
    return u->birth_date;
}

short user_get_account_creation(struct user *u){
    return u->account_creation;
}

char user_get_account_status(struct user *u){
    return u->account_status;
}

void *answer_q1_user(FILE *output,void *dbUsers, char *ID){
    DB_Users* db_users = (DB_Users*) dbUsers;
    gconstpointer id = (gconstpointer) ID;
    gpointer userp = g_hash_table_lookup(db_users->users_hashtable,id);
    User* user = (User*) userp;
    short Idade = idade(user->birth_date);
    double media = (user->aval)/(user->trips);
    if(user->account_status = 'a'){
        fprintf(output,"%s;%c;%d;%.3f;%d;%.3f\n",user->name,user->gender,Idade,media,user->trips,user->total_spent);//avaliacao_media,numero_viagens,total_gasto);    
    }    
    fclose(output);
}

// short user_get_idade(struct user *u,char *data_atual,char *birth_date){
//      u->idade = idade(data_atual,birth_date);
//      return u->idade;
// }