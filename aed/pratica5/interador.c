#include "iterador.h"
#include <stdlib.h>

typedef struct _iterador {
    void **vector;
    int capacidade;
    int atual;
};

iterador criaIterador(void ** vector, int n){
    iterador iter = malloc(sizeof(struct _iterador));
    if(iter == NULL ) return NULL;
    iter->vector = vector;
    iter->capacidade = n;
    iter->atual = 0;
    return iter;
}

void destroiIterador (iterador it){
    free(it->vector);
    free(it);
}

int temSeguinteIterador(iterador it){
    return !(it->atual == it->capacidade);
}

void * seguinteIterador(iterador it){
    return it->vector[it->atual++];
}