#include "comun.h"
// #include "estudante.h"
// #include "quarto.h"
// #include "gerente.h"
#include "sistema.h"

#include <stdlib.h>
#include <string.h>

#define MAX_ESTUDANTE 20000
#define MAX_GERENTE 1000
#define MAX_QUARTOS 10000

struct _sistema{
    estudante estudantes[MAX_ESTUDANTE];
    gerente gerentes[MAX_GERENTE];
    quarto quartos[MAX_QUARTOS];
    int qtdEstudantes;
    int qtdGerentes;
    int qtdQuartos;
};


sistema criaSistema(){
    sistema s = (sistema) malloc(sizeof(struct _sistema));
    if(s == NULL) return NULL;

    s->qtdEstudantes = 0;
    s->qtdGerentes = 0;
    s->qtdQuartos = 0;
    return s;
}

void inserirEstudanteSistema(sistema s, estudante e){
    s->estudantes[s->qtdEstudantes++] = e;
}

void inserirGerenteSistema(sistema s, gerente g){
    s->gerentes[s->qtdGerentes++] = g;
}

void inserirQuartoSistema(sistema s, quarto q){
    s->quartos[s->qtdQuartos++] = q;
}

void destroiSistema(sistema s){
    int i = 0;
    for(i = 0; i < s->qtdEstudantes; i++)
        destroiEstudante(s->estudantes[i]);
    
    for(i = 0; i < s->qtdGerentes; i++)
        destroiGerente(s->gerentes[i]);
    
    for(i = 0; i < s->qtdQuartos; i++)
        destroiQuarto(s->quartos[i]);
    
    free(s);
}

//########################## HANDLE ESTUDANTE ##########################
int existeEstudanteNoSistema(sistema s, estudante e){
    for(int i = 0; i < s->qtdEstudantes; i++){
        if(strcmp(daLogin(daDadosEstudante(s->estudantes[i])), daLogin(daDadosEstudante(e))) == 0)
            return 1;
    }
    return 0;
}

estudante daEstudantePorLoginDoSistema(sistema s, char *login){
    for(int i = 0; i < s->qtdEstudantes; i++){
        if(strcmp(daLogin(daDadosEstudante(s->estudantes[i])), login) == 0)
            return s->estudantes[i];
    }
    return NULL;
}


//########################## HANDLE GERENTE ##########################
int existeGerenteNoSistema(sistema s, gerente g){
    for(int i = 0; i < s->qtdGerentes; i++){
        if(strcmp(daLogin(daDadosGerente(s->gerentes[i])), daLogin(daDadosGerente(g))) == 0)
            return 1;
    }
    return 0;
}

gerente daGerentePorLoginDoSistema(sistema s, char *login){
    for(int i = 0; i < s->qtdGerentes; i++){
        if(strcmp(daLogin(daDadosGerente(s->gerentes[i])), login) == 0)
            return s->gerentes[i];
    }
    return NULL;
}


//########################## HANDLE QUARTO ##########################
int existeQuartoNoSistema(sistema s, quarto q){
    for(int i = 0; i < s->qtdQuartos; i++){
        if(strcmp(daCodigoQuarto(s->quartos[i]), daCodigoQuarto(q)) == 0)
            return 1;
    }
    return 0;
}

int existeCodigoDoQuartoNoSistema(sistema s, char * codigo){
    for(int i = 0; i < s->qtdQuartos; i++){
        if(strcmp(daCodigoQuarto(s->quartos[i]), codigo) == 0)
            return 1;
    }
    return 0;
}

quarto daQuartoPorCodigoDoSistema(sistema s, char *cod){
    for(int i = 0; i < s->qtdQuartos; i++){
        if(strcmp(daCodigoQuarto(s->quartos[i]), cod) == 0)
            return s->quartos[i];
    }
    return NULL;
}

int remocaoDoQuartoNoSistema(sistema s, quarto q){
    for(int i = 0; i < s->qtdQuartos; i++){
        if(strcmp(daCodigoQuarto(s->quartos[i]), daCodigoQuarto(q)) == 0){
            destroiQuarto(s->quartos[i]);
            for(int j = i; j < s->qtdQuartos - 1; j++){
                s->quartos[j] = s->quartos[j+1];
            }
            return 1;
        }
    }
    return 0;
}
