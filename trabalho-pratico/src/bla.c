#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


typedef struct user {
    char* username;
    char* name;
    char gender;
    int total_distance;
} user;

void print(user* user){
    if(user = NULL) return; 
    printf("%s\n",user->username);
    printf("%s\n",user->name);
    printf("%c\n",user->gender);
    printf("%d\n",user->total_distance);
}

int distance(gconstpointer dist1,gconstpointer dist2){
    int d1 = *((int*) dist1);
    int d2 = *((int*) dist2);
    return d1-d2;
}

int main() {
    user joao;
    char username[16] = "John Das Couves";
    joao.username = username;
    char nome[4] = "Joao";
    joao.name = nome;
    joao.gender = 'M';
    joao.total_distance = 20;

    user maria;
    char username2[17] = "Maria Das Couves";
    maria.username = username2;
    char nome2[5] = "Maria";
    maria.name = nome;
    maria.gender = 'F';
    maria.total_distance = 10;


    user jose;
    char username3[14] = "Ze Das Couves";
    jose.username = username3;
    char nome3[4] = "Jose";
    jose.name = nome;
    jose.gender = 'M';
    jose.total_distance = 40;


    GTree* tree = g_tree_new(&distance);
    gpointer p1 = &joao;
    gpointer p2 = &maria;
    gpointer p3 = &jose;

    gpointer d1 = &joao.total_distance;
    gpointer d2 = &maria.total_distance;
    gpointer d3 = &jose.total_distance;

    g_tree_insert(tree, d1, p1);
    g_tree_insert(tree, d2, p2);
    g_tree_insert(tree, d3, p3);
    GTreeNode* x = g_tree_node_first(tree);
    gpointer n = g_tree_node_value(x);
    user* desc = ((user* ) n);
    printf("%p\n",n);
    printf("%p\n",desc);
    //user* desc = 
    return 0;
}
