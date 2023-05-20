/*
 * noSimples.c
 *
 *  Created on: May 3, 2016
 *      Author: carmenmorgado
 */

/*
 * noSimples.c
 *
 *  Created on: 4 de Jan de 2013
 *      Author: fernanda
 */


#include <stdlib.h>
#include <stdio.h>
# include "noSimples.h"

/* Tipo do TAD noSimples */
struct _noSimples{
	void * elem;
	struct _noSimples * seguinte;
};

/* Prot�tipos das fun��es associadas a um aluno - TAD noSimples */

/* Cria��o de um n� simples */
noSimples criaNoSimples(void * e, noSimples seg){
	noSimples aux = (noSimples) malloc(sizeof(struct _noSimples));
	if (aux == NULL)
		return NULL;
	aux->elem = e;
	aux-> seguinte = seg;
	return aux;
}

/* Destrui��o do n� Simples */
void destroiNoSimples(noSimples n){
	free(n);
}

/* Destrui��o do n� Simples e do seu elemento */
void destroiElemENoSimples(noSimples n, void (*destroi)(void *)){
	destroi(n->elem);
	free(n);
}

/* Atribui��o de elemento e ao n� simples */
void atribuiElemNoSimples(noSimples n, void * e){
	n->elem = e;
}

/* Atribui��o de seguinte seg ao n� simples */
void atribuiSegNoSimples(noSimples n, noSimples seg){
	n->seguinte = seg;
}

/* Consulta do elemento do n� simples n */
void * elemNoSimples(noSimples n){
	return n->elem;
}

/* Consulta do seguinte do n� simples n */
noSimples segNoSimples(noSimples n){
	return n->seguinte;
}

