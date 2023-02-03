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

#define INIT_CITY  if (cityGP == NULL){\
            cities[city_counter] =  malloc(sizeof(struct city));\
            cities[city_counter]->total_money = 0;\
            char* c = strdup(city);\
            cities[city_counter]->city_name = c;\
            cities[city_counter]->num_rides = 0;\
            cities[city_counter]->num_drivers = 0;\
            cities[city_counter]->size = 256;\
            Info** drivers_array = malloc(sizeof(Info*)* 256);\
            GHashTable* drivers = g_hash_table_new(g_int_hash,g_int_equal);\
            cities[city_counter]->info = drivers_array;\
            cities[city_counter]->driversTmp = drivers;\
            g_hash_table_insert(cities_hashtable,cities[city_counter]->city_name,cities[city_counter]);\
            city_counter++;\
            cityGP = g_hash_table_lookup(cities_hashtable,city);\
        }       

#define INIT_DATES if (datesGP == NULL){\
            eachday[dates_counter] =  malloc(sizeof(eachDay));\
            eachday[dates_counter]->money = 0;\
            eachday[dates_counter]->day = dayte;\
            eachday[dates_counter]->num_trips = 0;\
            eachday[dates_counter]->size = 128;\
            eachday[dates_counter]->rides = malloc(sizeof(int)*128);\
            g_hash_table_insert(dates_hashtable,&(eachday[dates_counter]->day),eachday[dates_counter]);\
            dates_counter++;\
            datesGP = g_hash_table_lookup(dates_hashtable,&dayte);\
        }

#define GETTERS int id = ride_get_idArray(dbRides,i);\
        int driver_ID = ride_get_driver(dbRides,id);\
        ride_get_user(dbRides,id,user,&size_user);\
        short date = ride_get_date(dbRides,id);\
        ride_get_city(dbRides,id,city,&size_city);\
        double tip = ride_get_tip(dbRides,id);\
        short distance = ride_get_distance(dbRides,id);\
        short score_driver = ride_get_score_driver(dbRides,id);\
        short score_user = ride_get_score_user(dbRides,id);



typedef struct info{
    int id;
    int aval;
    int num_trips;
} Info;

typedef struct sexo{
    int id;
    short idade_d;
    short idade_u;
}Sexo;

struct city{
    
    char* city_name;
    double total_money;
    int num_rides;
    int size;
    int num_drivers;
    GHashTable* driversTmp;
    Info** info;
    int order;
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

    int nM;
    int nF;
    Sexo* males;
    Sexo* shemales; 
    int order1;
    int order2;
} Stats;



void *organize_statistics(void* dbUsers, void* dbRides, void* dbDrivers){
    int n = get_len_ride(dbRides);
    int size_cities = 16;
    
    Stats* stats = malloc(sizeof(Stats));
    GHashTable* cities_hashtable = g_hash_table_new(g_str_hash,g_str_equal);
    struct city** cities= malloc(sizeof(struct city*)*size_cities);
    int city_counter= 0;

    int size_dates = 1024;
    GHashTable* dates_hashtable = g_hash_table_new(g_int_hash,g_int_equal);
    eachDay** eachday = malloc(sizeof(eachDay*)*size_dates);
    int dates_counter = 0;

    int males_size = 256;
    int shemales_size = 256;
    int num_M = 0;
    int num_F = 0;
    Sexo* males = malloc(sizeof(Sexo*)*256);
    Sexo* shemales = malloc(sizeof(Sexo*)*256);

    char* user = malloc(50);
    char* city = malloc(30);
    int size_user = 50;
    int size_city = 30;
    for(int i = 0; i < n; i++){

        GETTERS
        double money = set_driver_stats(dbDrivers,&distance,&score_driver,&driver_ID,&tip,&date);
        set_user_stats(dbUsers,&distance,&score_user,user,&money,&date);
        
        
        //Estatisticas da query 4
        if(size_cities == city_counter){
            cities = realloc(cities, (size_cities*=2) * sizeof(struct city*));
        }
        gpointer cityGP = g_hash_table_lookup(cities_hashtable,city);
        INIT_CITY
        struct city* cityP = (struct city*) cityGP;
        cityP->total_money += money-tip;
        cityP->num_rides++;

        if(cityP->num_drivers == cityP->size){
            cityP->info = realloc(cityP->info, (cityP->size*=2) * sizeof(Info*));
        }

        //Estatisticas da Q7
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
        INIT_DATES
        eachDay* datesP = (eachDay*) datesGP;
        if(datesP->size == datesP->num_trips){
            datesP->rides = realloc(datesP->rides, (datesP->size*=2) * sizeof(int));
        }
        datesP->rides[datesP->num_trips] = id;
        datesP->num_trips++;
        datesP->money += money-tip;
        
        //Estatisticas da Q8
        char gender_D = driver_get_gender(dbDrivers,driver_ID);
        char gender_U = user_get_gender(dbUsers,user); 
        if(males_size == num_M){
            males = realloc(males,(males_size *=2)*sizeof(Sexo));
        }
        if(shemales_size == num_F){
            shemales = realloc(shemales,(shemales_size *=2)*sizeof(Sexo));
        }
        if(gender_D == gender_U){
            if(gender_D == 'M'){
                males[num_M].id = id;
                males[num_M].idade_d = driver_get_account_creation(dbDrivers,driver_ID);
                males[num_M].idade_u = user_get_account_creation(dbUsers,user);
                num_M++;
            }
            else{
                shemales[num_F].id = id;
                shemales[num_F].idade_d = driver_get_account_creation(dbDrivers,driver_ID);
                shemales[num_F].idade_u = user_get_account_creation(dbUsers,user);
                num_F++;
            }
        }

    }
    for (size_t i = 0; i < city_counter; i++)
    {
        g_hash_table_destroy(cities[i]->driversTmp);
    }
    order_by_dist(dbUsers);
    order_by_aval(dbDrivers);
    stats->cities = cities_hashtable;
    stats->cities_p = cities;
    stats->dates = dates_hashtable;
    stats->dates_p = eachday;
    stats->males = males;
    stats->shemales = shemales;
    stats->nF = num_F;
    stats->nM = num_M;
    stats->order1 = 0;
    stats->order2 = 0;
    free(user);
    free(city);
    return stats;
}


// typedef struct each_day{
    
//     int day;
//     int num_trips;
//     int size;
//     double money;
//     int* rides;

// } eachDay;


// typedef struct Statistics{
//     GHashTable* cities;
//     struct city** cities_p;

//     GHashTable* dates;
//     eachDay** dates_p;

//     int nM;
//     int nF;
//     Sexo* males;
//     Sexo* shemales; 
//     int order;
// } Stats;
void free_Stats(void* info){
    Stats* stats = (Stats*) info;
    for(int i = 0; stats->cities_p[i];i++){
        for(int j = 0; stats->cities_p[i]->info[j];j++){
            free(stats->cities_p[i]->info[j]);
        }
        free(stats->cities_p[i]->city_name);
        free(stats->cities_p[i]->info);
        free(stats->cities_p[i]);
    }
    free(stats->cities_p);
    g_hash_table_destroy(stats->cities);

    for (size_t i = 0;stats->dates_p[i]; i++)
    {
        free(stats->dates_p[i]->rides);
    }
    free(stats->dates_p);
    g_hash_table_destroy(stats->dates);
    
    free(stats->males);
    free(stats->shemales);
    free(stats);
}

void *order_by_account_age(void *info, char *gender, void* dbUsers, void* dbDrivers, void* dbRides)
{
    Stats *INFO = (Stats *)info;
    if(strcmp(gender,"M")==0){
        Sexo *Gender = INFO->males;
        if(Gender == NULL){
        return NULL;
        }
        int n = INFO->nM;

         if (INFO->order1 != 1){
            for (int gap = n/2; gap > 0; gap /= 2)
            {
                for (int i = gap; i < n; i += 1)
                {
                    Sexo genero = Gender[i];

                    int id = genero.id;
                    short user_age = genero.idade_u;
                    short driver_age = genero.idade_d;
                    int j;

                    for (j = i; j >= gap 
                    && ((Gender[j - gap].idade_d)>driver_age 
                    || ((Gender[j - gap].idade_d)==driver_age && (Gender[j - gap].idade_u)>user_age)
                    || ((Gender[j - gap].idade_d)==driver_age && (Gender[j - gap].idade_u)==user_age && (Gender[j - gap].id) > id)); j -= gap)
                        Gender[j] = Gender[j - gap];

                    Gender[j] = genero;
                }
            }
            INFO->order1=1;
        }
    }
    else if(strcmp(gender,"F")==0){
        Sexo *Gender = INFO->shemales;
        if(Gender == NULL){
        return NULL;
        }
        printf("aa\n");
        int n = INFO->nF;
         if (INFO->order2 != 1){
            for (int gap = n/2; gap > 0; gap /= 2)
            {
                for (int i = gap; i < n; i += 1)
                {
                    Sexo genero = Gender[i];
                    short driver_age = genero.idade_d;
                    short user_age = genero.idade_u;
                    int id = genero.id;


                    int j;
                    for (j = i; j >= gap 
                    && ((Gender[j - gap].idade_d)>driver_age 
                    || ((Gender[j - gap].idade_d)==driver_age && (Gender[j - gap].idade_u)>user_age)
                    || ((Gender[j - gap].idade_d)==driver_age && (Gender[j - gap].idade_u)==user_age && (Gender[j - gap].id) > id)); j -= gap)
                        Gender[j] = Gender[j - gap];

                    Gender[j] = genero;
                }
            }
            INFO->order2 = 1;    
        }
    }
}

void *order_by_aval_m(void *info, char *cidade)
{
    Stats *INFO = (Stats *)info;
    City *Cidade = g_hash_table_lookup(INFO->cities,cidade);
    if(Cidade == NULL){
        return NULL;
    }
    Info **infos = Cidade->info;
    int n = Cidade->num_drivers;
    if (Cidade->order != 1){
        for (int gap = n/2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i += 1)
            {
                Info* temp = infos[i];
                double media = (double) (temp->aval)/(temp->num_trips);
                //printf("%.3f\n",media);


                int j;
                for (j = i; j >= gap 
                && ((double)(infos[j - gap]->aval)/(infos[j - gap]->num_trips)>media 
                || ((double)(infos[j - gap]->aval)/(infos[j - gap]->num_trips)==media && (infos[j - gap]->id)>temp->id)); j -= gap)
                    infos[j] = infos[j - gap];

                infos[j] = temp;
            }
        }
         Cidade->order = 1;
    }
}

// int compar_int(const void *a, const void *b) {
//     int _a = * (int*) a;
//     int _b = * (int*) b;
//     return (_a > _b) - (_a < _b);
// }



void *order_by_distance(void *dbRides,int *bla, int Num)
{
    for (int gap = Num/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < Num; i += 1)
        {
            int temp = bla[i];
            short distance = ride_get_distance(dbRides,temp);
            short date = ride_get_date(dbRides,temp);
            int j;
            for (j = i; j >= gap 
            && ((ride_get_distance(dbRides,bla[j - gap])) > distance
            || ((ride_get_distance(dbRides,bla[j - gap])) == distance && (ride_get_date(dbRides,bla[j - gap])) > date)
            || ((ride_get_distance(dbRides,bla[j - gap])) == distance && (ride_get_date(dbRides,bla[j - gap])) == date && bla[j - gap] > temp)); j -= gap)
                bla[j] = bla[j - gap];
            bla[j] = temp;
        }
    } 
}



int city_get_num_drivers(void *stats_d,char *ID){
    Stats* stats = (Stats*) stats_d;
    gconstpointer id = (gconstpointer)ID;
    gpointer cityp = g_hash_table_lookup(stats->cities, id);
    City* city = (City*) cityp;
    if(city == NULL){
        return 0;
    }
    return city->num_drivers;
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

int city_get_info_id(void *stats_d,char *ID, int i){
    Stats* stats = (Stats*) stats_d;
    gconstpointer id = (gconstpointer)ID;
    gpointer cityp = g_hash_table_lookup(stats->cities, id);
    City* city = (City*) cityp;
    return city->info[i]->id;
}

int city_get_info_aval(void *stats_d,char *ID, int i){
    Stats* stats = (Stats*) stats_d;
    gconstpointer id = (gconstpointer)ID;
    gpointer cityp = g_hash_table_lookup(stats->cities, id);
    City* city = (City*) cityp;
    return city->info[i]->aval;
}

int city_get_info_num_trips(void *stats_d,char *ID, int i){
    Stats* stats = (Stats*) stats_d;
    gconstpointer id = (gconstpointer)ID;
    gpointer cityp = g_hash_table_lookup(stats->cities, id);
    City* city = (City*) cityp;
    return city->info[i]->num_trips;
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

int info_get_id(void *stats_d,int ID,int i){
    Stats* stats = (Stats*) stats_d;
    gconstpointer id = (gconstpointer)&ID;
    gpointer datep = g_hash_table_lookup(stats->dates, id);
    eachDay* date = (eachDay*) datep;
    if(date == NULL) return 0;
    return date->rides[i];
}

int ride_male_get_id(void *stats_d,int i){
    Stats* stats = (Stats*) stats_d;
    return stats->males[i].id;
}

int ride_shemale_get_id(void *stats_d,int i){
    Stats* stats = (Stats*) stats_d;
    return stats->shemales[i].id;
}

int gender_get_nM(void *stats_d){
    Stats* stats = (Stats*) stats_d;
    return stats->nM;
}

int gender_get_nF(void *stats_d){
    Stats* stats = (Stats*) stats_d;
    return stats->nF;
}

short male_driver_get_age(void *stats_d,int i){
    Stats* stats = (Stats*) stats_d;
    //printf("%u\n",stats->males[i].idade_d);
    return stats->males[i].idade_d;
}

short male_user_get_age(void *stats_d,int i){
    Stats* stats = (Stats*) stats_d;
    //printf("%u\n",stats->males[i].idade_u);
    return stats->males[i].idade_u;
}

short shemale_driver_get_age(void *stats_d,int i){
    Stats* stats = (Stats*) stats_d;
    return stats->shemales[i].idade_d;
}

short shemale_user_get_age(void *stats_d,int i){
    Stats* stats = (Stats*) stats_d;
    return stats->shemales[i].idade_u;
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