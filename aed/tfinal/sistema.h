#ifndef _H_SISTEMA
#define _H_SISTEMA

#include "estudante.h"
#include "gerente.h"
#include "quarto.h"

typedef struct _sistema *sistema;
sistema criaSistema();
void destroiSistema(sistema s);

int inserirEstudanteSistema(sistema s, estudante e);
int existeEstudanteNoSistema(sistema s, estudante e);
estudante daEstudantePorLoginDoSistema(sistema s, char *login);

int inserirGerenteSistema(sistema s, gerente g);
int existeGerenteNoSistema(sistema s, gerente g);
gerente daGerentePorLoginDoSistema(sistema s, char *login);

int inserirQuartoSistema(sistema s, quarto q);
int existeQuartoNoSistema(sistema s, quarto q);
quarto daQuartoPorCodigoDoSistema(sistema s, char *cod);
int existeCodigoDoQuartoNoSistema(sistema s, char * codigo);
quarto remocaoDoQuartoNoSistema(sistema s, quarto q);
// void inserirCandidaturaAQuartoSistema(sistema s, quarto q, estudante e);
void apagaTodasCandidaturasDoEstudanteNoSistema(sistema s, quarto q, estudante e);
#endif