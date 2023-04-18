#include <stdlib.h>
#include "sequencia.h"
#include "parque.h"

typedef struct _sequencia{
    void **elementos;
    int numElementos;
    int capacidade;
};

sequencia criaSequencia(int cap){
    sequencia seq = (sequencia) malloc(sizeof(struct _sequencia));
    if(seq == NULL) return NULL;
    seq->elementos = (void *) malloc(sizeof (void *) * cap);
    if(seq->elementos == NULL) return NULL;
    seq->capacidade = cap + 1;
    seq->numElementos = 0;
}

int vaziaSequencia(sequencia s){
    return s == NULL;
}
int tamanhoSequencia(sequencia s){
    return s->numElementos;
}
void * elementoPosSequencia(sequencia s, int i){
    return s->elementos + i;
}
void adicionaPosSequencia(sequencia s, void * elem, int i){
    if(i == 1)
        s->elementos[i] = elem;
    else if(i == tamanhoSequencia(s))
        s->elementos[tamanhoSequencia(s)] = elem;
    else{

    }
    void * tmp = elem;
}
void * removePosSequencia(sequencia s, int i){
    void * ele = s->elementos + i;
    free(s->elementos + i);
    return ele;
}
// iterador iteradorSequencia(sequencia s){}
void destroiSequencia (sequencia s ){
    for(int i = 0; i < s->capacidade ;i++)
        removePosSequencia(s, i);
        // free(s->capacidade + i);
    free(s);
}
void destroiSeqEElems(sequencia s, void (*destroi)(void *)){}