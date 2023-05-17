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
    if(seq->elementos == NULL){
        free(seq);
        return NULL;
    }
    seq->capacidade = cap;
    seq->numElementos = 0;
}

int tamanhoSequencia(sequencia s){
    return s->numElementos;
}

int vaziaSequencia(sequencia s){
    return !tamanhoSequencia(s); // 1 - empty || 0 - not empty
}

void * elementoPosSequencia(sequencia s, int i){
    return s->elementos[i-1];
    // return s->elementos + i;
}

void adicionaPosSequencia(sequencia s, void * elem, int i){
    if(i == s->numElementos)
        s->elementos[i] = elem;
    else if(i < s->numElementos){
	  for(int j = s->numElementos; j > (i-1); j--)   
		s->elementos[j] = s->elementos[j-1]
	s->elementos[i-1] = elem;  
	s->numElementos += 1;
    }
    void * tmp = elem; //tá aqui a fzr o q??? N foi utilizado
}
void * removePosSequencia(sequencia s, int i){
    void * elem = s->elementos[i-1];
    int j;
    for(j=i; j < s->numElementos; j++)
    	s->elementos[j-1] = s->elementos[j];
    s->numElementos--;
    return elem;
}

iterador iteradorSequencia(sequencia s){
	int i;
	void ** aux = malloc(sizeof(void*) * s->numElementos);
	for(i=0; i < s->numElementos; i++)
		aux[i] = s->elementos[i];
	return criaIterador(aux, s->numElementos);
}

void destroiSequencia (sequencia s ){
  free(s->elementos);
  free(s);
}

void destroiSeqEElems(sequencia s, void (*destroi)(void *)){
int j;
	for(j = 0;  j < s->numElementos; j++)
		destroi(s->elementos[j]);
free(s->elementos);
free(s);
}

void incSequencia(sequencia s){
	int i; 
	void ** aux;
	aux = malloc(sizeof(void *) * s->capacidade * 2)
	for(i=0; i < s->numElementos; i++)
		aux[i] = s->elementos[i];
	s->capacidade = capacidade * 2;
	free(s->elementos);
	s->elementos = aux;
	free(aux);	
}
