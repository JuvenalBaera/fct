/*
 * noSimples.h
 *
 *  Created on: May 3, 2016
 *      Author: carmenmorgado
 */


/*
 * noSimples.h
 */

#ifndef NOSIMPLES_H_
#define NOSIMPLES_H_

/* Tipo do TAD noSimples */
typedef struct _noSimples * noSimples;

/* Prot�tipos das fun��es associadas a um aluno - TAD noSimples */

/***********************************************
criaNoSimples - Cria��o da inst�ncia da estrutura associada a um n� simples.
Par�metros:
	e - elemento a guardar no n� (void *)
	seg - endere�o do seguinte n�
Retorno: apontador para a inst�ncia criada
Pr�-condi��es:
***********************************************/
noSimples criaNoSimples(void * e, noSimples seg);

/***********************************************
destroiNoSimples - Liberta a mem�ria ocupada pela inst�ncia da estrutura associada ao n�.
Par�metros:
	n - n� a destruir
Retorno:
Pr�-condi��es: n != NULL
***********************************************/
void destroiNoSimples(noSimples n);

/***********************************************
destroiElemENoSimples - Liberta a mem�ria ocupada pela inst�ncia da estrutura associada ao n�.
Par�metros:
	n - n� a destruir
	destroi - fun��o para destruir o elemento
Retorno:
Pr�-condi��es: n != NULL
***********************************************/
void destroiElemENoSimples(noSimples n, void (*destroi)(void *));

/***********************************************
atribuiElemNoSimples - Guarda o elemento dado no n�.
Par�metros:
	n - n�
	e - elemento (void *)
Retorno:
Pr�-condi��es: n != NULL
***********************************************/
void atribuiElemNoSimples(noSimples n, void * e);

/***********************************************
atribuiSegNoSimples - Guarda o endere�o do n� seguinte dado no n�.
Par�metros:
	n - n�
	seg - endere�o do n� seguinte
Retorno:
Pr�-condi��es: n != NULL
***********************************************/
void atribuiSegNoSimples(noSimples n, noSimples seg);

/***********************************************
elemNoSimples - Retorna o elemento no n� dado.
Par�metros:
	n - n�
Retorno: elemento (void *)
Pr�-condi��es: n != NULL
***********************************************/
void * elemNoSimples(noSimples n);

/***********************************************
segNoSimples - Retorna o endere�o do n� seguinte ao n� dado.
Par�metros:
	n - n�
Retorno: endere�o do n� seguinte
Pr�-condi��es: n != NULL
***********************************************/
noSimples segNoSimples(noSimples n);

#endif /* NOSIMPLES_H_ */
