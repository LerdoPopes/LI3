#ifndef STATISTICS_H
#define STATISTICS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct city City;

typedef struct each_day eachDay;

typedef struct Statistics Stats;

void *organize_statistics(void* dbUsers, void* dbRides, void* dbDrivers);

void print_braga(void* STATS);

void print_date(void* STATS);

double city_get_money(void *stats_d,char *ID);

double city_get_money_notip(void *stats_p,char *ID);

int city_get_num_rides(void *stats_d,char *ID);

int date_get_num_trips(void *stats_d,int ID);

double date_get_money(void *stats_d,int ID);

int date_get_ride(void *stats_d,int ID,int i);

void *order_by_aval_m(void *info, char *cidade);

void *order_by_account_age(void *info, char *gender);

void *order_by_distance(void *dbRides,int *bla, int Num);

int city_get_num_drivers(void *stats_d,char *ID);

int city_get_info_id(void *stats_d,char *ID, short i);

int city_get_info_aval(void *stats_d,char *ID, short i);

int city_get_info_num_trips(void *stats_d,char *ID, short i);

int cityValid(void* STATS, char* Cidade);

int ride_male_get_id(void *stats_d,int i);

int ride_shemale_get_id(void *stats_d,int i);

int gender_get_nM(void *stats_d);

int gender_get_nF(void *stats_d);

short male_driver_get_age(void *stats_d,int i);

short male_user_get_age(void *stats_d,int i);

short shemale_driver_get_age(void *stats_d,int i);

short shemale_user_get_age(void *stats_d,int i);

int compar_int(const void *a, const void *b);

#endif