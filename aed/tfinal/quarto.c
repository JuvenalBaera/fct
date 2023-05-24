
#include "comun.h"
#include "gerente.h"
#include "estudante.h"
#include "sequencia.h"
#include "quarto.h"
#include "messages.h"
#include <stdlib.h>
#include <string.h>

#define MAX_DESCRICAO 200

struct _quarto {
    char codigo[RESTANTE_DADOS];
    gerente gerenteQuarto;
    sequencia candidaturasAQuarto; // sequencia
    char universidade[TAM_DADOS];
    char residencia[TAM_DADOS];
    char localidade[TAM_DADOS];
    int andar;
    char descricao[MAX_DESCRICAO];
    char ocupado[RESTANTE_DADOS];
};

quarto criaQuarto(char *cod, gerente g, char *uni, char *res, char *local, int andar, char *desc){
    quarto q = (quarto) malloc(sizeof(struct _quarto));
    if(q == NULL) return NULL;
    q->candidaturasAQuarto = criaSequencia(0);
    if(q->candidaturasAQuarto == NULL) return NULL;
    strcpy(q->codigo,  cod);
    strcpy(q->localidade, local);
    strcpy(q->universidade, uni);
    strcpy(q->residencia, res);
    strcpy(q->descricao, desc);
    q->andar = andar;
    strcpy(q->ocupado, "livre");
    q->gerenteQuarto = g;
}

void destroiQuarto( quarto q){
    free(q);
}

void destroiGenQuarto(void* q){
    if(q != NULL)
        destroiQuarto((quarto) q);
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

void ocuparDesocuparQuarto(quarto q, char * oc_desc){
    strcpy(q->ocupado, oc_desc);
}

char *  daOcupadoQuarto(quarto q){
    return q->ocupado;
}

gerente daGerenteQuarto(quarto q){
    return q->gerenteQuarto;
}

sequencia daCanditadurasDoQuarto(quarto q){
    return q->candidaturasAQuarto;
}

void apagaCandidaturasDoQuarto(quarto q){
    destroiSequencia(daCanditadurasDoQuarto(q));
    q->candidaturasAQuarto = criaSequencia(1);
}
