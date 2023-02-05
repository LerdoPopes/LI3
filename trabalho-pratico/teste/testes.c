#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

#define TM 500

//answer_queries(INPUT,USERS,DRIVERS,RIDES,STATS);
//tempo_query(arg, input1, input2, input3, linhas, respostaM, dbDrivers, dbUsers, dbRides, dbStats);
void tempo_query(int arg, int j, char *input1, char *input2, char *input3, int nlinhas, char Ans[][400], void *DRIVERS,void *USERS,void *RIDES,void *STATS){
    clock_t start, end;
    double cpu_time_used;
    char ansfim[TM];
    start = clock();
    //char *resultadoo = "";
    //double resultado2;
    switch(arg){
        case(1):
            query1(input1,DRIVERS,USERS,j);
            //printf("Query 1: %f\n",((float)(end1 - start1))/CLOCKS_PER_SEC);  
            break;
        case(2):
            query2(input1,DRIVERS,j);
            //printf("Query 2: %f\n",((float)(end2 - start2))/CLOCKS_PER_SEC);
            break;
        case(3):
            query3(input1,USERS,j);
            //printf("Query 3: %f\n",((float)(end3 - start3))/CLOCKS_PER_SEC);
            break;
        case(4):
            query4(input1,STATS,j);
            //printf("Query 4: %f\n",((float)(end4 - start4))/CLOCKS_PER_SEC);
            break;
        case(5):
            query5(input1,input2,STATS,j);
            //printf("Query 5: %f\n",((float)(end5 - start5))/CLOCKS_PER_SEC);
            break;
        case(6):
            query6(input1,input2,input3,STATS,RIDES,j);
            //printf("Query 6: %f\n",((float)(end6 - start6))/CLOCKS_PER_SEC);
            break;
        case(7):
            query7(input1,input2,STATS,DRIVERS,j);
            //printf("Query 7: %f\n",((float)(end7 - start7))/CLOCKS_PER_SEC);
            break;
        case(8):
            query8(input1,input2,STATS,RIDES,DRIVERS,USERS,j);
            //printf("Query 8: %f\n",((float)(end8 - start8))/CLOCKS_PER_SEC);
            break;
        case(9):
            query9(input1,input2,STATS,RIDES,j);
            //printf("Query 9: %f\n",((float)(end9 - start9))/CLOCKS_PER_SEC);
            break;
        default:
            break;
    }
    end = clock();
    cpu_time_used = (((double)(end - start)) / CLOCKS_PER_SEC);
    sprintf(ansfim, "Numero da query: %i_Comand %i_Timer: %0.3f sg |", arg, nlinhas, cpu_time_used * 1000);
    if (cpu_time_used <= 10)
    {
        strcat(ansfim, " Executou em Tempo Útil : SIM :) |");
    }
    else
        strcat(ansfim, " Executou em Tempo Útil : Não :( |");
    strcpy(Ans[nlinhas], ansfim);
}

/Função que lê os ficheiros das queries
void verificar(char *resultados, char *resultados_certos, char respostaM[][400], int j)
{
    FILE *result;
    FILE *result_certo;
    char line_result[100], line_result_certo[100], resposta[100];

    result = fopen(resultados, "r");
    result_certo = fopen(resultados_certos, "r");

    if (!result || !result_certo)
    {
        strcpy(resposta, "Não foi possível abrir um dos ficheiros! |\n");
        strcat(respostaM[j], resposta);
        return;
    }

    int equal = 1;
    int n1, n2;
    while ((n1 = fread(line_result, 1, sizeof(line_result), result)) == (n2 = fread(line_result_certo, 1, sizeof(line_result_certo), result_certo)))
    {
        if (n1 == 0 || n2 == 0)
            break;
        if (memcmp(line_result, line_result_certo, n1))
        {
            equal = 0;
            break;
        }
    }

    if (n1 != n2)
        equal = 0;

    if (equal)
    {
        strcpy(resposta, " Certo\n");
        strcat(respostaM[j], resposta);
    }
    else
    {
        strcpy(resposta, " Errado!\n");
        strcat(respostaM[j], resposta);
    }
}

//Função que verifica a query
void verificao_query(char *resultados, char *outputs, int l, char respostaM[][400])
{
    char nome_file_result[400];
    char nome_file_verificacao[300];
    char comando1[70];
    char comando2[70];

    for (int i = 1; i <= l; i++)
    {
        strcpy(nome_file_result, resultados);
        sprintf(comando1, "/command%i_output.txt", i);
        strcat(nome_file_result, comando1);
        strcpy(nome_file_verificacao, outputs);
        sprintf(comando2, "/command%i_output.txt", i);
        strcat(nome_file_verificacao, comando2);
        verificar(nome_file_result, nome_file_verificacao, respostaM, i);
    }
}

//Função que permite obter o tempo que demora cada query
void query_teste(void **input, char *resultados, char *outputs, void *DRIVERS,void *USERS,void *RIDES, void *STATS, char respostaM[][400])
{
    FILE *Fptr;
    int linhas = 1;
   
    char*** INPUT = (char***) input;
    for(short i = 0, j = 1; INPUT[i] != NULL;i++,j++){   
        int agr = atoi(INPUT[i][0]);
        char *input1 = INPUT[i][1], *input2 = INPUT[i][2], *input3 = INPUT[i][3];
        tempo_query(arg, j, input1, input2, input3, linhas, respostaM, DRIVERS, USERS, RIDES, STATS);
        linhas++;
    }

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    char resultados_dir[100];
    Fptr = fopen("resultados_testes.txt", "w"); //faz sentido

    verificao_query(resultados, outputs, linhas - 1, respostaM); //verificao(argv[3],argv[4], contalinhas, resposta_matriz)
    for (int i = 0; i < linhas; i++)
    {
        fputs(respostaM[i], Fptr);
    }

    sprintf(resultados_dir, "Uso de memoria: %ld Mbytes\n", usage.ru_maxrss / 1024);
    fputs(resultados_dir, Fptr);

    fclose(Fptr);
}

//Função que calcula o número de comandos do ficheiro dos comandos
int tamArg(char *i)
{
    FILE *ftpr;
    ftpr = fopen(i, "r");
    int n = 1;
    if (!ftpr)
    {
        printf("Não existe o ficheiro dos comandos.\n");
        exit(0);
    }
    else
    {
        char line[1024];
        while (fgets(line, 1024, ftpr))
        {
            char *linha;
            char *savepointer;
            linha = strtok_r(line, "\n", &savepointer);
            if (linha)
            {
                n++;
                linha = strtok_r(NULL, "\n", &savepointer);
            }
        }
    }
    return n;
}

//recebe o numero de argumentos, o ficheiro dos datasets, os inputs a dar, resultados obtidos do programa principal e resultados esperados
void main(int argc, char *argv[])
{

    FILE *fPtr;
    char nameresultados[64];
    strcpy(nameresultados, "resultados_testes.txt");
    fPtr = fopen(nameresultados, "w");

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int tamanhoM = tamArg(argv[2]);
    char respostaM[tamanhoM][400];

    if (argc >= 4)
    {
        if (argv != NULL)
        {             
            query_teste(argv[2], argv[3], argv[4], tu, td, tr, respostaM);
        }
        fclose(fPtr);
        freeHashtableUser(tu);
        freeHashtableDriver(td);
        freeHashtableRides(tr);

        char aux[4096];
        strcpy(aux,argv[1]);
        strcat(aux,"/users.csv");
        FILE *users = fopen(aux, "r");
        if(users == NULL) {
            perror("Opening users.csv: try another path");
        }
        void *USERS = parser(users, ";\n\r", process_user,organize_user,0);
        fclose(users);

        strcpy(aux,argv[1]);
        strcat(aux,"/drivers.csv");
        FILE *drivers = fopen(aux, "r");
        if(drivers == NULL) {
            perror("Opening drivers.csv: try another path");
        }
        void *DRIVERS = parser(drivers, ";\n\r", process_driver,organize_driver,0);
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
        //char resposta[100];

        sprintf(respostaM[0], "Tempo de loading:%0.3f seg\n", cpu_time_used);
        fputs(respostaM[0], fPtr);

        if (argv != NULL)
        {             
            query_teste(INPUT, argv[3], argv[4], USERS, DRIVERS, RIDES, STATS, respostaM); //argv[2]- ficheiro inputs; argv[3]-ficheiro dos resultados criados; argv[4]-resultados esperados; USERS; DRIVERS,RIDES;STATs;respostaM
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

/*
int main(int argc, char **argv){
    // if(argc < 2){
        // initscr();
        // cbreak();
        // noecho();
        // curs_set(0);
        // int height,width,start_y,start_x;
        // int yMax, xMax;
        // char input[100];
        // getmaxyx(stdscr,yMax,xMax);
        // height = 30;
        // width = 200;
        // start_y = start_x = 10;
// 
        // WINDOW * win = newwin(10,xMax - 12,yMax/2,5);
        // refresh();
// 
        // box(win,0,0);
        // mvwprintw(win,1,1,"Insira a path dos ficheiros CSV:");
        // wrefresh(win);
        // mvwgetstr(win,1,35,input);
// 
        // char aux[4096];
        // strcpy(aux,input);
        // strcat(aux,"/users.csv");
        // FILE *users = fopen(aux, "r");
        // void *USERS = parser(users, ";\n\r", process_user,organize_user,0);
        // fclose(users);
// 
        // strcpy(aux,input);
        // strcat(aux,"/drivers.csv");
        // FILE *drivers = fopen(aux, "r");
        // void *DRIVERS = parser(drivers, ";\n\r", process_driver,organize_driver,0);
        // fclose(drivers);
// 
        // strcpy(aux,input);
        // strcat(aux,"/rides.csv");
        // FILE *rides = fopen(aux, "r");
        // void *RIDES = parser(rides, ";\n\r", process_ride,organize_rides);
        // fclose(rides);
// 
        // void* STATS = organize_statistics(USERS,RIDES,DRIVERS);
                // 
        // if(strcmp(input,".")==0){
            // werase(win);
            // wrefresh(win);
            // WINDOW * menu = newwin(15,xMax,0,0);
            // mvwprintw(menu,7,(xMax/2) - 5,"Query Selector");
            // wrefresh(menu);
            // queries_menu(DRIVERS,USERS,RIDES,STATS);
        // }
        // printw("Insira a path dos ficheiros CSV:");
        // int c = wgetch(win);
// 
        // endwin();
        // return 0;
    // }
    // else{
        
    char aux[4096];
    strcpy(aux,argv[1]);
    strcat(aux,"/users.csv");
    FILE *users = fopen(aux, "r");
        if(users == NULL) {
            perror("Opening users.csv: try another path");
        }
        void *USERS = parser(users, ";\n\r", process_user,organize_user,0);
        fclose(users);
    strcpy(aux,argv[1]);
    strcat(aux,"/drivers.csv");
    FILE *drivers = fopen(aux, "r");
        if(drivers == NULL) {
            perror("Opening drivers.csv: try another path");
        }
        void *DRIVERS = parser(drivers, ";\n\r", process_driver,organize_driver,0);
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
    answer_queries(INPUT,USERS,DRIVERS,RIDES,STATS);
    free_rides(RIDES);
    free_driver(DRIVERS);
    free_user(USERS);
    free_queries(INPUT);
    free(Input);
    clock_t time = clock();
    printf("Tempo total de Execução: %f\n",(float)time/CLOCKS_PER_SEC);  
}
}
*/
