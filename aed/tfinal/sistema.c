#include "comun.h"
#include "estudante.h"
#include "quarto.h"
#include "gerente.h"
#include "sistema.h"
#include "sequencia.h"

#include <stdlib.h>
#include <string.h>

#define MAX_ESTUDANTE 20000
#define MAX_GERENTE 1000
#define MAX_QUARTOS 10000

struct _sistema{
    dicionario estudantes;
    dicionario gerentes;
    dicionario quartos;
};


sistema criaSistema(){
    sistema s = (sistema) malloc(sizeof(struct _sistema));
    if(s == NULL) return NULL;

    s->estudantes = criaDicionario(MAX_ESTUDANTE, 1);
    if(s->estudantes == NULL){
        free(s);
        return NULL;
    }
    s->gerentes = criaDicionario(MAX_GERENTE, 1);
    if(s->gerentes == NULL){
        free(s);
        return NULL;
    }
    s->quartos = criaDicionario(MAX_QUARTOS, 1);
    if(s->quartos == NULL){
        free(s);
        return NULL;
    }
    return s;
}

int inserirEstudanteSistema(sistema s, estudante e){
    if(adicionaElemDicionario(s->estudantes, daLogin(daDadosEstudante(e)), e) == 1)
        return 1;
    return 0;
}

int inserirGerenteSistema(sistema s, gerente g){
    if(adicionaElemDicionario(s->gerentes,daLogin(daDadosGerente(g)), g) == 1)
        return 1;
    return 0;
}

int inserirQuartoSistema(sistema s, quarto q){
    if(adicionaElemDicionario(s->quartos, daCodigoQuarto(q), q) == 1)
        return 1;
    return 0;
}

void destroiSistema(sistema s){
    destroiDicEElems(s->estudantes, destroiGenEstudante);
    // destroiDicionario(s->estudantes);
    
    destroiDicEElems(s->gerentes, destroiGenGerente);
    // destroiDicionario(s->gerentes);

    destroiDicEElems(s->quartos, destroiGenQuarto);
    // destroiDicionario(s->quartos);
    free(s);
}

//########################## HANDLE ESTUDANTE ##########################
int existeEstudanteNoSistema(sistema s, estudante e){
    if(existeElemDicionario(s->estudantes, daLogin(daDadosEstudante(e))) == 1)
        return 1;
    if(existeElemDicionario(s->gerentes, daLogin(daDadosEstudante(e))) == 1)
        return 1;
    return 0;
}

estudante daEstudantePorLoginDoSistema(sistema s, char *login){
    estudante e = elementoDicionario(s->estudantes, login);
    if(e == NULL) return NULL;
    return e;
}


//########################## HANDLE GERENTE ##########################
int existeGerenteNoSistema(sistema s, gerente g){
    if(existeElemDicionario(s->gerentes, daLogin(daDadosGerente(g))) == 1)
        return 1;
    if(existeElemDicionario(s->estudantes, daLogin(daDadosGerente(g))) == 1)
        return 1;
    return 0;
}

gerente daGerentePorLoginDoSistema(sistema s, char *login){
    gerente g = elementoDicionario(s->gerentes, login);
    if(g == NULL) return NULL;
    return g;
}


//########################## HANDLE QUARTO ##########################
int existeCodigoDoQuartoNoSistema(sistema s, char * codigo){
    if(existeElemDicionario(s->quartos, codigo) == 1)
        return 1;
    return 0;
}

int existeQuartoNoSistema(sistema s, quarto q){
    if(existeElemDicionario(s->quartos, daCodigoQuarto(q)) == 1)
        return 1;
    return 0;
}

quarto daQuartoPorCodigoDoSistema(sistema s, char *cod){
    quarto q = elementoDicionario(s->quartos, cod);
    if(q == NULL) return NULL;
    return q;
}

quarto remocaoDoQuartoNoSistema(sistema s, quarto q){
    quarto q1 = (quarto) removeElemDicionario(s->quartos, daCodigoQuarto(q));
    if(q1 == NULL) return NULL;
    return q1;
}

/* void inserirCandidaturaAQuartoSistema(quarto q, estudante e){
    int tam = tamanhoSequencia(daCanditadurasDoQuarto(q));
    adicionaPosSequencia(daCanditadurasDoQuarto(q),e,tam);
} */

void apagaTodasCandidaturasDoEstudanteNoSistema(sistema s, quarto q, estudante e){
    iterador itE = iteradorDicionario(s->estudantes);
    iterador itS;
    int i=0, j=0;
    quarto auxQuarto;
    estudante auxEstudante;

     iterador it = iteradorDicionario(s->quartos);
     sequencia sAux;
     while(temSeguinteIterador(it)){
        auxQuarto = seguinteIterador(it);
        // iterador itS = iteradorSequencia(daCanditadurasDoQuarto(auxQuarto));
        if(existeCandidaturaQuartoEstudante(e, auxQuarto)){
           sAux= daCanditadurasDoQuarto(auxQuarto);
           itS = iteradorSequencia(sAux);
           while(temSeguinteIterador(itS)){
                auxEstudante = seguinteIterador(itS);
                if(strcmp(daLogin(daDadosEstudante(auxEstudante)),  daLogin(daDadosEstudante(e))) == 0){
                    removePosSequencia(daCanditadurasDoQuarto((quarto)elementoDicionario(s->quartos,daCodigoQuarto(auxQuarto))), j);
                }
                j++;
           }
           // removeCandidaturaEstudanteNoQuarto(auxQuarto, e);

        }
        i++;
     }


 // iterador itEQ = iteradorSequencia(daCanditadurasDoQuarto(q));
    // estudante e, e1;
    // while (temSeguinteIterador(itE)){
    //     e = seguinteIterador(itE);
    //     while(temSeguinteIterador(itEQ)){
    //         e1 = seguinteIterador(itEQ);
    //         if(e == e1){
    //             e1 = NULL;
    //         }
    //     }
    // }
    // int i;
    //   for(i=0; i < tamanhoDicionario(s->quartos); i++){
    //    aux = elementoDicionario(s->quartos, daCodigoQuarto(q));


    //     }
    //   }
}