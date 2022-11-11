#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "drivers.h"
#include "users.h"
#include "rides.h"
#include "parser.h"

int main(void){

    FILE *drivers = fopen("./files/drivers.csv", "r");
        if(drivers == NULL) {
            perror("Opening drivers.csv: try another path");
        }
        void **DRIVERS = parser(drivers, ";\n\r", process_driver);
        free(DRIVERS);
        fclose(drivers);

    FILE *rides = fopen("./files/rides.csv", "r");
        if(rides == NULL) {
            perror("Opening rides.csv: try another path");
        } 
        void **RIDES = parser(rides, ";\n\r", process_ride);
        free(RIDES);
        fclose(rides);
    
    FILE *users = fopen("./files/users.csv", "r");
        if(users == NULL) {
            perror("Opening users.csv: try another path");
        }
        void **USERS = parser(users, ";\n\r", process_user);
        free(USERS);
        fclose(users);

}
