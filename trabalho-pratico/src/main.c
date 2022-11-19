#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/rides.h"
#include "../Include/parser.h"

int main(void){

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
    
    print_driver(DRIVERS);
    




    free_rides(RIDES);
    free_driver(DRIVERS);
    free_user(USERS);
    int time = clock();
    printf("%f\n",(float)time/CLOCKS_PER_SEC);
    
}
