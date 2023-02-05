#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <time.h>
#include <ncurses.h>
#include <sys/resource.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/rides.h"
#include "../Include/parser.h"
#include "../Include/queries.h"
#include "../Include/statistics.h"
#include "../Include/userinterface.h"

#define SIZE 500

//answer_queries(INPUT,USERS,DRIVERS,RIDES,STATS);
//timequary(arg, input1, input2, input3, linhas, respostaM, dbDrivers, dbUsers, dbRides, dbStats);
void timequary(int arg, int j, char *input1, char *input2, char *input3, int nlinhas, char Ans[][400], void *DRIVERS,void *USERS,void *RIDES,void *STATS){
    //printf ("arg %d\n\n", arg);
    clock_t start, end;
    double cpu_time_used;
    char ansfim[SIZE];
    start = clock();
    //char *resultadoo = "";
    //double resultado2;
    switch(arg){
        case(1):
            // printf ("1");
            query1(input1,DRIVERS,USERS,j);
            //printf ("1\n");
            // //printf("Query 1: %f\n",((float)(end1 - start1))/CLOCKS_PER_SEC);  
            break;
        case(2):
            //printf ("2");
            query2(input1,DRIVERS,j);
            //printf ("2\n");
            // //printf("Query 2: %f\n",((float)(end2 - start2))/CLOCKS_PER_SEC);
            break;
        case(3):
            //printf ("3");
            query3(input1,USERS,j);
            //printf ("3\n");
            // //printf("Query 3: %f\n",((float)(end3 - start3))/CLOCKS_PER_SEC);
            break;
        case(4):
            //printf ("4");
            query4(input1,STATS,j);
            //printf ("4\n");
            // //printf("Query 4: %f\n",((float)(end4 - start4))/CLOCKS_PER_SEC);
            break;
        case(5):
            //printf ("5");
            query5(input1,input2,STATS,j);
            //printf ("5\n");
            // //printf("Query 5: %f\n",((float)(end5 - start5))/CLOCKS_PER_SEC);
            break;
        case(6):
            //printf ("6");
            query6(input1,input2,input3,STATS,RIDES,j);
            //printf ("1928374937645873568723\n");
            // //printf("Query 6: %f\n",((float)(end6 - start6))/CLOCKS_PER_SEC);
            break;
        case(7):
            //printf ("7\n\n");
            query7(input1,input2,STATS,DRIVERS,j);
            //printf ("7\n\n");
            //printf("Query 7: %f\n",((float)(end7 - start7))/CLOCKS_PER_SEC);
            break;
        case(8):
            //printf ("8");
            query8(input1,input2,STATS,RIDES,DRIVERS,USERS,j);
            //printf ("8\n");
            //printf("Query 8: %f\n",((float)(end8 - start8))/CLOCKS_PER_SEC);
            break;
        case(9):
            //printf ("9");
            query9(input1,input2,STATS,RIDES,j);
            //printf ("9\n");
            //printf("Query 9: %f\n",((float)(end9 - start9))/CLOCKS_PER_SEC);
            break;
        default:
            break;
    }
    end = clock();
    cpu_time_used = (((double)(end - start)) / CLOCKS_PER_SEC);
    sprintf(ansfim, "Numero da query: %i_Comand %i_Timer: %0.3f sg |", arg, nlinhas, cpu_time_used * 1000);
    if (cpu_time_used <= 10){
        strcat(ansfim, " Executou em Tempo Útil : SIM :) |");
    }
    else
        strcat(ansfim, " Executou em Tempo Útil : Não :( |");
    strcpy(Ans[nlinhas], ansfim);
}

//Lê os ficheiros das queries
void reader(char *resultados, char *resultados_certos, char respostaM[][400], int j){
    FILE *result;
    FILE *result_certo;
    char line_result[100], line_result_certo[100], resposta[100];

    result = fopen(resultados, "r");
    result_certo = fopen(resultados_certos, "r");

    if (!result || !result_certo){
        strcpy(resposta, "File didn't open |\n");
        strcat(respostaM[j], resposta);
        return;
    }

    int equal = 1;
    int n1, n2;
    while ((n1 = fread(line_result, 1, sizeof(line_result), result)) == (n2 = fread(line_result_certo, 1, sizeof(line_result_certo), result_certo))){
        if (n1 == 0 || n2 == 0)
            break;
        if (memcmp(line_result, line_result_certo, n1)){
            equal = 0;
            break;
        }
    }

    if (n1 != n2)
        equal = 0;

    if (equal){
        strcpy(resposta, " Certo\n");
        strcat(respostaM[j], resposta);
    }
    else{
        strcpy(resposta, " Errado!\n");
        strcat(respostaM[j], resposta);
    }
}

//Função que verifica a query
void verifqry(char *resultados, char *outputs, int l, char respostaM[][400]){
    char nmresult[400];
    char nmverificacao[300];
    char com1[70];
    char com2[70];

    for (int i = 1; i <= l; i++){
        strcpy(nmresult, resultados);
        sprintf(com1, "/command%i_output.txt", i);
        strcat(nmresult, com1);
        strcpy(nmverificacao, outputs);
        sprintf(com2, "/command%i_output.txt", i);
        strcat(nmverificacao, com2);
        reader(nmresult, nmverificacao, respostaM, i);
    }
}

//Tempo que demora cada query
void testing(void **input, char *resultados, char *outputs, void *DRIVERS,void *USERS,void *RIDES, void *STATS, char respostaM[][400]){
    FILE *Fptr;
    int linhas = 1;
   
    char*** INPUT = (char***) input;
    for(short i = 0, j = 1; INPUT[i] != NULL;i++,j++){   
        int arg = atoi(INPUT[i][0]);
        //printf("i %d\n", i);
        char *input1 = INPUT[i][1], *input2 = INPUT[i][2], *input3 = INPUT[i][3];
        timequary(arg, j, input1, input2, input3, linhas, respostaM, DRIVERS, USERS, RIDES, STATS);
        linhas++;
    }

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    char resultados_dir[100];
    Fptr = fopen("resultados_testes.txt", "w"); 

    //printf("2\n");

    verifqry(resultados, outputs, linhas - 1, respostaM); //verificao(argv[3],argv[4], nlinhas, resposta)
    
    
    for (int i = 0; i < linhas; i++){
        fputs(respostaM[i], Fptr);
        //printf("i %d\n", i);
    }

    sprintf(resultados_dir, "Memoria: %ld mbytes\n", usage.ru_maxrss / 1024);
    fputs(resultados_dir, Fptr);

    fclose(Fptr);
}

//Numero de comandos
int argsize(char *i){
    FILE *ftpr;
    ftpr = fopen(i, "r");
    int n = 1;
    if (!ftpr){
        printf("Comand file not found.\n");
        exit(0);
    }
    else{
        char line[1024];
        while (fgets(line, 1024, ftpr))
        {
            char *linha;
            char *pointer;
            linha = strtok_r(line, "\n", &pointer);
            if (linha){
                n++;
                linha = strtok_r(NULL, "\n", &pointer);
            }
        }
    }
    return n;
}

//recebe o numero de argumentos, o ficheiro dos datasets, os inputs a dar, resultados obtidos do programa principal e resultados esperados
void main(int argc, char *argv[]){

    FILE *fPtr;
    char nameresultados[64];
    strcpy(nameresultados, "resultados_testes.txt");
    fPtr = fopen(nameresultados, "w");

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int tamanhoM = argsize(argv[2]);
    char respostaM[tamanhoM][400];

    if (argc >= 4)
    {       

        char aux[4096];
        strcpy(aux,argv[1]);
        strcat(aux,"/users.csv");
        FILE *users = fopen(aux, "r");
        if(users == NULL) {
            perror("Opening users.csv: try another path");
        }
        void *USERS = parser(users, ";\n\r", process_user,organize_user);
        fclose(users);

        strcpy(aux,argv[1]);
        strcat(aux,"/drivers.csv");
        FILE *drivers = fopen(aux, "r");
        if(drivers == NULL) {
            perror("Opening drivers.csv: try another path");
        }
        void *DRIVERS = parser(drivers, ";\n\r", process_driver,organize_driver);
        fclose(drivers);

        strcpy(aux,argv[1]);
        strcat(aux,"/rides.csv");
        FILE *rides = fopen(aux, "r");
        if(rides == NULL) {
            perror("Opening rides.csv: try another path");
        } 
        void *RIDES = parser(rides, ";\n\r", process_ride,organize_rides);
        fclose(rides);
    
        char *Input = (char *)malloc(30 * sizeof(char));
        FILE *input = fopen(argv[2], "r");
        if(input == NULL){
            perror("Opening input.txt: try another path");
        }
        void **INPUT = parse_query(input,process_query);
        fclose(input);
        void* STATS = organize_statistics(USERS,RIDES,DRIVERS);

        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        sprintf(respostaM[0], "Tempo de loading:%0.3f seg\n", cpu_time_used);
        fputs(respostaM[0], fPtr);
        
        if (argv != NULL){             
            testing(INPUT, argv[3], argv[4], DRIVERS, USERS, RIDES, STATS, respostaM); 
        }
        free_rides(RIDES);
        free_driver(DRIVERS);
        free_user(USERS);
        free_queries(INPUT);
        free(Input);
        clock_t time = clock();

        char resultados_dir[100];
        sprintf(resultados_dir,"Tempo total de Execução: %f\n",(float)time/CLOCKS_PER_SEC);  
        fputs(resultados_dir, fPtr);

        fclose(fPtr);
        
    }
}

