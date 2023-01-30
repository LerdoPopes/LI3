#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void query1(char *ID, void *dbDrivers, void *dbUsers, short i);

void query2(char *N, void *dbDrivers, short i);

void query3(char *ID, void *dbUsers, short i);

void query4(char *Cidade,void * dbStats,short i);

void query5(char* data1, char* data2, void *dbStats,short i);

void query6(char* cidade, char* data1, char* data2, void *dbStats, void *dbRides,short i);

void query7(char * N, char * cidade, void *dbStats, void *dbDrivers, short i);

void query8(char* gender, char* X, void *dbStats, void *dbRides, void *dbDrivers, void *dbUsers,short i);

void query9(char* data1, char* data2, void *dbStats, void *dbRides,short i);

void answer_queries(void** input, void* USERS, void* DRIVERS, void* RIDES, void* STATS);

void free_queries(void** queries_p);

void* process_query(char** info);

void printq(void** queriesp);
