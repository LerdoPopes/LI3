#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/rides.h"
#include "../Include/dates.h"
#include "../Include/statistics.h"
#include "../Include/queries.h"
#include <ctype.h>
#include <math.h>


typedef struct info{
    int id;
    int aval;
    int num_trips;
} Info;

struct city{
    
    char* city_name;
    double total_money;
    int num_rides;
    int size;
    int num_drivers;
    GHashTable* driversTmp;
    Info** info;
};

typedef struct each_day{
    
    int day;
    int num_trips;
    int size;
    double money;
    int* rides;

} eachDay;


typedef struct Statistics{
    GHashTable* cities;
    struct city** cities_p;

    GHashTable* dates;
    eachDay** dates_p;
} Stats;



void *organize_statistics(void* dbUsers, void* dbRides, void* dbDrivers){
    int n = get_len_ride(dbRides);
    int size_cities = 16;
    
    Stats* stats = malloc(sizeof(Stats*));
    GHashTable* cities_hashtable = g_hash_table_new(g_str_hash,g_str_equal);
    struct city** cities= malloc(sizeof(struct city*)*size_cities);
    int city_counter= 0;

    int size_dates = 1024;
    GHashTable* dates_hashtable = g_hash_table_new(g_int_hash,g_int_equal);
    eachDay** eachday = malloc(sizeof(eachDay*)*size_dates);
    int dates_counter = 0;

    for(int i = 0; i < n; i++){

        int id = ride_get_idArray(dbRides,i);
        int driver_ID = ride_get_driver(dbRides,id);
        char *user = ride_get_user(dbRides,id);
        short date = ride_get_date(dbRides,id);
        char *city = ride_get_city(dbRides,id);
        double tip = ride_get_tip(dbRides,id);
        short distance = ride_get_distance(dbRides,id);
        short score_driver = ride_get_score_driver(dbRides,id);
        short score_user = ride_get_score_user(dbRides,id);

        double *money = (double *) set_driver_stats(dbDrivers,&distance,&score_driver,&driver_ID,&tip,&date);
        set_user_stats(dbUsers,&distance,&score_user,user,money,&date);
        
        
        //Estatisticas da query 4
        if(size_cities == city_counter){
            cities = realloc(cities, (size_cities*=2) * sizeof(struct city*));
        }
        gpointer cityGP = g_hash_table_lookup(cities_hashtable,city);
        if (cityGP == NULL){
            cities[city_counter] =  malloc(sizeof(struct city));
            cities[city_counter]->total_money = 0;
            char* c = strdup(city);
            cities[city_counter]->city_name = c;
            cities[city_counter]->num_rides = 0;
            cities[city_counter]->num_drivers = 0;
            cities[city_counter]->size = 256;
            Info** drivers_array = malloc(sizeof(Info*)* 256);
            GHashTable* drivers = g_hash_table_new(g_int_hash,g_int_equal);
            cities[city_counter]->info  = drivers_array;
            cities[city_counter]->driversTmp = drivers;
            g_hash_table_insert(cities_hashtable,cities[city_counter]->city_name,cities[city_counter]);
            city_counter++;
            cityGP = g_hash_table_lookup(cities_hashtable,city);

        }
        struct city* cityP = (struct city*) cityGP;
        cityP->total_money += *money-tip;
        cityP->num_rides++;

        if(cityP->num_drivers == cityP->size){
            cityP->info = realloc(cityP->info, (cityP->size*=2) * sizeof(Info*));
        }

        gpointer driverGP = g_hash_table_lookup(cityP->driversTmp,&driver_ID);
        if(driverGP == NULL){
            cityP->info[cityP->num_drivers] = malloc(sizeof(Info));
            cityP->info[cityP->num_drivers]->aval = 0;
            cityP->info[cityP->num_drivers]->num_trips = 0;
            cityP->info[cityP->num_drivers]->id = driver_ID;
            g_hash_table_insert(cityP->driversTmp,&cityP->info[cityP->num_drivers]->id,cityP->info[cityP->num_drivers]);
            cityP->num_drivers++;
            driverGP = g_hash_table_lookup(cityP->driversTmp,&driver_ID);
        }
        Info* driverP = (Info*) driverGP;
        driverP->aval += score_driver;
        driverP->num_trips++;






        //Estatisticas da query 5
        if(size_dates == dates_counter){
            eachday = realloc(eachday, (size_dates*=2) * sizeof(eachDay*));
        }
        int dayte = (int) date;
        gpointer datesGP = g_hash_table_lookup(dates_hashtable,&dayte);
        if (datesGP == NULL){
            eachday[dates_counter] =  malloc(sizeof(eachDay));
            eachday[dates_counter]->money = 0;
            eachday[dates_counter]->day = dayte;
            eachday[dates_counter]->num_trips = 0;
            eachday[dates_counter]->size = 128;
            eachday[dates_counter]->rides = malloc(sizeof(int)*128);
            g_hash_table_insert(dates_hashtable,&(eachday[dates_counter]->day),eachday[dates_counter]);
            dates_counter++;
            datesGP = g_hash_table_lookup(dates_hashtable,&dayte);
        }
        eachDay* datesP = (eachDay*) datesGP;
        if(datesP->size == datesP->num_trips){
            datesP->rides = realloc(datesP->rides, (datesP->size*=2) * sizeof(int));
        }
        
        datesP->rides[datesP->num_trips] = id;
        datesP->num_trips++;
        datesP->money += *money-tip;
        free(money);
        free(city);
        free(user);
    
    }
    stats->cities = cities_hashtable;
    stats->cities_p = cities;
    stats->dates = dates_hashtable;
    stats->dates_p = eachday;
    return stats;
}

double city_get_money(void *stats_d,char *ID){
    Stats* stats = (Stats*) stats_d;
    gconstpointer id = (gconstpointer)ID;
    gpointer cityp = g_hash_table_lookup(stats->cities, id);
    City* city = (City*) cityp;
    return city->total_money;
}

int city_get_num_rides(void *stats_d,char *ID){
    Stats* stats = (Stats*) stats_d;
    gconstpointer id = (gconstpointer)ID;
    gpointer cityp = g_hash_table_lookup(stats->cities, id);
    City* city = (City*) cityp;
    //printf("%u\n",city->num_rides);
    return city->num_rides;
}

int cityValid(void* STATS, char* Cidade){
    Stats* stats = (Stats*) STATS;
    gconstpointer id = (gconstpointer)Cidade;
    gpointer cityp = g_hash_table_lookup(stats->cities, id);
    City* city = (City*) cityp;
    return (city!=NULL);
}

int date_get_num_trips(void *stats_d,int ID){
    Stats* stats = (Stats*) stats_d;
    gconstpointer id = (gconstpointer)&ID;
    gpointer datep = g_hash_table_lookup(stats->dates, id);
    eachDay* date = (eachDay*) datep;
    if(date == NULL) return 0;
    return date->num_trips;
}

double date_get_money(void *stats_d,int ID){
    Stats* stats = (Stats*) stats_d;
    gconstpointer id = (gconstpointer)&ID;
    gpointer datep = g_hash_table_lookup(stats->dates, id);
    eachDay* date = (eachDay*) datep;
    if(date == NULL) return 0; 
    return date->money;
}

int date_get_ride(void *stats_d,int ID,int i){
    Stats* stats = (Stats*) stats_d;
    gconstpointer id = (gconstpointer)&ID;
    gpointer datep = g_hash_table_lookup(stats->dates, id);
    eachDay* date = (eachDay*) datep;
    if(date == NULL) return 0;
    return date->rides[i];
}



































void print_braga(void* STATS){
    Stats* stats = (Stats*) STATS;

    gpointer braga = g_hash_table_lookup(stats->cities, "Braga");
    struct city* BRAGA = (struct city*) braga; 
    printf("%.3f\n", BRAGA->total_money);

    printf("%.3f\n",stats->cities_p[3]->total_money);
}

void print_date(void* STATS){
    Stats* stats = (Stats*) STATS;
    int day = 23321;
    dateCombo* aaaa= conv_Days_to_Date(23321);
    printf("%u/%u/%u\n",aaaa->day,aaaa->month,aaaa->year);
    gpointer BRAGA = g_hash_table_lookup(stats->dates,&day);
    eachDay* braga = (eachDay*) BRAGA;
    printf("%d\n",braga->num_trips);
}

// double city_get_money_notip(void *stats_p,char *ID){
//     Stats* stats = (Stats*) stats_p;
//     gconstpointer id = (gconstpointer)ID;
//     gpointer cityp = g_hash_table_lookup(stats->cities, id);
//     City* city = (City*) cityp;
//     return city->total_money_notip;
// }