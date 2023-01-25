#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/rides.h"
#include "../Include/dates.h"
#include "../Include/queries.h"
#include "../Include/statistics.h"
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


void answer_queries(void** input, void* USERS, void* DRIVERS, void* RIDES, void* STATS){
    char*** INPUT = (char***) input;
    for(short i = 0, j = 1; INPUT[i] != NULL;i++,j++){
        switch(atoi(INPUT[i][0])){
            case(1):
                clock_t start1 = clock();
                query1(INPUT[i][1],DRIVERS,USERS,j);
                clock_t end1 = clock();
                printf("Query 1: %f\n",((float)(end1 - start1))/CLOCKS_PER_SEC);  
                break;
            case(2):
                clock_t start2 = clock();
                query2(INPUT[i][1],DRIVERS,j);
                clock_t end2 = clock();
                printf("Query 2: %f\n",((float)(end2 - start2))/CLOCKS_PER_SEC);
                break;
            case(3):
                clock_t start3 = clock();
                query3(INPUT[i][1],USERS,j);
                clock_t end3 = clock();
                printf("Query 3: %f\n",((float)(end3 - start3))/CLOCKS_PER_SEC);
                break;
            case(4):
                clock_t start4 = clock();
                query4(INPUT[i][1],STATS,j);
                clock_t end4 = clock();
                printf("Query 4: %f\n",((float)(end4 - start4))/CLOCKS_PER_SEC);
                break;
            case(5):
                clock_t start5 = clock();
                query5(INPUT[i][1],INPUT[i][2],STATS,j);
                clock_t end5 = clock();
                printf("Query 5: %f\n",((float)(end5 - start5))/CLOCKS_PER_SEC);
                break;
            case(6):
                clock_t start6 = clock();
                query6(INPUT[i][1],INPUT[i][2],INPUT[i][3],STATS,RIDES,j);
                clock_t end6 = clock();
                printf("Query 6: %f\n",((float)(end6 - start6))/CLOCKS_PER_SEC);
                break;
            // case(7):
            //     clock_t start7 = clock();
            //     query7(INPUT[i][1],USERS,j);
            //     clock_t end7 = clock();
            //     printf("Query 7: %f\n",((float)(end7 - start7))/CLOCKS_PER_SEC);
            //     break;
            // case(8):
            //     clock_t start8 = clock();
            //     query8(INPUT[i][1],USERS,j);
            //     clock_t end8 = clock();
            //     printf("Query 8: %f\n",((float)(end8 - start8))/CLOCKS_PER_SEC);
            //     break;
            // case(9):
            //     clock_t start9 = clock();
            //     query9(INPUT[i][1],USERS,j);
            //     clock_t end9 = clock();
            //     printf("Query 9: %f\n",((float)(end9 - start9))/CLOCKS_PER_SEC);
            //     break;
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
            fprintf(resultado,"%012d;%s;%.3f\n",id,driver_get_name(dbDrivers,id),driver_get_aval_m(dbDrivers,id));
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

void query4(char *Cidade,void * dbStats,short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");
    if(cityValid(dbStats,Cidade)){
        fprintf(resultado,"%.3f\n",(double)(city_get_money(dbStats,Cidade)/city_get_num_rides(dbStats,Cidade)));
    }
    fclose(resultado);
}

void query5(char* data1, char* data2, void *dbStats,short i){
    char *id = malloc(50);
    int num_rides = 0;
    double total_money = 0;
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");
    int date1 = (int) calc_Date(data1);
    int date2 = (int) calc_Date(data2);
    for(int i = date1; i <= date2; i++){
        total_money += date_get_money(dbStats,i);
        num_rides += date_get_num_trips(dbStats,i);
    }
    printf("%d\n",num_rides);
    fprintf(resultado,"%.3f\n",(double)(total_money/num_rides));
    fclose(resultado);
}

void query6(char* cidade, char* data1, char* data2, void *dbStats, void *dbRides,short i){
    char *id = malloc(50);
    int num_rides = 0;
    double total_distance = 0;
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");
    int date1 = (int) calc_Date(data1);
    int date2 = (int) calc_Date(data2);
    for(int i = date1; i <= date2; i++){
        for(int j = 0; j < date_get_num_trips(dbStats,i);j++){
            total_distance += (double)ride_get_distance(dbRides,date_get_ride(dbStats,i,j));
        }
        num_rides += date_get_num_trips(dbStats,i);
    }
    fprintf(resultado,"%.3f\n",(double)(total_distance/num_rides));
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

