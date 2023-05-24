#ifndef ESTUDANTE_H_
#define ESTUDANTE_H_

#include "comun.h"
#include "quarto.h"
#include "estudante.h"

#define MAX_CANDIDATURA 10

typedef struct _estudante *estudante;

estudante criaEstudante(char *login, char *nome, int idade, char *local, char *uni);
void destroiEstudante(estudante e);
void destroiGenEstudante(void* e);
char* daLocalidadeEstudante(estudante e);
int daIdadeEstudante(estudante e);
int existeCandidaturaQuartoEstudante(estudante e, quarto q);
int adicionaCandidaturaEstudante(estudante e, quarto q);
comum daDadosEstudante(estudante e);
int daQuantidadeDeCandidaturaEstudante(estudante e);
int candidaturaExisteEstudante(estudante e, quarto q);
void apagaCanditadurasDoEstudante(estudante e);
quarto daQuartosQueCandidatouEstudante(estudante e, int indice);

#endif