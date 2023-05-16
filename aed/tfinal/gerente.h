#ifndef _H_GERENTE
#define _H_GERENTE

#include "comun.h"

typedef struct _gerente *gerente;

gerente criaGerente(char *login, char *nome, char *uni);
void destroiGerente(gerente g);
comum daDadosGerente(gerente g);

#endif