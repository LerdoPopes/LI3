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
    //     for(size_t i = 0; i < 9 ; ++i) {
    //         printf(
    //             "%s;%s;%c;%c;%c;%c\n",
    //             ((User *) USERS[i])->username,
    //             ((User *) USERS[i])->name,
    //             ((User *) USERS[i])->gender,
    //             ((User *) USERS[i])->birth_date,
    //             ((User *) USERS[i])->account_creation,
    //             ((User *) USERS[i])->account_status
    //     );
    // }
    // for(size_t i = 0; i < 9 ; ++i) {
    //     free(((User *) USERS[i])->username);
    //     free(((User *) USERS[i])->name);
    //     free(((User *) USERS[i])->gender);
    //     free(((User *) USERS[i])->birth_date);
    //     free(((User *) USERS[i])->account_creation);
    //     free(((User *) USERS[i])->account_status);
    //     free(USERS[i]);
    // }
        free(USERS);
        fclose(users);

}
