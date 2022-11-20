#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/dates.h"
#include <ctype.h>
#define data_atual "09/10/2022"

struct queries {
    char** arguments;
};

struct queries_db {
    void** queries_parsed;
};

void* process_querie(char* const* info){
    struct queries queriess = malloc(sizeof(struct queries));
    queriess->arguments = info;
    return queriess;
};

void* organize_querie(void** results, void* struct_drivers, void* struct_users, void(set_users_stats)(void*,void*,void*,void*,void*), void*(set_driver_stats)(void*,void*,void*,void*)){
    struct queries_db result = malloc(sizeof(struct queries_db));
    result->queries_parsed = results;
    return result;
}

void *query1(char *ID, void *dbDrivers, void *dbUsers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");    
    if(isdigit(ID[0])){
            answer_q1_driver(resultado,dbDrivers,ID);
    }
    else{
            answer_q1_user(resultado,dbUsers,ID);
    }
}