#ifndef ESTUDANTE_H_
#define ESTUDANTE_H_

#include "comun.h"
#include "quarto.h"
#include "estudante.h"

typedef struct _estudante *estudante;

estudante criaEstudante(char *login, char *nome, int idade, char *local, char *uni);
void destroiEstudante(estudante e);
char* daLocalidadeEstudante(estudante e);
int daIdadeEstudante(estudante e);
int existeCandidaturaQuartoEstudante(estudante e, quarto q);
void adicionaCandidaturaEstudante(estudante e, quarto q);
comum daDadosEstudante(estudante e);

#endif