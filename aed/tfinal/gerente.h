#ifndef _H_GERENTE
#define _H_GERENTE

typedef struct _gerente *gerente;

gerente criaGerente(char *login, char *nome, char *uni);
void destroiGerente(gerente g);

#endif