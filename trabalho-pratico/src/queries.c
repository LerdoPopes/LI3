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
        int id = atoi(ID);
        if(isDriver(dbDrivers,id))
        {
            if (driver_get_account_status(dbDrivers,id) == 'a' && driver_get_trips(dbDrivers,id) != 0)
            {
                fprintf(resultado, "%s;%c;%d;%.3f;%d;%.3f\n", driver_get_name(dbDrivers,id), driver_get_gender(dbDrivers,id), driver_get_idade(dbDrivers,id), driver_get_aval_m(dbDrivers,id), driver_get_trips(dbDrivers,id), driver_get_total_spent(dbDrivers,id));
            }
            else if (driver_get_account_status(dbDrivers,id) == 'a' && driver_get_trips(dbDrivers,id) == 0)
            {
                fprintf(resultado, "%s;%c;%d;%d;%d;%d\n", driver_get_name(dbDrivers,id), driver_get_gender(dbDrivers,id), driver_get_idade(dbDrivers,id), 0, 0, 0);
            }
        }
    }
    else{
        if(isUser(dbUsers,ID)){
            char* user = user_get_name(dbUsers,ID);
            if(user_get_account_status(dbUsers,ID) == 'a' && user_get_trips(dbUsers,ID) != 0){
                fprintf(resultado,"%s;%c;%d;%.3f;%d;%.3f\n",user,user_get_gender(dbUsers,ID),user_get_idade(dbUsers,ID),user_get_aval_m(dbUsers,ID),user_get_trips(dbUsers,ID),user_get_total_spent(dbUsers,ID));
            }
            else if(user_get_account_status(dbUsers,ID) == 'a' && user_get_trips(dbUsers,ID) == 0){
                fprintf(resultado,"%s;%c;%d;%d;%d;%d\n",user,user_get_gender(dbUsers,ID),user_get_idade(dbUsers,ID),0,0,0);
            } 
        }
    }
    fclose(resultado);
}

void query2(char* N, void *dbDrivers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");   
    int n = atoi(N);
    int len = driver_get_len(dbDrivers);
    order_by_aval(dbDrivers);
    for (size_t i = len-1; i>len-n-1; i--)
    {
        int id = get_n_driver(dbDrivers,i);
        if(driver_get_account_status(dbDrivers,id) != 'a'){
            n++;
        }
        else{
            fprintf(resultado,"%d;%s;%d\n",id,driver_get_name(dbDrivers,id),driver_get_aval_m(dbDrivers,id));
        }        
    }
    fclose(resultado);
}


void query3(char *Num, void *dbUsers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");
    int n = atoi(Num);
    int len = get_len_user(dbUsers);
    order_by_dist(dbUsers);
    for (size_t i = len-1; i>len-n-1; i--)
    {
        char* User = get_n_user(dbUsers,i);
        if(user_get_account_status(dbUsers,User) != 'a'){
            n++;
        }
        else{
            fprintf(resultado,"%s;%s;%d\n",User,user_get_name(dbUsers,User),user_get_total_dist(dbUsers,User));
        }        
    }
    fclose(resultado);
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

