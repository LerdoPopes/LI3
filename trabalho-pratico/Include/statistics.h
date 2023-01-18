#ifndef STATISTICS_H
#define STATISTICS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void *organize_statistics(void* dbUsers, void* dbRides, void* dbDrivers);

void print_braga(void* STATS);

void print_date(void* STATS);

#endif