#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/rides.h"
#include "../Include/parser.h"
#include "../Include/queries.h"
#include "../Include/statistics.h"
#include "../Include/userinterface.h"

int main(int argc, char **argv){
// Modo Interativo 
    if(argc < 2){
        initscr();
        cbreak();
        curs_set(0);
        int height,width,start_y,start_x;
        int yMax, xMax;
        char input[100];
        getmaxyx(stdscr,yMax,xMax);
        height = 30;
        width = 200;
        start_y = start_x = 10;

        WINDOW * win = newwin(10,xMax - 12,yMax/2,5);
        refresh();

        box(win,0,0);
        mvwprintw(win,1,1,"Insira a path dos ficheiros CSV:");
        wrefresh(win);
        mvwgetstr(win,1,35,input);

        char aux[4096];
        strcpy(aux,input);
        strcat(aux,"/users.csv");
        FILE *users = fopen(aux, "r");
            void *USERS = parser(users, ";\n\r", process_user,organize_user,0);
            fclose(users);

        strcpy(aux,input);
        strcat(aux,"/drivers.csv");
        FILE *drivers = fopen(aux, "r");
            void *DRIVERS = parser(drivers, ";\n\r", process_driver,organize_driver,0);
            fclose(drivers);

        strcpy(aux,input);
        strcat(aux,"/rides.csv");
        FILE *rides = fopen(aux, "r");
            void *RIDES = parser(rides, ";\n\r", process_ride,organize_rides);
            fclose(rides);

        void* STATS = organize_statistics(USERS,RIDES,DRIVERS);
                
        if(strcmp(input,".")==0){
            werase(win);
            wrefresh(win);
            queries_menu(DRIVERS,USERS,RIDES,STATS);
        }

        endwin();
        return 0;
    }
// Modo Batch 
    else{
    char aux[4096];
    strcpy(aux,argv[1]);
    strcat(aux,"/users.csv");
    FILE *users = fopen(aux, "r");
        if(users == NULL) {
            perror("Opening users.csv: try another path");
        }
        void *USERS = parser(users, ";\n\r", process_user,organize_user,0);
        fclose(users);

    strcpy(aux,argv[1]);
    strcat(aux,"/drivers.csv");
    FILE *drivers = fopen(aux, "r");
        if(drivers == NULL) {
            perror("Opening drivers.csv: try another path");
        }
        void *DRIVERS = parser(drivers, ";\n\r", process_driver,organize_driver,0);
        fclose(drivers);

    strcpy(aux,argv[1]);
    strcat(aux,"/rides.csv");
    FILE *rides = fopen(aux, "r");
        if(rides == NULL) {
            perror("Opening rides.csv: try another path");
        } 
        void *RIDES = parser(rides, ";\n\r", process_ride,organize_rides);
        fclose(rides);
    
    char *Input = (char *)malloc(30 * sizeof(char));
    FILE *input = fopen(argv[2], "r");
        if(input == NULL){
            perror("Opening input.txt: try another path");
        }
        void **INPUT = parse_query(input,process_query);
        fclose(input);
    void* STATS = organize_statistics(USERS,RIDES,DRIVERS);
    answer_queries(INPUT,USERS,DRIVERS,RIDES,STATS);
    free_rides(RIDES);
    free_driver(DRIVERS);
    free_user(USERS);
    free_Stats(STATS);
    free_queries(INPUT);
    free(Input);
    clock_t time = clock();
    printf("Tempo total de Execução: %f\n",(float)time/CLOCKS_PER_SEC);  
}
}


