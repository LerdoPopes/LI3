#ifndef USER_I
#define USER_I

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

void query_menu(int opçao,void *DRIVERS,void *USERS,void *RIDES,void *STATS);

void queries_menu(void *DRIVERS,void *USERS, void *RIDES, void *STATS);

#endif