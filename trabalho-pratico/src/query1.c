#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/dates.h"
#include <ctype.h>
#define data_atual "09/10/2022"

void query1(char *ID, void *hash_drivers){
    // switch(isdigit(ID[0]))
    // {
    //     case(1):
        gconstpointer id = (gconstpointer) &ID;
        Driver *driver = g_hash_table_lookup(hash_drivers,id);
        printf("%s",driver_get_name(driver));
        // if(driver_get_account_status(driver) == 'a'){
            // char *data;
            // char *filename = malloc(50);
            // char *id = malloc(50);
            // sprintf(data, "%s",driver_get_birth_date(driver));
            // sprintf(id, "%d", i);
            // filename = "../Resultados/command";
            // filename = strcat(filename, id);
            // filename = strcat(filename, "_output.txt");
            // FILE *resultado = fopen(filename, "w");
            // fprintf(resultado,"%s;%c;%d\n",driver_get_name(driver),driver_get_gender(driver),driver_get_idade(driver,data_atual,data));//avaliacao_media,numero_viagens,total_gasto);
            // fclose(resultado);     
        }
    //     case(0):
    //     User *user = g_hash_table_lookup(hash_users,ID);
    //     if(user_get_account_status(user) == 'a'){
    //         char *data;
    //         char *filename = malloc(50);
    //         char *id = malloc(50);
    //         sprintf(data, "%s",user_get_birth_date(user));
    //         sprintf(id, "%d", i);
    //         filename = "../Resultados/command";
    //         filename = strcat(filename, id);
    //         filename = strcat(filename, "_output.txt");
    //         FILE *resultado = fopen(filename, "w");
    //         fprintf(resultado,"%s;%c;%d\n",user_get_name(user),user_get_gender(user),user_get_idade(user,data_atual,data));//avaliacao_media,numero_viagens,total_gasto);
    //         fclose(resultado); 
    //     }
    // }
//}
//}