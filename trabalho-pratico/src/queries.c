#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/dates.h"
#include "../Include/queries.h"
#include <ctype.h>

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