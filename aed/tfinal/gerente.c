#include "gerente.h"
#include "comun.h"
#include <stdlib.h>

struct _gerente {
    comum dados;
};

gerente criaGerente(char *login, char *nome, char *uni){
    gerente g = (gerente) malloc(sizeof(struct _gerente));
    if(g == NULL) return NULL;
    g->dados = criaComum(login, nome, uni);
    if(g->dados == NULL) return NULL;
    return g;
}

void destroiGerente(gerente g){
    destroiComum(g->dados);
    free(g);
}