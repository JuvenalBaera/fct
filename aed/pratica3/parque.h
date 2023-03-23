#ifndef _H_PARQUE
#define _H_PARQUE

#define MAXPARQUE 150

typedef struct _parque *parque;

parque criaParque();
int daLotacaoParque(parque p);
float daCaixaParque(parque p);
int procuraCarroParque(parque p, char *mat);
int entradaCarroParque(parque p, char *mat, int hora, int minutos);
void destroiParqueETickets(parque fctParque);
int posCarro(parque p, char * mat);
void tiraCarroParque(parque p, char *mat);
float daPrecoParque(parque p, char *mat, int h, int m);
char* pegaMatriculaParque(parque p, int index);

#endif
