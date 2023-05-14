#include "estudante.h"
#include "comun.h"
#include "quarto.h"
#include <stdlib.h>
#include <string.h>


struct _estudante{
    comum dados;
    int idade;
    char *localidade;
    quarto q[10];
    int numCandidaturas;
};

estudante criaEstudante(char *login, char *nome, int idade, char *local, char *uni){
    estudante e = (estudante) malloc(sizeof(struct _estudante));
    if(e == NULL);
    e->dados = criaComum(login, nome, uni);
    if(e->dados == NULL) return NULL;
    e->idade = idade;
    strcpy(e->localidade, local);
    e->numCandidaturas = 0;
    return e;
}

void destroiEstudante(estudante e){
    destroiComum(e->dados);
    free(e);
}

char* daLocalidade(estudante e){
    return e->localidade;
}

int daIdade(estudante e){
    return e->idade;
}
