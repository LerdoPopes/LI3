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

void tempo_query(int arg, char *line, int nlinhas, char Ans[][400], void *dbDrivers,void *dbUsers,void *dbRides){
    clock_t start, end;
    double cpu_time_used;
    char ansfim[TM];
    start = clock();
    char *input1, *input2, *input3;
    char *resultadoo = "";
    double resultado2;
        switch (arg){
            case 1:
                input1 = strdup(strsep(&line, " "));
                resultadoo = query1(hu, hd, hr, input1);
                free(input1);
                break;
            case 2:
                input1 = strdup(strsep(&line, " "));
                int i1 = atoi(input1);
                if (i1 > 0)
                {
                    resultadoo = bestDrivers(hd, hr, i1);
                }
                free(input1);
                break;
            case 3:
                input1 = strdup(strsep(&line, " "));
                int j = atoi(input1);
                if (j > 0 && j <= 70)
                {
                    resultadoo = longUsers(hu, hr, input1);
                }
                free(input1);
                break;
            case 4:
                input1 = strdup(strsep(&line, " "));
                resultado2 = precoMedioCidade(hd, hr, input1);
                free(input1);
                break;
            case 5:
                input1 = strdup(strsep(&line, " "));
                input2 = strdup(strsep(&line, " "));
                resultado2 = precoMedioDatas(hd, hr, input1, input2);
                free(input2);
                free(input1);
                break;

            case 6:
                input1 = strdup(strsep(&line, " "));
                input2 = strdup(strsep(&line, " "));
                input3 = strdup(strsep(&line, " "));
                resultado2 = distanciaMedioDatas(hr, input1, input2, input3);
                free(input3);
                free(input2);
                free(input1);
                break;
            case 7:
                input1 = strdup(strsep(&line, " "));
                input2 = strdup(strsep(&line, " "));
                resultadoo = bestDriverCity(hd, hr, input1, input2);
                free(input2);
                free(input1);
                break;
            case 8:
                input1 = strdup(strsep(&line, " "));
                input2 = strdup(strsep(&line, " "));
                resultadoo = generoIdade(hu, hd, hr, input1, input2);
                free(input2);
                free(input1);
                break;
            case 9:
                input1 = strdup(strsep(&line, " "));
                input2 = strdup(strsep(&line, " "));
                resultadoo = gorjetaIntervaloTempo(hr, input1, input2);
                free(input2);
                free(input1);
                break;
            default:
                break;
    }
    end = clock();
    cpu_time_used = (((double)(end - start)) / CLOCKS_PER_SEC);
    sprintf(ansfim, "Numero da query: %i_Comand %i_Timer: %0.3f sg |", arg, nlinhas, cpu_time_used * 1000);
    if (cpu_time_used <= 10)
    {
        strcat(ansfim, " Tempo Util : SIM! |");
    }
    else
        strcat(ansfim, " Tempo Util : Não... |");
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
void query_teste(char *input, char *resultados, char *outputs, HashUser hu, HashDriver hd, HashRides hr, char respostaM[][400])
{
    FILE *Fptr;
    char *line = malloc(sizeof(char) * 100);
    FILE *fp = fopen(input, "r");
    int arg;
    int contalinhas = 1;
    if (fp != NULL)
    {
        for (int i = 0; fgets(line, 100, fp); i++)
        {
            line = strdup(strsep(&line, "\r\n"));
            char *command;
            command = strdup(strsep(&line, " "));
            arg = atoi(command);
            tempo_query(arg, line, contalinhas, hu, hd, hr, respostaM);
            contalinhas++;
            line = malloc(sizeof(char) * 100);
        }
    }
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    char resultados_dir[100];
    Fptr = fopen("resultados_testes.txt", "w"); //faz sentido

    verificao_query(resultados, outputs, contalinhas - 1, respostaM); //verificao(argv[3],argv[4], contalinhas, resposta_matriz)
    for (int i = 0; i < contalinhas; i++)
    {
        fputs(respostaM[i], Fptr);
    }

    sprintf(resultados_dir, "Uso de memoria: %ld Mbytes\n", usage.ru_maxrss / 1024);
    fputs(resultados_dir, Fptr);

    fclose(fp);
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

    if (argc >= 2)
    {
        HashUser tu;
        HashDriver td;
        HashRides tr;
        loadHash(tu, td, tr, argv[1]);
        //em vez disto dar load as nossas !!!!!!!!!!!!!!!


        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        //char resposta[100];

        sprintf(respostaM[0], "Tempo de loading:%0.3f seg\n", cpu_time_used);
        fputs(respostaM[0], fPtr);

        if (argv != NULL)
        {
            query_teste(argv[2], argv[3], argv[4], tu, td, tr, respostaM);
        }
        fclose(fPtr);
        freeHashtableUser(tu);
        freeHashtableDriver(td);
        freeHashtableRides(tr);
    }
}