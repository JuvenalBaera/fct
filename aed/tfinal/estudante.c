#include "estudante.h"
#include "comun.h"
#include "quarto.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_CANDIDATURA 10
struct _estudante{
    comum dados;
    int idade;
    char localidade[TAM_DADOS];
    quarto candidaturasQuartos[MAX_CANDIDATURA];
    int numCandidaturas;
};

estudante criaEstudante(char *login, char *nome, int idade, char *local, char *uni){
    estudante e = (estudante) malloc(sizeof(struct _estudante));
    if(e == NULL) return NULL;
    e->dados = criaComum(login, nome, uni);
    if(e->dados == NULL) {
        free(e);
        return NULL;
    }
    e->idade = idade;
    strcpy(e->localidade, local);
    e->numCandidaturas = 0;
    return e;
}

void destroiEstudante(estudante e){
    destroiComum(e->dados);
    free(e);
}

void destroiGenEstudante(void* e){
    destroiEstudante((estudante) e);
}

int existeCandidaturaQuartoEstudante(estudante e, quarto q){
    for(int i = 0; i < MAX_CANDIDATURA; i++){
        if(strcmp(daCodigoQuarto(e->candidaturasQuartos[i]), daCodigoQuarto(q)) == 0){
            return 1;
        }
    }
    return 0;
}

void adicionaCandidaturaEstudante(estudante e, quarto q){
    e->candidaturasQuartos[e->numCandidaturas++] = q;
}

char* daLocalidadeEstudante(estudante e){
    return e->localidade;
}

int daIdadeEstudante(estudante e){
    return e->idade;
}

comum daDadosEstudante(estudante e){
    return e->dados;
}
