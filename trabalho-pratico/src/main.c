#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/rides.h"
#include "../Include/parser.h"
#include "../Include/queries.h"
#include "../Include/statistics.h"

int main(int argc, char **argv){
    if(argc < 2){
        perror("Not enough arguments are being used: try again");
    }
    else{
    char *aux = (char *)malloc(1000 * sizeof(char));
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
    printf("aa%d\n",isDriver(DRIVERS,45));
    void* STATS = organize_statistics(USERS,RIDES,DRIVERS);
    answer_queries(INPUT,USERS,DRIVERS,RIDES,STATS);
    //print_braga(STATS);
    //print_date(STATS);
    free_rides(RIDES);
    free_driver(DRIVERS);
    free_user(USERS);
    free_queries(INPUT);
    free(aux);
    free(Input);
    clock_t time = clock();
    printf("Tempo total de Execução: %f\n",(float)time/CLOCKS_PER_SEC);  
}
}


