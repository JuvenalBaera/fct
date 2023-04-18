#ifndef _H_TICKET
#define _H_TICKET

#define MAXMAT 9

typedef struct _ticket *ticket;

ticket criaTicket(char matricula[MAXMAT], int hora, int minutos);
void daSaidaTicket(ticket meuTicket,int hora, int minutos);
void apagaTicket(ticket t);
char* pegaMatriculaTicket(ticket t);
int pegaEstadiaTicket(ticket t);

#endif