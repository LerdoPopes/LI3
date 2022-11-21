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

int main(int argc, char *argv){

    FILE *users = fopen("./users.csv", "r");
        if(users == NULL) {
            perror("Opening users.csv: try another path");
        }
        void *USERS = parser(users, ";\n\r", process_user,organize_user,NULL,NULL,NULL,NULL);
        fclose(users);
    
    FILE *drivers = fopen("./drivers.csv", "r");
        if(drivers == NULL) {
            perror("Opening drivers.csv: try another path");
        }
        void *DRIVERS = parser(drivers, ";\n\r", process_driver,organize_driver,NULL,NULL,NULL,NULL);
        fclose(drivers);

    FILE *rides = fopen("./rides.csv", "r");
        if(rides == NULL) {
            perror("Opening rides.csv: try another path");
        } 
        void *RIDES = parser(rides, ";\n\r", process_ride,organize_rides,DRIVERS,USERS,set_user_stats,set_driver_stats);
        fclose(rides);
    
    // FILE *input = fopen("./input.txt", "r");
    //     if(input == NULL){
    //         perror("Opening input.txt: try another path");
    //     }
    //     //void *INPUT = parser_queries(input," \n\r");
    //     fclose(input);

    // for(short i = 0, j = 1; INPUT[i] != NULL;i++,j++){
    //     switch(INPUT[i][0]){
    //         case(1):                                              <------    Criador de command_outputs possivemente porreiro 
    //             query1(INPUT[i][1],DRIVERS,USERS,j);
    //             break;
    //         case(2):
    //             query2();
    //             break;
    //         case(3):
    //             query3();
    //             break;
    //     }
    // }

    query1("SaCruz110",DRIVERS,USERS,1);
    //answer_q2_driver(output,DRIVERS,1,2);
    free_rides(RIDES);
    free_driver(DRIVERS);
    free_user(USERS);

    int time = clock();
    printf("%f\n",(float)time/CLOCKS_PER_SEC);  
}



