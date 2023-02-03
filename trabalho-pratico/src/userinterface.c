#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "../Include/drivers.h"
#include "../Include/users.h"
#include "../Include/rides.h"
#include "../Include/parser.h"
#include "../Include/queries.h"
#include "../Include/statistics.h"
#include "../Include/userinterface.h"

void query_menu(int opçao,void *DRIVERS,void *USERS,void *RIDES,void *STATS){
    int height,width,start_y,start_x;
    int yMax, xMax;
    char ID[30];
    char N[10];
    char Cidade[15];
    char data1[11];
    char data2[11];
    char *Gender;
    char Idade[3];
    getmaxyx(stdscr,yMax,xMax);
    switch(opçao){
        case(1):
            clear();
            mvprintw(yMax/2 - 8, xMax/2-strlen("Esta query lista o resumo de um perfil registado no serviço através do seu identificador.")/2,"Esta query lista o resumo de um perfil registado no serviço através do seu identificador.");
            mvprintw(yMax/2 - 4, xMax/2-strlen("Este identificador pode corresponder a um utilizador (username) ou a um condutor (id).")/2,"Este identificador pode corresponder a um utilizador (username) ou a um condutor (id).");
            mvprintw(yMax/2,xMax/2-strlen("Insira o identificador do perfil (ID de um condutor ou Username de um utilizador:")/2,"Insira o identificador do perfil (ID de um condutor ou Username de um utilizador:");
            mvgetstr(yMax/2 + 4,xMax/2-strlen(ID)/2,ID);
            clear();
            query1_UI(ID,DRIVERS,USERS,STATS,RIDES);
            break;            
        case(2):
            clear();
            mvprintw(yMax/2 - 12,xMax/2-strlen("Esta query lista os N condutores com a maior avaliação média.")/2,"Esta query lista os N condutores com a maior avaliação média");
            mvprintw(yMax/2 - 8,xMax/2-strlen("Em caso de empate, o resultado é ordenado de forma que os condutores com a viagem mais recente surjam primeiro.")/2,"Em caso de empate, o resultado é ordenado de forma que os condutores com a viagem mais recente surjam primeiro.");
            mvprintw(yMax/2 - 4,xMax/2-strlen("Caso surja outro empate, o desempate é feito com o id do condutor (ordem crescente)")/2,"Caso surja outro empate, o desempate é feito com o id do condutor (ordem crescente)");
            mvprintw(yMax/2,xMax/2-strlen("Insira o número de condutores:")/2,"Insira o número de condutores:");
            mvgetstr(yMax/2+4,xMax/2-strlen(N)/2,N);
            clear();
            query2_UI(N,DRIVERS,USERS,RIDES,STATS);
            break;
        case(3):
            clear();
            mvprintw(yMax/2 - 12,xMax/2-strlen("Esta query lista os N utilizadores com a maior distância viajada.")/2,"Esta query lista os N utilizadores com a maior distância viajada.");
            mvprintw(yMax/2 - 8,xMax/2-strlen("Em caso de empate, o resultado é ordenado de forma que os utilizadores com a viagem mais recente surjam primeiro.")/2,"Em caso de empate, o resultado é ordenado de forma que os utilizadores com a viagem mais recente surjam primeiro.");
            mvprintw(yMax/2 - 4,xMax/2-strlen("Caso surja outro empate, o desempate é feito com o username do utilizador (ordem crescente)")/2,"Caso surja outro empate, o desempate é feito com o username do utilizador (ordem crescente)");
            mvprintw(yMax/2,xMax/2-strlen("Insira o número de utilizadores:")/2,"Insira o número de utilizadores:");
            mvgetstr(yMax/2+4,xMax/2-strlen(N),N);            
            clear();
            query3_UI(N,USERS,RIDES,DRIVERS,STATS);
            break;
        case(4):
            clear();
            mvprintw(yMax/2 - 4, xMax/2-strlen("Esta query calcula o preço médio de viagens numa determinada cidade.")/2,"Esta query calcula o preço médio de viagens numa determinada cidade.");
            mvprintw(yMax/2,xMax/2-strlen("Insira a cidade:")/2,"Insira a cidade:");
            mvgetstr(yMax/2 + 4,xMax/2-strlen(Cidade)/2,Cidade);
            clear();
            query4_UI(Cidade,STATS,USERS,RIDES,DRIVERS);
            break;
        case(5):
            clear();
            mvprintw(yMax/2 - 4,xMax/2 - strlen("Esta query calcula o preço médio das viagens (sem considerar gorjetas) entre 2 dias.")/2,"Esta query calcula o preço médio das viagens (sem considerar gorjetas) entre 2 dias");
            mvprintw(yMax/2,xMax/2-strlen("Insira a primeira data para o cálculo do preço médio das viagens (sem gorjetas) entre 2 dias:")/2,"Insira a primeira data para o cálculo do preço médio das viagens (sem gorjetas) entre 2 dias:");
            mvgetstr(yMax/2 + 4,(xMax/2) - strlen(data1)/2,data1);
            clear();
            mvprintw(yMax/2 - 4,xMax/2 - strlen("Esta query calcula o preço médio das viagens (sem considerar gorjetas) entre 2 dias.")/2,"Esta query calcula o preço médio das viagens (sem considerar gorjetas) entre 2 dias");
            mvprintw(yMax/2,xMax/2-strlen("Insira agora a segunda data:")/2,"Insira agora a segunda data:");
            mvgetstr(yMax/2 + 4,(xMax/2) - strlen(data2)/2,data2);
            clear();
            query5_UI(data1,data2,STATS,USERS,RIDES,DRIVERS);
            break;
        case(6):
            clear();
            mvprintw(yMax/2 - 4,xMax/2 - strlen("Esta query calcula a distância média percorrida, numa determinada cidade, entre 2 dias.")/2,"Esta query calcula a distância média percorrida, numa determinada cidade, entre 2 dias.");
            mvprintw(yMax/2,xMax/2-strlen("Insira a cidade")/2,"Insira a cidade:");
            mvgetstr(yMax/2 + 4,(xMax/2)-strlen(Cidade)/2,Cidade);
            clear();
            mvprintw(yMax/2,xMax/2-strlen("Insira a primeira data:")/2,"Insira a primeira data:");
            mvgetstr(yMax/2+4,3*(xMax/2) - strlen(data1)/2,data1);
            clear();
            mvprintw(yMax/2,xMax/2-strlen("Insira agora a segunda data:")/2,"Insira agora a segunda data:");
            mvgetstr(yMax/2+4,(xMax/2) - strlen(data2),data2);
            clear();
            query6_UI(Cidade,data1,data2,STATS,RIDES,USERS,DRIVERS);
            break;
        case(7):
            clear();
            mvprintw(yMax/2 - 8,xMax/2-strlen("Esta query lista os Top N condutores com a maior avaliação média, numa determinada cidade.")/2,"Esta query lista os Top N condutores com a maior avaliação média, numa determinada cidade.");
            mvprintw(yMax/2 - 4,xMax/2-strlen("Em caso de empate, o resultado é ordenado através do id do condutor, de forma decrescente.")/2,"Em caso de empate, o resultado é ordenado através do id do condutor, de forma decrescente.");
            mvprintw(yMax/2,xMax/2-strlen("Insira o número de condutores:")/2,"Insira o número de condutores:");
            mvgetstr(yMax/2+4,(xMax/2)-strlen(N)/2,N);
            clear();
            mvprintw(yMax/2,xMax/2-strlen("Insira agora a cidade:"),"Insira agora a cidade:");
            mvgetstr(yMax/2+4,(xMax/2)-strlen(Cidade)/2,Cidade);
            clear();
            // query7_UI(N,Cidade,STATS,DRIVERS,USERS,RIDES);
            // answer_queries_interativo(bla);
            break;
        case(8):
            clear();
            mvprintw(yMax/2 - 12,xMax/2-strlen("Esta query lista todas as viagens nas quais o utilizador e o condutor são do género selecionado e têm perfis com uma certa quantia ou mais de anos.")/2,"Esta query lista todas as viagens nas quais o utilizador e o condutor são do género selecionado e têm perfis com uma certa quantia ou mais de anos.");
            mvprintw(yMax/2 - 8,xMax/2 - strlen("O resultado será ordenado de forma que as contas mais antigas de condutores apareçam primeiro e, se necessário, que as contas de utilizadores apareçam primeiro.")/2,"O resultado será ordenado de forma que as contas mais antigas de condutores apareçam primeiro e, se necessário, que as contas de utilizadores apareçam primeiro.");
            mvprintw(yMax/2 - 4,xMax/2-strlen("Em caso de empate, o resultado é ordenado pelo id da viagem (em ordem crescente).")/2,"Em caso de empate, o resultado é ordenado pelo id da viagem (em ordem crescente).");
            mvprintw(yMax/2,xMax/2 - strlen("Insira o género do condutor e utilizador das viagens:")/2,"Insira o género do condutor e utilizador das viagens:");
            mvgetstr(yMax/2 + 4,(xMax/2)-strlen(Gender)/2,Gender);
            clear();
            mvprintw(yMax/2,xMax/2 - strlen("Insira agora a idade mínima dos perfis em anos:")/2,"Insira agora a idade mínima dos perfis em anos:");
            mvgetstr(yMax/2 + 4,(xMax/2) - strlen(Idade)/2,Idade);  
            clear();
            query8_UI(Gender,Idade,STATS,RIDES,DRIVERS,USERS);          
            // answer_queries_interativo(bla);
            break;
        case(9):
            clear();
            mvprintw(yMax/2 - 12,xMax/2-strlen("Esta query lista todas as viagens nas quais o passageiro deu gorjeta, entre 2 dias, ordenadas por ordem de distância percorrida (em ordem decrescente).")/2,"Esta query lista todas as viagens nas quais o passageiro deu gorjeta, entre 2 dias, ordenadas por ordem de distância percorrida (em ordem decrescente).");            
            mvprintw(yMax/2 - 8,xMax/2-strlen("Em caso de empate, as viagens mais recentes aparecerão primeiro.")/2,"Em caso de empate, as viagens mais recentes aparecerão primeiro.");
            mvprintw(yMax/2 - 4,xMax/2-strlen("Caso persistam empates, o resultado é ordenado pelo id da viagem (ordem decrescente)")/2,"Caso persistam empates, o resultado é ordenado pelo id da viagem (ordem decrescente)");
            mvprintw(yMax/2,xMax/2 - strlen("Insira a primeira data:")/2,"Insira a primeira data:");
            mvgetstr(yMax/2 + 4,(xMax/2) - strlen(data1)/2,data1);
            clear();
            mvprintw(yMax/2,xMax/2,"Insira agora a segunda data:");
            mvgetstr(yMax/2 + 4,(xMax/2)-strlen(data2)/2,data2);
            clear();
            query9_UI(data1,data2,STATS,RIDES,USERS,DRIVERS);
            // answer_queries_interativo(bla);
            break;
    }


}

void queries_menu(void *DRIVERS,void *USERS, void *RIDES, void *STATS){
    int yMax, xMax;
    getmaxyx(stdscr,yMax,xMax);
    mvprintw(50, xMax/2 - strlen("Pressione 'Enter' para selecionar, 'Ctrl + C' para sair")/2 ,"Pressione 'Enter' para selecionar, 'Ctrl + C' para sair");    
    mvprintw(7,(xMax/2) - 8,"Query Selector");
    WINDOW * opcoes = newwin(30,40,15,xMax/2 - 20);
    refresh();
    box(opcoes,0,0);
    wrefresh(opcoes);
    keypad(opcoes,true);
    char *Opcoes[9] = {"Query 1","Query 2","Query 3","Query 4","Query 5","Query 6","Query 7","Query 8","Query 9"};
    int choice;
    int highlight = 0;
    short j = 1;
        while(j)
        {
            for(int i = 0; i < 9; i++){
                if(i == highlight) wattron(opcoes,A_REVERSE);
                mvwprintw(opcoes,2 + 3*i, 15,Opcoes[i]);
                wattroff(opcoes,A_REVERSE);
            }
            choice = wgetch(opcoes);
            switch(choice)
            {
                case(KEY_UP):
                if(highlight > 0)
                    highlight--;
                break;
                case(KEY_DOWN):
                if(highlight < 8)
                    highlight++;
                break;
                case(10):
                    clear();
                    query_menu(highlight + 1,DRIVERS,USERS,RIDES,STATS);
                    // mvprintw(0, 0, "Executando a Query %d",highlight+1);
                    // getch();
                    j = 0;
                default:
                break;
            }
        }
    }
// }
// #include <math.h>
// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <ncurses.h>
// #include "../Include/drivers.h"
// #include "../Include/users.h"
// #include "../Include/rides.h"
// #include "../Include/parser.h"
// #include "../Include/queries.h"
// #include "../Include/statistics.h"
// #include "../Include/userinterface.h"

// void query_menu(int opçao,void *DRIVERS,void *USERS,void *RIDES,void *STATS){
//     int height,width,start_y,start_x;
//     int yMax, xMax;
//     char ID[30];
//     char N[10];
//     char Cidade[15];
//     char data1[11];
//     char data2[11];
//     char *Gender;
//     char Idade[3];
//     getmaxyx(stdscr,yMax,xMax);
//     switch(opçao){
//         case(1):
//             clear();
//             mvprintw(yMax/2 - 8, xMax/2-strlen("Esta query lista o resumo de um perfil registado no serviço através do seu identificador.")/2,"Esta query lista o resumo de um perfil registado no serviço através do seu identificador.");
//             mvprintw(yMax/2 - 4, xMax/2-strlen("Este identificador pode corresponder a um utilizador (username) ou a um condutor (id).")/2,"Este identificador pode corresponder a um utilizador (username) ou a um condutor (id).");
//             mvprintw(yMax/2,xMax/2-strlen("Insira o identificador do perfil (ID de um condutor ou Username de um utilizador:")/2,"Insira o identificador do perfil (ID de um condutor ou Username de um utilizador:");
//             mvgetstr(yMax/2 + 4,xMax/2-strlen(ID)/2,ID);
//             clear();
//             query1_UI(ID,DRIVERS,USERS,STATS,RIDES);
//             break;            
//         case(2):
//             clear();
//             mvprintw(yMax/2 - 12,xMax/2-strlen("Esta query lista os N condutores com a maior avaliação média.")/2,"Esta query lista os N condutores com a maior avaliação média");
//             mvprintw(yMax/2 - 8,xMax/2-strlen("Em caso de empate, o resultado é ordenado de forma que os condutores com a viagem mais recente surjam primeiro.")/2,"Em caso de empate, o resultado é ordenado de forma que os condutores com a viagem mais recente surjam primeiro.");
//             mvprintw(yMax/2 - 4,xMax/2-strlen("Caso surja outro empate, o desempate é feito com o id do condutor (ordem crescente)")/2,"Caso surja outro empate, o desempate é feito com o id do condutor (ordem crescente)");
//             mvprintw(yMax/2,xMax/2-strlen("Insira o número de condutores:")/2,"Insira o número de condutores:");
//             mvgetstr(yMax/2+4,xMax/2-strlen(N)/2,N);
//             clear();
//             query2_UI(N,DRIVERS,USERS,RIDES,STATS);
//             break;
//         case(3):
//             clear();
//             mvprintw(yMax/2 - 12,xMax/2-strlen("Esta query lista os N utilizadores com a maior distância viajada.")/2,"Esta query lista os N utilizadores com a maior distância viajada.");
//             mvprintw(yMax/2 - 8,xMax/2-strlen("Em caso de empate, o resultado é ordenado de forma que os utilizadores com a viagem mais recente surjam primeiro.")/2,"Em caso de empate, o resultado é ordenado de forma que os utilizadores com a viagem mais recente surjam primeiro.");
//             mvprintw(yMax/2 - 4,xMax/2-strlen("Caso surja outro empate, o desempate é feito com o username do utilizador (ordem crescente)")/2,"Caso surja outro empate, o desempate é feito com o username do utilizador (ordem crescente)");
//             mvprintw(yMax/2,xMax/2-strlen("Insira o número de utilizadores:")/2,"Insira o número de utilizadores:");
//             mvgetstr(yMax/2+4,xMax/2-strlen(N),N);            
//             clear();
//             query3_UI(N,USERS,RIDES,DRIVERS,STATS);
//             break;
//         case(4):
//             clear();
//             mvprintw(yMax/2 - 4, xMax/2-strlen("Esta query calcula o preço médio de viagens numa determinada cidade.")/2,"Esta query calcula o preço médio de viagens numa determinada cidade.");
//             mvprintw(yMax/2,xMax/2-strlen("Insira a cidade:")/2,"Insira a cidade:");
//             mvgetstr(yMax/2 + 4,xMax/2-strlen(Cidade)/2,Cidade);
//             clear();
//             query4_UI(Cidade,STATS,USERS,RIDES,DRIVERS);
//             break;
//         case(5):
//             clear();
//             mvprintw(yMax/2 - 4,xMax/2 - strlen("Esta query calcula o preço médio das viagens (sem considerar gorjetas) entre 2 dias.")/2,"Esta query calcula o preço médio das viagens (sem considerar gorjetas) entre 2 dias");
//             mvprintw(yMax/2,xMax/2-strlen("Insira a primeira data para o cálculo do preço médio das viagens (sem gorjetas) entre 2 dias:")/2,"Insira a primeira data para o cálculo do preço médio das viagens (sem gorjetas) entre 2 dias:");
//             mvgetstr(yMax/2 + 4,(xMax/2) - strlen(data1)/2,data1);
//             clear();
//             mvprintw(yMax/2 - 4,xMax/2 - strlen("Esta query calcula o preço médio das viagens (sem considerar gorjetas) entre 2 dias.")/2,"Esta query calcula o preço médio das viagens (sem considerar gorjetas) entre 2 dias");
//             mvprintw(yMax/2,xMax/2-strlen("Insira agora a segunda data:")/2,"Insira agora a segunda data:");
//             mvgetstr(yMax/2 + 4,(xMax/2) - strlen(data2)/2,data2);
//             clear();
//             query5_UI(data1,data2,STATS,USERS,RIDES,DRIVERS);
//             break;
//         case(6):
//             clear();
//             mvprintw(yMax/2 - 4,xMax/2 - strlen("Esta query calcula a distância média percorrida, numa determinada cidade, entre 2 dias.")/2,"Esta query calcula a distância média percorrida, numa determinada cidade, entre 2 dias.");
//             mvprintw(yMax/2,xMax/2-strlen("Insira a cidade")/2,"Insira a cidade:");
//             mvgetstr(yMax/2 + 4,(xMax/2)-strlen(Cidade)/2,Cidade);
//             clear();
//             mvprintw(yMax/2,xMax/2-strlen("Insira a primeira data:")/2,"Insira a primeira data:");
//             mvgetstr(yMax/2+4,3*(xMax/2) - strlen(data1)/2,data1);
//             clear();
//             mvprintw(yMax/2,xMax/2-strlen("Insira agora a segunda data:")/2,"Insira agora a segunda data:");
//             mvgetstr(yMax/2+4,(xMax/2) - strlen(data2),data2);
//             clear();
//             query6_UI(Cidade,data1,data2,STATS,RIDES,USERS,DRIVERS);
//             break;
//         case(7):
//             clear();
//             mvprintw(yMax/2 - 8,xMax/2-strlen("Esta query lista os Top N condutores com a maior avaliação média, numa determinada cidade.")/2,"Esta query lista os Top N condutores com a maior avaliação média, numa determinada cidade.");
//             mvprintw(yMax/2 - 4,xMax/2-strlen("Em caso de empate, o resultado é ordenado através do id do condutor, de forma decrescente.")/2,"Em caso de empate, o resultado é ordenado através do id do condutor, de forma decrescente.");
//             mvprintw(yMax/2,xMax/2-strlen("Insira o número de condutores:")/2,"Insira o número de condutores:");
//             mvgetstr(yMax/2+4,(xMax/2)-strlen(N)/2,N);
//             clear();
//             mvprintw(yMax/2,xMax/2-strlen("Insira agora a cidade:"),"Insira agora a cidade:");
//             mvgetstr(yMax/2+4,(xMax/2)-strlen(Cidade)/2,Cidade);
//             clear();
//             // query7_UI(N,Cidade,STATS,DRIVERS,USERS,RIDES);
//             // answer_queries_interativo(bla);
//             break;
//         case(8):
//             clear();
//             mvprintw(yMax/2 - 12,xMax/2-strlen("Esta query lista todas as viagens nas quais o utilizador e o condutor são do género selecionado e têm perfis com uma certa quantia ou mais de anos.")/2,"Esta query lista todas as viagens nas quais o utilizador e o condutor são do género selecionado e têm perfis com uma certa quantia ou mais de anos.");
//             mvprintw(yMax/2 - 8,xMax/2 - strlen("O resultado será ordenado de forma que as contas mais antigas de condutores apareçam primeiro e, se necessário, que as contas de utilizadores apareçam primeiro.")/2,"O resultado será ordenado de forma que as contas mais antigas de condutores apareçam primeiro e, se necessário, que as contas de utilizadores apareçam primeiro.");
//             mvprintw(yMax/2 - 4,xMax/2-strlen("Em caso de empate, o resultado é ordenado pelo id da viagem (em ordem crescente).")/2,"Em caso de empate, o resultado é ordenado pelo id da viagem (em ordem crescente).");
//             mvprintw(yMax/2,xMax/2 - strlen("Insira o género do condutor e utilizador das viagens:")/2,"Insira o género do condutor e utilizador das viagens:");
//             mvgetstr(yMax/2 + 4,(xMax/2)-strlen(Gender)/2,Gender);
//             clear();
//             mvprintw(yMax/2,xMax/2 - strlen("Insira agora a idade mínima dos perfis em anos:")/2,"Insira agora a idade mínima dos perfis em anos:");
//             mvgetstr(yMax/2 + 4,(xMax/2) - strlen(Idade)/2,Idade);  
//             clear();
//             query8_UI(Gender,Idade,STATS,RIDES,DRIVERS,USERS);          
//             // answer_queries_interativo(bla);
//             break;
//         case(9):
//             clear();
//             mvprintw(yMax/2 - 12,xMax/2-strlen("Esta query lista todas as viagens nas quais o passageiro deu gorjeta, entre 2 dias, ordenadas por ordem de distância percorrida (em ordem decrescente).")/2,"Esta query lista todas as viagens nas quais o passageiro deu gorjeta, entre 2 dias, ordenadas por ordem de distância percorrida (em ordem decrescente).");            
//             mvprintw(yMax/2 - 8,xMax/2-strlen("Em caso de empate, as viagens mais recentes aparecerão primeiro.")/2,"Em caso de empate, as viagens mais recentes aparecerão primeiro.");
//             mvprintw(yMax/2 - 4,xMax/2-strlen("Caso persistam empates, o resultado é ordenado pelo id da viagem (ordem decrescente)")/2,"Caso persistam empates, o resultado é ordenado pelo id da viagem (ordem decrescente)");
//             mvprintw(yMax/2,xMax/2 - strlen("Insira a primeira data:")/2,"Insira a primeira data:");
//             mvgetstr(yMax/2 + 4,(xMax/2) - strlen(data1)/2,data1);
//             clear();
//             mvprintw(yMax/2,xMax/2,"Insira agora a segunda data:");
//             mvgetstr(yMax/2 + 4,(xMax/2)-strlen(data2)/2,data2);
//             clear();
//             query9_UI(data1,data2,STATS,RIDES,USERS,DRIVERS);
//             // answer_queries_interativo(bla);
//             break;
//     }


// }

// void queries_menu(void *DRIVERS,void *USERS, void *RIDES, void *STATS){
//     int yMax, xMax;
//     getmaxyx(stdscr,yMax,xMax);
//     mvprintw(50, xMax/2 - strlen("Pressione 'Enter' para selecionar, 'Ctrl + C' para sair")/2 ,"Pressione 'Enter' para selecionar, 'Ctrl + C' para sair");    
//     mvprintw(7,(xMax/2) - 8,"Query Selector");
//     WINDOW * opcoes = newwin(30,40,15,xMax/2 - 20);
//     refresh();
//     box(opcoes,0,0);
//     wrefresh(opcoes);
//     keypad(opcoes,true);
//     char *Opcoes[9] = {"Query 1","Query 2","Query 3","Query 4","Query 5","Query 6","Query 7","Query 8","Query 9"};
//     int choice;
//     int highlight = 0;
//     short j = 1;
//         while(j)
//         {
//             for(int i = 0; i < 9; i++){
//                 if(i == highlight) wattron(opcoes,A_REVERSE);
//                 mvwprintw(opcoes,2 + 3*i, 15,Opcoes[i]);
//                 wattroff(opcoes,A_REVERSE);
//             }
//             choice = wgetch(opcoes);
//             switch(choice)
//             {
//                 case(KEY_UP):
//                 if(highlight > 0)
//                     highlight--;
//                 break;
//                 case(KEY_DOWN):
//                 if(highlight < 8)
//                     highlight++;
//                 break;
//                 case(10):
//                     clear();
//                     query_menu(highlight + 1,DRIVERS,USERS,RIDES,STATS);
//                     // mvprintw(0, 0, "Executando a Query %d",highlight+1);
//                     // getch();
//                     j = 0;
//                 default:
//                 break;
//             }
//         }
// }