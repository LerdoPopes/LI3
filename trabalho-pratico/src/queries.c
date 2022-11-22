#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/dates.h"
#include "../Include/queries.h"
#include <ctype.h>
#include <math.h>

void query1(char *ID, void *dbDrivers, void *dbUsers, short i){
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

void query2(char* N, void *dbDrivers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");    
        answer_q2_driver(resultado,dbDrivers,atoi(N));
    }

void query3(char *N, void *dbUsers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");    
        answer_q3_user(resultado,dbUsers,atoi(N));
    }
