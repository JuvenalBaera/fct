#include <stdlib.h>
#include <string.h>
#include "comun.h"

struct _comum
{
    char login[RESTANTE_DADOS];
    char nome[TAM_DADOS];
    char unversidade[TAM_DADOS];
};

comum criaComum(char *login, char *nome, char *uni){
    comum com = (comum) malloc(sizeof(struct _comum));
    if (com == NULL) return NULL;
    strcpy(com->login, login);
    strcpy(com->nome, nome);
    strcpy(com->unversidade, uni);
    return com;
}

void destroiComum(comum com){
    free(com);
}

char* daLogin(comum com){
    return com->login;
}
char* daNome(comum com){
    return com->nome;
}
char* daUniversidade(comum com){
    return com->unversidade;
}
