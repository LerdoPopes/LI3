#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include "../Include/errors.h"

int empty_error(char* error){
    if(error[0]){
        return 0;
    }
    return 1;
}

int invalid_accStats(char* error){
    for(int i = 0; error[i]; i++){
        error[i] = tolower(error[i]);
    }
    if (strcmp(error,"active") != 0 && strcmp(error,"inactive") != 0)
    {
        return 1;
    }
    return 0;
}

int invalid_carClass(char* error){
    for(int i = 0; error[i]; i++){
        error[i] = tolower(error[i]);
    }
    if (strcmp(error,"basic") != 0 && strcmp(error,"premium") != 0 && strcmp(error,"green") != 0)
    {
        return 1;
    }
    return 0;
}


int invalid_Pint(char* error){
    if(!error[0]){
        return 1;
    }
    for(int i = 0; error[i]; i++){
        if(!(isdigit(error[i]))){
            return 1;
        }
    }
    return 0;
}

int invalid_Pdouble(char* error){
    int counter = 0;
    if(!error[0]){
        return 1;
    }
    for (int i = 0; error[i]; i++)
    {
        if(error[i] == '.'){
            counter++;
        }
        if(counter > 1 || (!(isdigit(error[i])) && error[i] != '.')){
            return 1;
        }
    }
    return 0;
}