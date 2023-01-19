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

#endif