#ifndef DATES_H
#define DATES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define INITDATE 26.579 // 1 de Janeiro 1950
//#pragma once 

typedef struct dateCombo {
    short day;
    short month;
    short year;
} dateCombo;

unsigned short calc_Date(char* data);

short idade(short birth_date);

dateCombo* conv_Days_to_Date(short days);

int invalid_date(char* error);

#endif
