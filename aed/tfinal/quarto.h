#ifndef _H_QUARTOS
#define _H_QUARTOS
#include "gerente.h"

typedef struct _quarto *quarto;

quarto criaQuarto(char *cod, gerente g, char *uni, char *local, int andar, char *desc);
void destroiQuarto(quarto q);

#endif