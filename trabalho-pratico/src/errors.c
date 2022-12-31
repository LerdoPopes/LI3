#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include "../Include/errors.h"

int empty_error(char* error){
    if(error[0] == "\0" || error == NULL){
        return 1;
    }
    return 0;
}

int invalid_accStats(char* error){
    if (strcmp(tolower(error),"active") != 0 && strcmp(tolower(error),"inactive") != 0)
    {
        return 1;
    }
    return 0;
}

int invalid_carClass(char* error){
    if (strcmp(tolower(error),"basic") != 0 && strcmp(tolower(error),"premium") != 0 && strcmp(tolower(error),"green") != 0)
    {
        return 1;
    }
    return 0;
}


int invalid_Pint(char* error){
    for(int i = 0; error[i] != '\0'; i++){
        if(!(isdigit(error[i]))){
            return 1;
        }
    }
    return 0;
}

int invalid_Pdouble(char* error){
    int counter = 0;
    for (int i = 0; error[i] != '\0'; i++)
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