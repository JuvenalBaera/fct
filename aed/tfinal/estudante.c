#include "estudante.h"
#include "comun.h"
#include "quarto.h"
#include <stdlib.h>
#include <string.h>

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
    for(int i = 0; i < MAX_CANDIDATURA; i++)
        e->candidaturasQuartos[i] = NULL;
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
        if(e->candidaturasQuartos[i] != NULL){
            if(strcmp(daCodigoQuarto(e->candidaturasQuartos[i]), daCodigoQuarto(q)) == 0){
                return 1;
            }
        }
    }
    return 0;
}

int adicionaCandidaturaEstudante(estudante e, quarto q){
    if(e->numCandidaturas < MAX_CANDIDATURA){
        e->candidaturasQuartos[e->numCandidaturas++] = q;
        return 1;
    }
    return 0;
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

int daQuantidadeDeCandidaturaEstudante(estudante e){
    int total = 0;
    for(int i = 0; i < MAX_CANDIDATURA; i++){
        if(e->candidaturasQuartos[i] != NULL)
            total++;
    }
    return total;
}

int candidaturaExisteEstudante(estudante e, quarto q){
    for(int i = 0; i < MAX_CANDIDATURA; i++){
        if(e->candidaturasQuartos[i] != NULL){
            if(strcmp(daCodigoQuarto(e->candidaturasQuartos[i]), daCodigoQuarto(q)) == 0)
                return 1;
        }
    }
    return 0;
}

void apagaCanditadurasDoEstudante(estudante e){
    for(int i = 0; i < MAX_CANDIDATURA; i++)
        e->candidaturasQuartos[i] = NULL;
    e->numCandidaturas = 0;
}
