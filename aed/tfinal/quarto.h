#ifndef _H_QUARTOS
#define _H_QUARTOS
#include "gerente.h"
#include "dicionario.h"

typedef struct _quarto *quarto;

quarto criaQuarto(char *cod, gerente g, char *uni, char *res, char *local, int andar, char *desc);
void destroiQuarto(quarto q);

char * daCodigoQuarto(quarto q);
char * daUniversidadeQuarto(quarto q);
char * daResidenciaQuarto(quarto q);
char * daLocalidadeQuarto(quarto q);
int daAndarQuarto(quarto q);
char * daDescricaoQuarto(quarto q);
void ocuparDesocuparQuarto(quarto q, char * oc_desc);
char * daOcupadoQuarto(quarto q);
gerente daGerenteQuarto(quarto q);
dicionario daCanditadurasDoQuarto(quarto q);
#endif
