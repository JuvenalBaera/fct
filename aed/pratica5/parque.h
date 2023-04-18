#ifndef _H_PARQUE
#define _H_PARQUE

#define MAXPARQUE 150

typedef struct _parque *parque;

/***********************************************
criaParque - Criação da instância da estrutura associada a um parque.
Parâmetros: none
Retorno:    apontador para a instância criada
Pré-condições: none
***********************************************/
parque criaParque();

/***********************************************
daLotacaoParque - Retorna a lotação do parque
Parâmetros:
	p - apontador para um parque
Retorno:
    inteiro com tamanho do parque
Pré-condições: p != NULL
***********************************************/
int daLotacaoParque(parque p);

/***********************************************
daCaixaParque - Devolve a quantidade de caixa
Parâmetros:
	p - apontador para um parque
Retorno:
    float - valor em caixa
Pré-condições: p != NULL
***********************************************/
float daCaixaParque(parque p);

/***********************************************
procuraCarroParque - Procura carro no parque com uma certa matricula
Parâmetros:
    p - apontador para um parque
	mat - char* matricula de um carro
Retorno: 1 se existe o carro e 0 caso contrário
Pré-condições: p != NULL && mat na formatação certa
***********************************************/
int procuraCarroParque(parque p, char *mat);

/***********************************************
entradaCarroParque - Inserir um carro no estacionamento
Parâmetros:
    p - apontador para um parque
	mat - char* matricula de um carro
Retorno: 1 se conseguiu inserir carro e 0 caso contrário (matricula já existe)
Pré-condições:
    p != NULL && mat na formatação certa
    hora - int com as horas de entrada
    minutos - int com as horas de entrada
***********************************************/
int entradaCarroParque(parque p, char *mat, int hora, int minutos);

/***********************************************
destroiParqueETickets - destrói todos os tickets no parque
Parâmetros:
    p - apontador para um parque
Retorno: none
Pré-condições: p != NULL
***********************************************/
void destroiParqueETickets(parque p);

int posCarro(parque p, char * mat);
void tiraCarroParque(parque p, int pos);
float daPrecoParque(parque p, char *mat, int h, int m);
char* pegaMatriculaParque(parque p, int index);

#endif
