#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dateCombo{
    short day;
    short month;
    short year;
} dateCombo;

int main(){
    char date[] = "16/03/1955";
    char* data = strdup(date);
    char* token;
    char cycle = 0;
    short n_days = 0;
    short month_diff[] = {0,31,59,90,120,151,181,212,243,273,304,334};
    char post_Fev = 0;
    while((token = strtok_r(data,"/",&data))!= NULL){
        short date = atol(token);
        if(cycle == 0){
            n_days += date - 1;
        }

        else if(cycle == 1){
            if(date >= 3) post_Fev = 1;
            n_days += month_diff[date-1];
        }

        else{
            if(post_Fev == 1 && date%4 == 0) n_days++;
            if(date>2000) n_days + 1;
            for (size_t i = 1950; i < date; i++)
            {
                n_days += (i%4==0)*1 + 365; 
            }
        }
        cycle++;
    }
    printf("%hu\n",n_days);
    return n_days;
    
}


void * (*)(void **, void *, void *, void (*)(void *, void *, void *, void *, void *), void * (*)(void *, void *, void *, void *))

void * (*)(void **, void *, void *, void * (*)(void *, void *, void *, void *, void *), void * (*)(void *, void *, void *, void *))