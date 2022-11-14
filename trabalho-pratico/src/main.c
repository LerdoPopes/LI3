#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/rides.h"
#include "../Include/parser.h"
#include "../Include/dates.h"


int main(void){

    FILE *drivers = fopen("./drivers.csv", "r");
        if(drivers == NULL) {
            perror("Opening drivers.csv: try another path");
        }
        //void **DRIVERS = parser(drivers, ";\n\r", process_driver);
        //free(DRIVERS);
        fclose(drivers);

    FILE *rides = fopen("./rides.csv", "r");
        if(rides == NULL) {
            perror("Opening rides.csv: try another path");
        } 
        //void **RIDES = parser(rides, ";\n\r", process_ride);
        //free(RIDES);
        fclose(rides);

    FILE *users = fopen("./users.csv", "r");
        if(users == NULL) {
            perror("Opening users.csv: try another path");
        }
        void *USERS = parser(users, ";\n\r", process_user,organize_user,arrange_user);
        char username[] = "LuciaPinto36";
        print_user(username, USERS);
        free_user(USERS);
        fclose(users);

}
