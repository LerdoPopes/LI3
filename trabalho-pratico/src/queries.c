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
#include "../Include/userinterface.h"
#include <ctype.h>
#include <math.h>
#include <ncurses.h>

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
            case(7):
                clock_t start7 = clock();
                query7(INPUT[i][1],INPUT[i][2],STATS,DRIVERS,j);
                clock_t end7 = clock();
                printf("Query 7: %f\n",((float)(end7 - start7))/CLOCKS_PER_SEC);
                break;
            case(8):
                clock_t start8 = clock();
                query8(INPUT[i][1],INPUT[i][2],STATS,RIDES,DRIVERS,USERS,j);
                clock_t end8 = clock();
                printf("Query 8: %f\n",((float)(end8 - start8))/CLOCKS_PER_SEC);
                break;
            case(9):
                clock_t start9 = clock();
                query9(INPUT[i][1],INPUT[i][2],STATS,RIDES,j);
                clock_t end9 = clock();
                printf("Query 9: %f\n",((float)(end9 - start9))/CLOCKS_PER_SEC);
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
            char* driver = malloc(50);
            int size_d = 50;
            if (driver_get_account_status(dbDrivers,id) == 'a' && driver_get_trips(dbDrivers,id) != 0)
            {
                driver_get_name(dbDrivers,id,driver,&size_d);
                fprintf(resultado, "%s;%c;%d;%.3f;%d;%.3f\n",driver, driver_get_gender(dbDrivers,id), driver_get_idade(dbDrivers,id), driver_get_aval_m(dbDrivers,id), driver_get_trips(dbDrivers,id), driver_get_total_spent(dbDrivers,id));
                free(driver);
            }
            else if (driver_get_account_status(dbDrivers,id) == 'a' && driver_get_trips(dbDrivers,id) == 0)
            {
                driver_get_name(dbDrivers,id,driver,&size_d);
                fprintf(resultado, "%s;%c;%d;%d;%d;%d\n", driver, driver_get_gender(dbDrivers,id), driver_get_idade(dbDrivers,id), 0, 0, 0);
                free(driver);
            }
        }
    }
    else{
        if(isUser(dbUsers,ID)){
            char* user = malloc(50);
            int size_user = 50;
            if(user_get_account_status(dbUsers,ID) == 'a' && user_get_trips(dbUsers,ID) != 0){
                user_get_name(dbUsers,ID,user,&size_user);
                fprintf(resultado,"%s;%c;%d;%.3f;%d;%.3f\n",user,user_get_gender(dbUsers,ID),user_get_idade(dbUsers,ID),user_get_aval_m(dbUsers,ID),user_get_trips(dbUsers,ID),user_get_total_spent(dbUsers,ID));
                free(user);
            }
            else if(user_get_account_status(dbUsers,ID) == 'a' && user_get_trips(dbUsers,ID) == 0){
                user_get_name(dbUsers,ID,user,&size_user);
                fprintf(resultado,"%s;%c;%d;%d;%d;%d\n",user,user_get_gender(dbUsers,ID),user_get_idade(dbUsers,ID),0,0,0);
                free(user);
            } 
        }
    }
    fclose(resultado);
    free(id);
}

void query1_UI(char *ID, void *dbDrivers, void *dbUsers, void *dbStats, void *dbRides){
    int yMax, xMax;
    getmaxyx(stdscr,yMax,xMax);
    short done = 0;
    char* person = malloc(50);
    int size_p = 50;
    while(!done){
    if(isdigit(ID[0])){
        int id = atoi(ID);
        if(isDriver(dbDrivers,id))
        {
            if (driver_get_account_status(dbDrivers,id) == 'a' && driver_get_trips(dbDrivers,id) != 0)
            {
                mvprintw(yMax/2, 22, "%s", driver_get_name(dbDrivers,id,person,&size_p));
                mvprintw(yMax/2, 52, "%c", driver_get_gender(dbDrivers,id));
                mvprintw(yMax/2,82 , "%d", driver_get_idade(dbDrivers,id)); 
                mvprintw(yMax/2, 112, "%.3f", driver_get_aval_m(dbDrivers,id));
                mvprintw(yMax/2, 142, "%d", driver_get_trips(dbDrivers,id));
                mvprintw(yMax/2,172 , "%.3f", driver_get_total_spent(dbDrivers,id));
            }
            else if (driver_get_account_status(dbDrivers,id) == 'a' && driver_get_trips(dbDrivers,id) == 0)
            {
                mvprintw(yMax/2, 22, "%s", driver_get_name(dbDrivers,id,person,&size_p));
                mvprintw(yMax/2, 52, "%c", driver_get_gender(dbDrivers,id));
                mvprintw(yMax/2,82 , "%d", driver_get_idade(dbDrivers,id)); 
                mvprintw(yMax/2, 112, "%d", 0);
                mvprintw(yMax/2, 142, "%d", 0);
                mvprintw(yMax/2,172 , "%d", 0);                
            }
        }
    }
    else{
        if(isUser(dbUsers,ID)){
            user_get_name(dbUsers,ID,person,&size_p);
            if(user_get_account_status(dbUsers,ID) == 'a' && user_get_trips(dbUsers,ID) != 0){
                mvprintw(yMax/2, 22, "%s", person);
                mvprintw(yMax/2, 52, "%c", user_get_gender(dbUsers,ID));
                mvprintw(yMax/2,82 , "%d", user_get_idade(dbUsers,ID)); 
                mvprintw(yMax/2, 112, "%.3f", user_get_aval_m(dbUsers,ID));
                mvprintw(yMax/2, 142, "%d", user_get_trips(dbUsers,ID));
                mvprintw(yMax/2,172 , "%.3f", user_get_total_spent(dbUsers,ID));                
            }
            else if(user_get_account_status(dbUsers,ID) == 'a' && user_get_trips(dbUsers,ID) == 0){
                mvprintw(yMax/2, 22, "%s", person);
                mvprintw(yMax/2, 52, "%c", user_get_gender(dbUsers,ID));
                mvprintw(yMax/2,82 , "%d", user_get_idade(dbUsers,ID)); 
                mvprintw(yMax/2, 112, "%d", 0);
                mvprintw(yMax/2, 142, "%d", 0);
                mvprintw(yMax/2,172 , "%d", 0);                
            } 
        }
    }
    mvprintw(50, xMax/2 - strlen("Pressione 'Q' para voltar ao Menu Inicial")/2 , "Pressione 'Q' para voltar ao Menu Inicial");
    int ch = getch();
    switch (ch) {
    case 'q':
    case 'Q':
        done = 1;
        clear();
        queries_menu(dbDrivers,dbUsers,dbRides,dbStats);
    }
    }
}

void query2(char* N, void *dbDrivers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");   
    int n = atoi(N);
    int len = driver_get_len(dbDrivers);
    char* driver = malloc(50);
    int size_d = 50;
    for (size_t i = len-1; i>len-n-1; i--)
    {
        int id = get_n_driver(dbDrivers,i);
        if(driver_get_account_status(dbDrivers,id) != 'a'){
            n++;
        }
        else{
            fprintf(resultado,"%012d;%s;%.3f\n",id,driver_get_name(dbDrivers,id,driver,&size_d),driver_get_aval_m(dbDrivers,id));
        }        
    }
    fclose(resultado);
}

void query2_UI(char* N, void *dbDrivers,void *dbUsers,void *dbRides, void *dbStats){
    int n = atoi(N);
    int m = n;
    int len = driver_get_len(dbDrivers);
    int yMax, xMax;
    getmaxyx(stdscr,yMax,xMax);
    int pages;
    if (n % 30 == 0) pages = n / 30;
    else pages = n / 30 + 1;
    short done = 0;
    int page = 0;
    keypad(stdscr, TRUE);

    char* driver = malloc(50);
    int size_d = 50;

    while (!done) {
        clear();
        
        int start = page * 30;
        int j = (len-1) - start;
        int end = start + 30;
        if (end > m) {
            end = m;
        }

        mvprintw(45, xMax/2 - strlen ("Page 1 / 1")/2 , "Page %d / %d", page + 1, pages);
        int a = 0;
        mvprintw(9, 27,"ID                                                           Nome                                                       Avaliacao Media                         ");

        for(int i = start; i < end;j--){
            if (a % 31 == 0) a *= 0;
            int id = get_n_driver(dbDrivers,i);
            if(driver_get_account_status(dbDrivers,id) != 'a'){
                n++;
            }
            else{

                mvprintw(a + 11, 22, "%012d", id);
                mvprintw(a + 11, 81, "%s", driver_get_name(dbDrivers,id,driver,&size_d));
                mvprintw(a + 11, 152 ,"%.3f", driver_get_aval_m(dbDrivers,id)); 
                a++;
                i++;
            }      
        }       
       
        mvprintw(50, xMax/2 - strlen("Pressione 'N' para ver a próxima página, 'B' para a página anterior, 'Q' para voltar ao Menu Inicial")/2 , "Pressione 'N' para ver a próxima página, 'B' para a página anterior, 'Q' para voltar ao Menu Inicial");
        int ch = getch();
        switch (ch) {
        case 'n':
        case 'N':
            page++;
            if (page >= pages) {
            page = pages - 1;
            }
            break;
        case 'b':
        case 'B':
            page--;
            if (page < 0) {
            page = 0;
            }
            break;
        case 'q':
        case 'Q':
            done = 1;
            clear();
            queries_menu(dbDrivers,dbUsers,dbRides,dbStats);
        }
    }    
}

void query3(char *Num, void *dbUsers, short i){
    char *id = malloc(50);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");
    int n = atoi(Num);
    int len = get_len_user(dbUsers);
    char* username = malloc(50);
    int size_user = 50;
    char* name = malloc(50);
    int size_name = 50;
    for (size_t i = len-1; i>len-n-1; i--)
    {
        char* User = get_n_user(dbUsers,i,username,&size_user);
        if(user_get_account_status(dbUsers,User) != 'a'){
            n++;
        }
        else{
            fprintf(resultado,"%s;%s;%d\n",User,user_get_name(dbUsers,User,name,&size_name),user_get_total_dist(dbUsers,User));
        }        
    }
    fclose(resultado);
}

void query3_UI(char *Num, void *dbUsers,void *dbRides, void *dbDrivers, void *dbStats){
    int yMax, xMax;
    int f = 0;
    getmaxyx(stdscr,yMax,xMax);
    int n = atoi(Num);
    int m = n;
    int len = get_len_user(dbUsers);
    int pages;
    if (n % 30 == 0) pages = n / 30;
    else pages = n / 30 + 1;
    short done = 0;
    int page = 0;
    keypad(stdscr, TRUE);

    while (!done) {
        clear();
        
        int start = page * 30;
        int j = (len-1) - start;
        int end = start + 30;
        if (end > m) {
            end = m;
        }
        
        mvprintw(45, xMax/2 - strlen ("Page 1 / 1")/2 , "Page %d / %d", page + 1, pages);
        int a = 0;
        mvprintw(9, 27,"ID                                                           Nome                                                       Avaliacao Media                         ");
        
        char* User = malloc(50);
        int size_u = 50;

        char* name_u = malloc(50);
        int size_nU = 50;
        for(int i = start; i < end;j--){
            if (a % 31 == 0) a *= 0;
            get_n_user(dbUsers,j,User,&size_u);
            if(user_get_account_status(dbUsers,User) != 'a'){
                n++;
            }
            else{
                mvprintw(a + 11, 22, "%s", User);
                mvprintw(a + 11, 81, "%s", user_get_name(dbUsers,User,name_u,&size_nU));
                mvprintw(a + 11, 152 , "%d", user_get_total_dist(dbUsers,User)); 
                a++;
                i++;
            }      
        }       
       
        mvprintw(50, xMax/2 - strlen("Pressione 'N' para ver a próxima página, 'B' para a página anterior, 'Q' para voltar ao Menu Inicial")/2 , "Pressione 'N' para ver a próxima página, 'B' para a página anterior, 'Q' para voltar ao Menu Inicial");
        int ch = getch();
        switch (ch) {
        case 'n':
        case 'N':
            page++;
            if (page >= pages) {
            page = pages - 1;
            }
            break;
        case 'b':
        case 'B':
            page--;
            if (page < 0) {
            page = 0;
            }
            break;
        case 'q':
        case 'Q':
            done = 1;
            clear();
            queries_menu(dbDrivers,dbUsers,dbRides,dbStats);
        }
    }
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

void query4_UI(char *Cidade,void * dbStats,void *dbUsers, void *dbRides, void *dbDrivers){
    int yMax, xMax;
    getmaxyx(stdscr,yMax,xMax);
    short done = 0;
    while(!done){
        if(cityValid(dbStats,Cidade)){
            mvprintw(yMax/2,xMax/2,"%.3f\n", (double)(city_get_money(dbStats,Cidade)/city_get_num_rides(dbStats,Cidade)));
        }
        mvprintw(50, xMax/2 - strlen("Pressione 'Q' para voltar ao Menu Inicial")/2 , "Pressione 'Q' para voltar ao Menu Inicial");
        int ch = getch();
        switch (ch) {
        case 'q':
        case 'Q':
            done = 1;
            clear();
            queries_menu(dbDrivers,dbUsers,dbRides,dbStats);
        }
    }
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
    if(num_rides > 0){
        fprintf(resultado,"%.3f\n",(double)(total_money/num_rides));
    }
    fclose(resultado);
}

void query5_UI(char* data1, char* data2, void *dbStats,void *dbUsers, void *dbRides,void *dbDrivers){
    int yMax, xMax;
    getmaxyx(stdscr,yMax,xMax);
    int num_rides = 0;
    double total_money = 0;
    int date1 = (int) calc_Date(data1);
    int date2 = (int) calc_Date(data2);
    short done = 0;
    for(int i = date1; i <= date2; i++){
        total_money += date_get_money(dbStats,i);
        num_rides += date_get_num_trips(dbStats,i);
    }
    while(!done){
        if(num_rides > 0){
            mvprintw(yMax/2,xMax/2,"%.3f\n", (double)(total_money/num_rides));
        }
        mvprintw(50, xMax/2 - strlen("Pressione 'Q' para voltar ao Menu Inicial")/2 , "Pressione 'Q' para voltar ao Menu Inicial");
            int ch = getch();
            switch (ch) {
            case 'q':
            case 'Q':
                done = 1;
                clear();
                queries_menu(dbDrivers,dbUsers,dbRides,dbStats);
            }
    }
}

void query6(char* cidade, char* data1, char* data2, void *dbStats, void *dbRides,short i){
    char *id = malloc(50);
    int num_rides = 0;
    double total_distance = 0;
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");
    int date1 = (int) calc_Date(data1);
    int date2 = (int) calc_Date(data2);

    char* ride_c = malloc(30);
    int city_size = 30;
    
    for(int i = date1; i <= date2; i++){
        int max = date_get_num_trips(dbStats,i);

        for(int j = 0; j < max;j++){
            int id = date_get_ride(dbStats,i,j);
            ride_get_city(dbRides,id,ride_c,&city_size);
            if(strcmp(cidade,ride_c) == 0){
                total_distance += (double) ride_get_distance(dbRides,id);
                num_rides++;
            }
        }
    }
    if(num_rides){
        fprintf(resultado,"%.3f\n",(double)(total_distance/num_rides));
    }
    fclose(resultado);
}

void query6_UI(char* cidade, char* data1, char* data2, void *dbStats, void *dbRides, void *dbUsers, void *dbDrivers){
    int yMax, xMax;
    getmaxyx(stdscr,yMax,xMax);
    int num_rides = 0;
    double total_distance = 0;
    int date1 = (int) calc_Date(data1);
    int date2 = (int) calc_Date(data2);
    int done = 0;
    char* city = malloc(30);
    int size = 30;
    for(int i = date1; i <= date2; i++){
        int max = date_get_num_trips(dbStats,i);

        for(int j = 0; j < max;j++){
            int id = date_get_ride(dbStats,i,j);
            if(strcmp(cidade,ride_get_city(dbRides,id,city,&size)) == 0){
                total_distance += (double) ride_get_distance(dbRides,id);
                num_rides++;
            }
        }
    }
    while(!done){
    if(num_rides){
        mvprintw(yMax/2,xMax/2,"%.3f\n", (double)(total_distance/num_rides));
    }
    mvprintw(50, xMax/2 - strlen("Pressione 'Q' para voltar ao Menu Inicial")/2 , "Pressione 'Q' para voltar ao Menu Inicial");
            int ch = getch();
            switch (ch) {
            case 'q':
            case 'Q':
                done = 1;
                clear();
                queries_menu(dbDrivers,dbUsers,dbRides,dbStats);
            }
        }
}

void query7(char * N, char * cidade, void *dbStats, void *dbDrivers, short i){
    char *id = malloc(50);
    int n = atoi(N);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");
    char* driver = malloc(50);
    int size_d = 50;
    order_by_aval_m(dbStats,cidade);
    for(int i = 0; i < n;i++){
        int num_drivers = city_get_num_drivers(dbStats,cidade)-i-1;
        if(num_drivers == -1){
            break;
        }
        int id = city_get_info_id(dbStats,cidade,num_drivers);
        if(driver_get_account_status(dbDrivers,id) != 'a'){
            n++;
        }
        else{
            double aval_m = (double) ((double)city_get_info_aval(dbStats,cidade,num_drivers)/(double)city_get_info_num_trips(dbStats,cidade,num_drivers));
            fprintf(resultado,"%012d;%s;%.3f\n",id,driver_get_name(dbDrivers,id,driver,&size_d),aval_m);
        }
    }
    fclose(resultado);
}

// void query7_UI(char * N, char * cidade, void *dbStats, void *dbDrivers, short i){
//     int n = atoi(N);
//     order_by_aval_m(dbStats,cidade);
//     for(int i = 0; i < n;i++){
//         int num_drivers = city_get_num_drivers(dbStats,cidade)-i-1;
//         if(num_drivers == -1){
//             break;
//         }
//         int id = city_get_info_id(dbStats,cidade,num_drivers);
//         if(driver_get_account_status(dbDrivers,id) != 'a'){
//             n++;
//         }
//         else{
//             double aval_m = (double) ((double)city_get_info_aval(dbStats,cidade,num_drivers)/(double)city_get_info_num_trips(dbStats,cidade,num_drivers));
//             fprintf(resultado,"%012d;%s;%.3f\n",id,driver_get_name(dbDrivers,id),aval_m);
//         }
//     }
// }

void query8(char* gender, char* X, void *dbStats, void *dbRides, void *dbDrivers, void *dbUsers,short i){
    char *id = malloc(50);
    short x = atoi(X);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");  
    order_by_account_age(dbStats,gender,dbUsers,dbDrivers,dbRides);
    
    char* user = malloc(50);
    int size_user = 50;
    
    char* name_user = malloc(50);
    int size_nameU = 50;

    char* driver = malloc(50);
    int size_driver = 50;
    
    if(strcmp(gender,"M") == 0){
        int nM = gender_get_nM(dbStats);
        for(int i = 0; i < nM; i++){
            short driver_age = idade(male_driver_get_age(dbStats,i));
            short user_age = idade(male_user_get_age(dbStats,i));
            if(driver_age >= x && user_age >= x){
                int id = ride_male_get_id(dbStats,i);
                int id_driver = ride_get_driver(dbRides,id);
                driver_get_name(dbDrivers,id_driver,driver,&size_driver);
                ride_get_user(dbRides,id,user,&size_user);
                user_get_name(dbUsers,user,name_user,&size_nameU);

                fprintf(resultado,"%d;%s;%s;%s\n",id_driver,driver,user,name_user,driver_age,user_age);
            }
        }
    }
    else if(strcmp(gender,"F") == 0){ 
        int nF = gender_get_nF(dbStats);
        for(int i = 0; i < nF; i++){
            short driver_age = shemale_driver_get_age(dbStats,i);
            short user_age = shemale_user_get_age(dbStats,i);
            if(driver_age >= x && user_age >= x){
                int id = ride_shemale_get_id(dbStats,i);
                int id_driver = ride_get_driver(dbRides,id);
                driver_get_name(dbDrivers,id_driver,driver,&size_driver);
                ride_get_user(dbRides,id,user,&size_user);
                user_get_name(dbUsers,user,name_user,&size_nameU);
                fprintf(resultado,"%012d;%s;%s;%s\n",id_driver,driver,user,name_user);
            }
        }
    }
    fclose(resultado);
}

// void query8_UI(char* gender, char* X, void *dbStats, void *dbRides, void *dbDrivers, void *dbUsers,short i){
//     short x = atoi(X);
//     order_by_account_age(dbStats,gender);
//     if(strcmp(gender,"M") == 0){
//         int nM = gender_get_nM(dbStats);
//         for(int i = nM-1; i > 0; i--){
//             short driver_age = male_driver_get_age(dbStats,i);
//             short user_age = male_user_get_age(dbStats,i);
//             if(driver_age < x || user_age < x){
//                 break;
//             }
//             int id = ride_male_get_id(dbStats,i);
//             int id_driver = ride_get_driver(dbRides,id);
//             char *name_driver = driver_get_name(dbDrivers,id_driver);
//             char *username_user = ride_get_user(dbRides,id);
//             char *name_user = user_get_name(dbUsers,username_user);
//             fprintf(resultado,"%d;%s;%s;%s\n",id_driver,name_driver,username_user,name_user);
//         }
//     }
//     else if(strcmp(gender,"F") == 0){ 
//         int nF = gender_get_nF(dbStats);
//         for(int i = 0; i < nF; i++){
//             short driver_age = shemale_driver_get_age(dbStats,i);
//             short user_age = shemale_user_get_age(dbStats,i);
//             if(driver_age >= x && user_age >= x){
//                 int id = ride_shemale_get_id(dbStats,i);
//                 int id_driver = ride_get_driver(dbRides,id);
//                 char *name_driver = driver_get_name(dbDrivers,id_driver);
//                 char *username_user = ride_get_user(dbRides,id);
//                 char *name_user = user_get_name(dbUsers,username_user);
//                 fprintf(resultado,"%d;%s;%s;%s\n",id_driver,name_driver,username_user,name_user);
//             }
//         }
//     }
// }

void query9(char* data1, char* data2, void *dbStats, void *dbRides,short i){
    char *id = malloc(50);
    int num = 0;
    int current = 256;
    int *ride_ids = malloc(sizeof(int) * current);
    sprintf(id, "./Resultados/command%d_output.txt", i);
    FILE *resultado = fopen(id, "w");
    int date1 = (int) calc_Date(data1);
    int date2 = (int) calc_Date(data2);
    for(int i = date1; i <= date2; i++){
        int max = date_get_num_trips(dbStats,i);
        for(int j = 0; j < max;j++){
            int id = date_get_ride(dbStats,i,j);
            if(num + 1 == current) ride_ids = realloc(ride_ids, (current *= 2) * sizeof(int)); 
            if(ride_get_tip(dbRides,id) != 0){
                ride_ids[num++] = id;
            }
        }
    }
    order_by_distance(dbRides,ride_ids,num);
    char* city = malloc(30);
    int size_city = 30;
    for(int n = num - 1; n >= 0; n--){
        dateCombo *data = conv_Days_to_Date(ride_get_date(dbRides,ride_ids[n]));
        short distancia = ride_get_distance(dbRides,ride_ids[n]);
        ride_get_city(dbRides,ride_ids[n],city,&size_city);
        double tip = ride_get_tip(dbRides,ride_ids[n]);
        fprintf(resultado,"%012d;%02d/%02d/%d;%d;%s;%.3f\n",ride_ids[n],data->day,data->month,data->year,distancia,city,tip);
    }
    fclose(resultado);
}

void query9_UI(char* data1, char* data2, void *dbStats, void *dbRides, void *dbUsers, void *dbDrivers){
    int yMax, xMax;
    getmaxyx(stdscr,yMax,xMax);
    int num = 0;
    int current = 256;
    int *ride_ids = malloc(sizeof(int) * current);
    int date1 = (int) calc_Date(data1);
    int date2 = (int) calc_Date(data2);
    for(int i = date1; i <= date2; i++){
        int max = date_get_num_trips(dbStats,i);
        for(int j = 0; j < max;j++){
            int id = date_get_ride(dbStats,i,j);
            if(num + 1 == current) ride_ids = realloc(ride_ids, (current *= 2) * sizeof(int)); 
            if(ride_get_tip(dbRides,id) != 0){
                ride_ids[num++] = id;
            }
        }
    }
    order_by_distance(dbRides,ride_ids,num);
    int pages;
    if (num % 30 == 0) pages = num / 30;
    else pages = num / 30 + 1;
    int done = 0;
    int page = 0;

    keypad(stdscr, TRUE);

    while (!done) {
        clear();
        
        int start = page * 30;
        int j = (num-1) - start;
        int end = start + 30;
        if (end > num) {
            end = num;
        }
        
        mvprintw(45, xMax/2 - strlen ("Page 1 / 1")/2 , "Page %d / %d", page + 1, pages);
        int a = 0;
        mvprintw(9, 27,"ID                                                           Nome                                                       Avaliacao Media                         ");
        char* cidade = malloc(30);
        int size = 30;
        for(int n = start; n < end; n++){
            if (a % 31 == 0) a *= 0;
            dateCombo *data = conv_Days_to_Date(ride_get_date(dbRides,ride_ids[j]));
            short distancia = ride_get_distance(dbRides,ride_ids[j]);
            ride_get_city(dbRides,ride_ids[j],cidade,&size);
            double tip = ride_get_tip(dbRides,ride_ids[j]);
            // fprintf(resultado,"%012d;%02d/%02d/%d;%d;%s;%.3f\n",ride_ids[n],data->day,data->month,data->year,distancia,cidade,tip);
            mvprintw(a + 11, 20,"%012d",ride_ids[j]);
            mvprintw(a + 11, 60,"%02d/%02d/%d",data->day,data->month,data->year);
            mvprintw(a + 11, 100,"%d",distancia);
            mvprintw(a + 11, 140,"%s",cidade);
            mvprintw(a + 11, 180,"%.3f",tip);
            a++;
            j--;
        }       
       
        // for (int i = start; i < end; i++) {
        //     if (a % 31 == 0) a *= 0;
        //     mvprintw(a + 11, 22, "%012d", get_id_driver_top_N(catalog_drivers, i));
        //     mvprintw(a + 11, 81, "%s", get_name_driver_top_N(catalog_drivers, i));
        //     mvprintw(a + 11, 152 , "%.3f", get_aval_med_top_N(catalog_drivers, i));
        //     mvprintw(a+11, 61, "|");
        //     mvprintw(a+11, 122, "|");
        //     mvprintw(a+11, 183, "|");
        //     a++;
        // }
        
        mvprintw(50, xMax/2 - strlen("Pressione 'N' para ver a próxima página, 'B' para a página anterior, 'Q' para voltar ao Menu Inicial")/2 , "Pressione 'N' para ver a próxima página, 'B' para a página anterior, 'Q' para voltar ao Menu Inicial");
        int ch = getch();
        switch (ch) {
        case 'n':
        case 'N':
            page++;
            if (page >= pages) {
            page = pages - 1;
            }
            break;
        case 'b':
        case 'B':
            page--;
            if (page < 0) {
            page = 0;
            }
            break;
        case 'q':
        case 'Q':
            done = 1;
            clear();
            queries_menu(dbDrivers,dbUsers,dbRides,dbStats);
            // queries_menu(x, y, catalog_users, catalog_drivers, catalog_rides, catalog_cities);
        }
    }
    
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

