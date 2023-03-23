#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ticket.h"

struct _ticket{
    int horas;
    char matricula[MAXMAT];
    int minutos;
    int estadia;
};

ticket criaTicket(char matricula[MAXMAT], int hora, int minutos){
	ticket tick = (ticket) malloc(sizeof(struct _ticket));
	if(tick == NULL) return NULL;
	strcpy(tick->matricula, matricula);
	tick->horas = hora;
	tick->minutos = minutos;
	tick->estadia = 0;
	return tick;
}

void daSaidaTicket(ticket meuTicket, int hora, int minutos){
	int t_entrada_min = 0, t_saida_min = 0, total_min = 0;
	t_entrada_min = meuTicket->horas * 60 + meuTicket->minutos;
	t_saida_min = hora * 60 + minutos;
	total_min = t_saida_min - t_entrada_min;
	if(total_min % 60 == 0)
		total_min /= 60;
	else{
		total_min /= 60;
		total_min++;
	}
	meuTicket->estadia = total_min;
}

char* pegaMatriculaTicket(ticket t){
	return t->matricula;
}

int pegaEstadiaTicket(ticket t){
	return t->estadia;
}

void apagaTicket(ticket t){
	free(t);
}