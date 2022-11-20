#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITDATE 26.579 // 1 de Janeiro 1950

typedef struct dateCombo{
    short day;
    short month;
    short year;
} dateCombo;

short calc_Date(char* data);

short idade(short data_atual,short birth_date);

dateCombo* conv_Days_to_Date(short days);