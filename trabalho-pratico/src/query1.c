#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/drivers.h"
#include "../Include/dates.h"
#define data_atual "09/10/2022"

void query1(char *ID, void *hash_users, void *hash_drivers, void *hash_rides){
    GHashTable* gtable = (GHashTable*) hash_drivers;    
    switch(isdigit(ID[0]))
    {
        case(1):
        struct driver *driver = g_hash_table_lookup(gtable,atoi(ID));
        if(get_account_status_driver(gtable,atoi(ID)) == 'a'){
            char *data = sprintf(data, "%s",get_birth_date_driver(hash_drivers,atoi(ID)));
            int i;
            char *filename = malloc(50);
            char *id = malloc(50);
            sprintf(id, "%d", i);
            filename = "../Resultados/command";
            filename = strcat(filename, id);
            filename = strcat(filename, "_output.txt");
            FILE *resultado = fopen(filename, "w");
            fprintf(resultado,"%s;%c;%d;%.3f;%d;%.3f\n",get_name_driver(hash_drivers,atoi(ID)),get_gender_driver(hash_drivers,atoi(ID)),get_idade_driver(hash_drivers,atoi(ID),data_atual,data),avaliacao_media,numero_viagens,total_gasto);
            fclose(filename);
            i++;
        }
        case(0):
        if(get_account_status_driver(gtable,ID) == 'a'){
            char *data = sprintf(data, "%s",get_birth_date_driver(hash_drivers,atoi(ID)));
            int i;
            char *filename = malloc(50);
            char *id = malloc(50);
            sprintf(id, "%d", i);
            filename = "../Resultados/command";
            filename = strcat(filename, id);
            filename = strcat(filename, "_output.txt");
            FILE *resultado = fopen(filename, "w");
            fprintf(resultado,"%s;%c;%d;%.3f;%d;%.3f\n",get_name_driver(hash_drivers,atoi(ID)),get_gender_driver(hash_drivers,atoi(ID)),get_idade_driver(hash_drivers,atoi(ID),data_atual,data),avaliacao_media,numero_viagens,total_gasto);
            fclose(filename);
            i++;     
        }
    }

}
