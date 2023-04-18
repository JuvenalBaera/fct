#ifndef _H_SEQUENCIA
#define _H_SEQUENCIA

/* Tipo de dados: sequencia ---> s1, s2, s3 ....*/
typedef struct _sequencia * sequencia;

/* Prototipos das funcoes associadas a uma sequencia */
/***********************************************
criaSequencia - Criacao da instancia da estrutura associada a uma sequencia.
Parametros: cap - capacidade prevista da sequencia
Retorno: apontador para a instancia criada
Pre-condicoes: cap > 0
***********************************************/
sequencia criaSequencia(int cap);

/***********************************************
vaziaSequencia - Indica se a sequencia está vazia.
Parametros: s - sequencia
Retorno: 1- caso sequencia vazia; 0 - caso contrário
Pre-condicoes: s != NULL
***********************************************/
int vaziaSequencia(sequencia s);

/***********************************************
tamanhoSequencia - Consulta o numero de elementos na sequencia.
Parametros: s - sequencia
Retorno: numero de elementos na sequencia
Pre-condicoes: s != NULL
***********************************************/
int tamanhoSequencia(sequencia s);

/***********************************************
elementoPosSequencia - Consulta o i-esimo elemento na sequencia.
Parametros: s - sequencia
i - posicao na sequencia
Retorno: endereco do elemento
Pre-condicoes: s != NULL && i>0 && i<= tamanhoSequencia(s)
***********************************************/
void * elementoPosSequencia(sequencia s, int i);

/***********************************************
adicionaPosSequencia - Adiciona o elemento dado na posicao i da sequencia.
Parametros: s – sequencia
elem - endereco do elemento
i - posicao
Retorno:
Pre-condicoes: s != NULL && i>0 && i<= tamanhoSequencia(s)+1
***********************************************/
void adicionaPosSequencia(sequencia s, void * elem, int i);

/***********************************************
removePosSequencia - Remove o elemento na posicao i da sequencia.
Parametros: s – sequencia
i - posicao na sequencia
Retorno: retorna o elemento retirado
Pre-condicoes: s != NULL && i>0 && i<= tamanhoSequencia(s)
***********************************************/
void * removePosSequencia(sequencia s, int i);


/***********************************************
iteradorSequencia - Cria e devolve um iterador para a sequencia.
Parametros: s - sequencia
Retorno: iterador da sequencia
Pre-condicoes: s != NULL && vaziaSequencia(s)!=1
***********************************************/
// iterador iteradorSequencia(sequencia s); 

/***********************************************
destroiSequencia - Liberta a memoria ocupada pela instancia da estrutura associada à sequencia.
Parametros: s - sequencia a destruir
Retorno:
Pre-condicoes: s != NULL
***********************************************/
void destroiSequencia (sequencia s );

/***********************************************
destroiSeqEElems - Liberta a memoria ocupada pela instancia da estrutura associada à sequencia e os elementos.
Parametros: s - sequencia a destruir
destroi - função para destruição os elementos
Retorno:
Pre-condicoes: s != NULL
***********************************************/
void destroiSeqEElems(sequencia s, void (*destroi)(void *) );
#endif