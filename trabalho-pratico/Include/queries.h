#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void query1(char *ID, void *dbDrivers, void *dbUsers, short i);

void query1_UI(char *ID, void *dbDrivers, void *dbUsers, void *dbStats, void *dbRides);

void query2(char *N, void *dbDrivers, short i);

void query2_UI(char* N, void *dbDrivers,void *dbUsers,void *dbRides, void *dbStats);

void query3(char *ID, void *dbUsers, short i);

void query3_UI(char *Num, void *dbUsers,void *dbRides, void *dbDrivers, void *dbStats);

void query4(char *Cidade,void * dbStats,short i);

void query4_UI(char *Cidade,void * dbStats,void *dbUsers, void *dbRides, void *dbDrivers);

void query5(char* data1, char* data2, void *dbStats,short i);

void query5_UI(char* data1, char* data2, void *dbStats,void *dbUsers, void *dbRides,void *dbDrivers);

void query6(char* cidade, char* data1, char* data2, void *dbStats, void *dbRides,short i);

void query6_UI(char* cidade, char* data1, char* data2, void *dbStats, void *dbRides, void *dbUsers, void *dbDrivers);

void query7(char * N, char * cidade, void *dbStats, void *dbDrivers, short i);

void query8(char* gender, char* X, void *dbStats, void *dbRides, void *dbDrivers, void *dbUsers,short i);

void query9(char* data1, char* data2, void *dbStats, void *dbRides,short i);

void query9_UI(char* data1, char* data2, void *dbStats, void *dbRides, void *dbUsers, void *dbDrivers);

void answer_queries(void** input, void* USERS, void* DRIVERS, void* RIDES, void* STATS);

void free_queries(void** queries_p);

void* process_query(char** info);

void printq(void** queriesp);
