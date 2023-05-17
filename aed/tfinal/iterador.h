#ifndef _H_ITERADOR
#define _H_ITERADOR

typedef struct _iterador *iterador;
iterador criaIterador(void **vector, int n);
void destroiIterador(iterador it);
int temSeguinteIterador(iterador it);
void* seguinteIterador(iterador it);
#endif