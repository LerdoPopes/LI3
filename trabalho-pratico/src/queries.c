#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/rides.h"
#include "../Include/dates.h"
#include "../Include/queries.h"
#include <ctype.h>
#include <math.h>

void* process_query(char** save){
    char** save2 = malloc(12*sizeof(char*));
    size_t i = 0;
    for(; save[i]; i++)
    {
        save2[i] = strdup(save[i]);
    }
    save2[i] = NULL;
    return save2;
}

void free_queries(void** queries_p){
    char*** queries = (char***) queries_p;
    for(int i = 0; queries[i] != NULL;i++){
        for (size_t j = 0; queries[i][j] != NULL ; j++)
        {
            free(queries[i][j]);
        }
        
        free(queries[i]);
    }
    free(queries);
}


void answer_queries(void** input, void* USERS, void* DRIVERS){
    char*** INPUT = (char***) input;
    for(short i = 0, j = 1; INPUT[i] != NULL;i++,j++){
         switch(atoi(INPUT[i][0])){
             case(1):                                              
                 query1(INPUT[i][1],DRIVERS,USERS,j);
                 break;
             case(2):
                 query2(INPUT[i][1],DRIVERS,j);
                 break;
             case(3):
                 query3(INPUT[i][1],USERS,j);
                 break;
         }
    }
}

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
    // answer_q2_driver(resultado,dbDrivers,atoi(N));
}

//  for (size_t i = n-1; i>n-N-1; i--)
//     {
//         Driver *driver = drivers[i];
//         if(driver->account_status != 'a'){
//             N++;
//         }
//         else if(driver->trips == 0){
//             fprintf(output,"%012d;%s;%d\n",driver->id,driver->name,0);
//         }
//         else{
//             double media = (double)(driver->aval) / (driver->trips);
//             fprintf(output,"%012d;%s;%.3f\n",driver->id,driver->name,media);
//         }        
//     }
//     fclose(output);

void query3(char *N, void *dbUsers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");    
    // answer_q3_user(resultado,dbUsers,atoi(N));
}

// for (size_t i = n-1; i>n-N-1; i--)
//     {
//         User *user = users[i];
//         if(user->account_status != 'a'){
//             N++;
//         }
//         else{
//             fprintf(output,"%s;%s;%d\n",user->username,user->name,user->total_dist);
//         }        
//     }
//     fclose(output);

