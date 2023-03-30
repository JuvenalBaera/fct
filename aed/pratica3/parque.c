#include <stdlib.h>
#include <string.h>
#include "ticket.h"
#include "parque.h"

#include <stdio.h>

#define PHORA_1 1.5f
#define PHORA_3 1.0f
#define PHORA_MAIS 0.75f


struct _estacionamento 
{
	ticket vetorLugares[MAXPARQUE];  // declaracao estatica do vetor de tickets
	int cont;                   	 // numero de tickets no parque	
	int cap;						 // capacidade do vetor de tickets
};

typedef struct _estacionamento estacionamento;

struct _parque{
	estacionamento lugares;		// vetor acompanhado
	float caixa;                // valor em caixa
};

parque criaParque(){
	parque p = (parque) malloc(sizeof(struct _parque));
	if (p == NULL) return NULL;
	//TODO
    p->caixa = 0;
    p->lugares.cont = 0;
    p->lugares.cap = MAXPARQUE;
	return p;
}

int daLotacaoParque(parque p){
    return p->lugares.cont;
}

float daCaixaParque(parque p){
    return p->caixa;
}

// int procuraCarroParque(parque p, char *mat){
//     int tamParque = p->lugares.cont;
//     int i = 0, existeMatricula = 0;

//     if(tamParque <= p->lugares.cap){
//         while((i < tamParque) && (existeMatricula == 0)){
//             if(strcmp(pegaMatriculaTicket(p->lugares.vetorLugares[i]), mat) == 0)
//                 existeMatricula = 1;
//             i++;
//         }
//     }
//     return existeMatricula;
// }

// PRE: p != NULL && mat != NULL
int posCarro(parque p, char * mat){
	//TODO
    int tamParque = p->lugares.cont;
    int i = 0;

    if(tamParque <= p->lugares.cap){
        for(;i<tamParque; i++){
            if(strcmp(pegaMatriculaTicket(p->lugares.vetorLugares[i]), mat) == 0)
                return i;
        }
    }
    return -1;
}

int entradaCarroParque(parque p, char *mat, int hora, int minutos){
    int tamParque = p->lugares.cont;
    int i = 0, existeMatricula = posCarro(p, mat);

    if(existeMatricula == -1){
        p->lugares.vetorLugares[tamParque] = criaTicket(mat, hora, minutos);
        p->lugares.cont++;
        return 1;
    }
    return 0;
}


float daPrecoParque(parque p, char *mat, int h, int m){
    int pos = posCarro(p, mat), estadia;
    float pagar = 0.0;
    daSaidaTicket(p->lugares.vetorLugares[pos], h, m);
    
    estadia = pegaEstadiaTicket(p->lugares.vetorLugares[pos]);
    
    switch(estadia){
        case 1:
            pagar = PHORA_1; break;
        case 2: case 3:
            pagar = PHORA_1 + PHORA_3*(estadia-1); break;
        default: pagar = PHORA_1 + 2*PHORA_3 + PHORA_MAIS*(estadia-3);
    }
    p->caixa += pagar;
    return pagar;
}

void tiraCarroParque(parque p, int pos){
    apagaTicket(p->lugares.vetorLugares[pos]);
    for(int i = pos; i < p->lugares.cont-1; i++){
        p->lugares.vetorLugares[i] = p->lugares.vetorLugares[i+1];
    }
    p->lugares.cont--;
}

char* pegaMatriculaParque(parque p, int index){
    return pegaMatriculaTicket(p->lugares.vetorLugares[index]);
}


// PRE: p != NULL
void destroiParque(parque p){
	//TODO
    free(p);
}

// PRE: p != NULL
void destroiParqueETickets(parque p){
	//TODO
    for(int i = 0; i < p->lugares.cont; i++){
        apagaTicket(p->lugares.vetorLugares[i]);
    }
    destroiParque(p);
}
//TODO