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
    //     printf(
    //         "%s\n",
    //         ((Driver *) DRIVERS[1])->account_status,
    //         ((Driver *) DRIVERS[i])->name,
    //         ((Driver *) DRIVERS[i])->birth_date
    //         // ((Driver *) DRIVERS[i])-> ,
    //         // ((Driver *) DRIVERS[i])-> ,
    //         // ((Driver *) DRIVERS[i])->
    //         // ((Driver *) DRIVERS[i])->
    //         // ((Driver *) DRIVERS[i])->
    //         // ((Driver *) DRIVERS[i])->
    //     );
    // }
    // for(size_t i = 0; DRIVERS[i] != NULL; ++i) {
    //     free(((Driver *) DRIVERS[i])->id);
    //     free(((Driver *) DRIVERS[i])->name);
    //     free(((Driver *) DRIVERS[i])->birth_date);
    //     free(DRIVERS[i]);
    // }
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
