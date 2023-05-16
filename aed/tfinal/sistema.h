#ifndef _H_SISTEMA
#define _H_SISTEMA

#include "estudante.h"
#include "gerente.h"
#include "quarto.h"

typedef struct _sistema *sistema;
sistema criaSistema();
void destroiSistema(sistema s);

void inserirEstudanteSistema(sistema s, estudante e);
int existeEstudanteNoSistema(sistema s, estudante e);
estudante daEstudantePorLoginDoSistema(sistema s, char *login);

void inserirGerenteSistema(sistema s, gerente g);
int existeGerenteNoSistema(sistema s, gerente g);
gerente daGerentePorLoginDoSistema(sistema s, char *login);

int existeQuartoNoSistema(sistema s, quarto q);
void inserirQuartoSistema(sistema s, quarto q);
quarto daQuartoPoCodigoDoSistema(sistema s, char *cod);

#endif