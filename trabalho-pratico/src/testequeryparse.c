void *parseQueries(FILE *queries){
    size_t numquerie = BUF
    size_t current = 128
    querie *all = calloc(numquerie, sizeof(querie)); //todas as querys
    //char *um = malloc(sizeof(char)*current); 

    for (size_t i=1, char str[BUF] = { 0 }; fgets(str,BUF,queries);){
        querie* one = malloc(sizeof (querie));
        one->queriex = str[0];

        char *store[20] = { 0 };
        
        size_t j = 0;
        for(char *token = str, *aux = str; token != NULL; token = aux){ 
            token = strtok(aux," ");
            store[j++] = token;

        } 
        strcpy(one->comando,&store[2]);
        one->line = i;
        i++;

        all [i-1] = *one;

        if(i + 1 > BUF){
            all = realloc(all, (BUF *= 2) * sizeof(querie));

        }
    }    
    all[i].line = 1;
    return all;

}

void q_printall(Querys *all){
    int i = 0;
    printf("%d\n", all[i].id);
    while (all[i].line != 1){
        printf("indice: %d\n",all[i].line);
        printf("n: %c\n",all[i].queriex);
        printf("argument: %s\n",all[i].comando);
        printf("------------------------------------------------------------------\n");
        i++;
    }
    printf("done\n");

} 