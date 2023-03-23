#include <stdio.h>
#include <stdlib.h>
#include "ticket.h"

/**** function prototypes ****/
void lerEntrada(char * mat, int * h, int * m);
void lerHora(char * tipo,int * h, int * m);
void apresentarEstadia(ticket t);

int main(void) {

	char matricula[MAXMAT];
	int hora, minutos;
	ticket meuTicket;   // Main ADT (TAD)

	/****initializations and input ****/
	lerEntrada(matricula, &hora, &minutos);
	meuTicket = criaTicket(matricula, hora, minutos);

	lerHora("Saida", &hora, &minutos);
	daSaidaTicket(meuTicket, hora, minutos);

	/****processing****/
		//(empty)

	/****output****/
	apresentarEstadia(meuTicket);
	// apagaTicket(meuTicket);
	return 0;
}

/***
 * 
 *  Complete code here
 * 
 * **/
void lerEntrada(char *matricula, int *hora, int *minutos){
	printf("Matricula: ");
	scanf("%s", matricula);
	lerHora("Entrada", hora, minutos);
}

void lerHora(char *tipo,int *h, int *m){
	printf("%s (hh:mm): ", tipo);
	scanf("%d:%d", h, m);
}

void apresentarEstadia(ticket t){
	printf("O carro com matricula %s teve uma estadia de %d horas\n", pegaMatriculaTicket(t), pegaEstadiaTicket(t));
}
