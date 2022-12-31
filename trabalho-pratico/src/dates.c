#include "../Include/dates.h"

unsigned short calc_Date(char* data){
    char* token;
    char cycle = 0;
    short n_days = 0;
    short month_diff[] = {0,31,59,90,120,151,181,212,243,273,304,334};
    char post_Fev = 0;
    while((token = strtok_r(data,"/",&data))!= NULL){
        int date = atol(token);
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
    return n_days;
}

dateCombo* conv_Days_to_Date(short days){
    size_t i = 1950;
    short month_diff[] = {0,31,59,90,120,151,181,212,243,273,304,334,365};
    dateCombo* dateCombo = malloc(sizeof(dateCombo));
    dateCombo->day = 1;
    dateCombo->month = 1;
    for (; days > 365; i++)
    {
        if(i%4 == 0) days--;
        days -= 365;
    }
    dateCombo->year = i;
    if ((dateCombo->year)%4==0 && days>59){
        days--;     
    }
    for (i = 0; month_diff[i+1]<=days; i++);
    dateCombo->month += i;
    days-=month_diff[i];
    dateCombo->day += days;
    return dateCombo;
}

short idade(short birth_date){
    dateCombo* dateCombo = conv_Days_to_Date(birth_date);
    short idade = 0;
    if (dateCombo->month<10 || (dateCombo->month==10 && dateCombo->day<=9))
    {
        idade = 2022-dateCombo->year;
    }
    else{
        idade = 2022-dateCombo->year-1;
    }
    free(dateCombo);
    return idade;
}

int invalid_date(char* error){
    if(
        !(isdigit(error[0])) 
        || !(isdigit(error[1])) 
        || error[2] != '/' 
        || isdigit(error[3]) 
        || isdigit(error[4]) 
        || error[5] != '/' 
        || isdigit(error[6]) 
        || isdigit(error[7]) 
        || isdigit(error[8]) 
        || isdigit(error[9]) 
        || error[10] != "\0"){
        return 1;
    }
    return 0;
}