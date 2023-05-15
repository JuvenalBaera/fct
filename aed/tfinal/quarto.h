#ifndef _H_QUARTOS
#define _H_QUARTOS
#include "gerente.h"

typedef struct _quarto *quarto;

quarto criaQuarto(char *cod, gerente g, char *uni, char *local, int andar, char *desc);
void destroiQuarto(quarto q);

char * daCodigoQuarto(quarto q);
char * daUni(quarto q);
char * daResidencia(quarto q);
char * daLocalidade(quarto q);
int daAndar(quarto q);
char * daDescricao(quarto q);
void ocuparDesocuparQuarto(quarto q, int oc_desc);

#endif