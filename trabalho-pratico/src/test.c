#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dateCombo{
    short day;
    short month;
    short year;
} dateCombo;

int main(){
    short days = 1095;
    size_t i = 1950;
    short month_diff[] = {0,31,59,90,120,151,181,212,243,273,304,334,365};
    dateCombo* dateCombo = malloc(sizeof(dateCombo));
    dateCombo->day = 1;
    dateCombo->month = 1;
    for (; days >=365; i++)
    {
        if(i%4 == 0) days--;
        days-=365;
    }
    dateCombo->year = i;
    if ((dateCombo->year)%4==0 && days>59){
        days--;    
    }
    for (i = 0; month_diff[i+1]<=days; i++);
    dateCombo->month += i;
    days-=month_diff[i];
    dateCombo->day += days;
    printf("%d\n",dateCombo->day);
    printf("%d\n",dateCombo->month);
    printf("%d\n",dateCombo->year);
}
