#include "quarto.h"
#include "gerente.h"
#include "estudante.h"
#include "comun.h"
#include <stdlib.h>
#include <string.h>

#define RESTANTE_DADOS 20
#define TAM_DADOS 50

struct _quarto {
    char codigo[RESTANTE_DADOS];
    gerente gerenteQuarto;
    // estudante estudanteQuarto; // (coleção);
    char universidade[TAM_DADOS];
    char residencia[TAM_DADOS];
    char localidade[TAM_DADOS];
    int andar;
    char descricao[200];
    int ocupado;
};

quarto criaQuarto(char *cod, gerente g, char *uni, char *local, int andar, char *desc){
    quarto q = (quarto) malloc(sizeof(struct _quarto));
    if(q == NULL) return NULL;
    strcpy(q->codigo,  cod);
    strcpy(q->localidade, local);
    strcpy(q->universidade, uni);
    strcpy(q->descricao, desc);
    q->andar = andar;
    q->ocupado = 0;
    q->gerenteQuarto = g;
}

void destroiQuarto( quarto q){
    free(q);
}

char * daCodigoQuarto(quarto q){
    return q->codigo;
}

char * daUniversidadeQuarto(quarto q){
    return q->universidade;
}

char * daResidenciaQuarto(quarto q){
    return q->residencia;
}

char * daLocalidadeQuarto(quarto q){
    return q->localidade;
}

int daAndarQuarto(quarto q){
    return q->andar;
}

char * daDescricaoQuarto(quarto q){
    return q->descricao;
}

void ocuparDesocuparQuarto(quarto q, int oc_desc){
    q->ocupado = oc_desc;
}