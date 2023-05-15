#include "estudante.h"
#include "sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXL 50


void interpretador(sistema s);
void lerDadosEstudante(char *linha);

/* protótipos das funções usadas no main */
void inserirNovoEstudante(sistema s, char *linha);
void informacaoDoEstudante(sistema s, char *linha);
void inserirNovoGerente(sistema s, char *linha);
void informacaoDoGerente(sistema s, char *linha);
void inserirNovoQuarto(sistema s, char *linha);
void informacaoDoQuarto(sistema s, char *linha);
void modificaEstadoDeQuarto(sistema s, char *linha);
void remocaoDeQuarto(sistema s, char *linha);
void inserirCandidaturaDeEstudanteQuarto(sistema s, char *linha);
void aceitacaoDeCandidatura(sistema s, char *linha);
void listagemDeCandidaturaAQuarto(sistema s, char *linha);


int main(){
    sistema s = criaSistema();
    interpretador(s);
    // destroiSistemaCompleto(s);
    return 0;
}


void interpretador(sistema s){
    char linha[MAXL], cmd[3];
    do {
        fgets(linha,MAXL,stdin);
        cmd[0] = toupper(linha[0]);
        cmd[1] = toupper(linha[1]);
        cmd[2] = '\0';
        if (strcmp(cmd,"IE")==0){
            lerDadosEstudante(linha);
            inserirNovoEstudante(s, linha);
            printf("Acabei com Estudante\n");
        }else if(strcmp(cmd,"DE")==0){

        }else if(strcmp(cmd,"IG")==0){

        }else if(strcmp(cmd,"DG")==0){

        }else if(strcmp(cmd,"IQ")==0){

        }else if(strcmp(cmd,"DQ")==0){

        }else if(strcmp(cmd,"MQ")==0){

        }else if(strcmp(cmd,"RQ")==0){

        }else if(strcmp(cmd,"IC")==0){

        }else if(strcmp(cmd,"AC")==0){

        }else if(strcmp(cmd,"LC")==0){

        }else if(strcmp(cmd,"LQ")==0){

        }else if(strcmp(cmd,"LL")==0){

        }else if(strcmp(cmd,"LT")==0){

        }else {
            printf("Dados inválidos\n\n");
        } 
    }while (strcmp(cmd, "XS")==0);

}

void lerDadosEstudante(char *linha){
    char aux[50];
    for(int i = 0; i < 2; i++){
        fgets(aux, 50, stdin);
        strcat(linha, aux);
    }
}

void inserirNovoEstudante(sistema s, char *linha){
    estudante e;
    char cmd[3], login[30], pnome[30], apelido[30], local[30], uni[30], nome[30];
    int idade;
    if(sscanf(linha, "%s %s %s %s\n%d %s\n%s\n", cmd, login, pnome, apelido, &idade, local, uni) != 7){
        printf("Comando invalidos\n");
    }
    else{
        nome[0] = '\0';
        strcat(nome, pnome);
        strcat(nome, " ");
        strcat(nome, apelido);

        e = criaEstudante(login, nome, idade, local, uni);
        if(e != NULL){
            printf("Registo de estudante executado\n");
        }
        else{
            printf("Errorrrrrr\n");
        }
    }
}

void informacaoDoEstudante(sistema s, char *linha){}
void inserirNovoGerente(sistema s, char *linha){}
void informacaoDoGerente(sistema s, char *linha){}
void inserirNovoQuarto(sistema s, char *linha){}
void informacaoDoQuarto(sistema s, char *linha){}
void modificaEstadoDeQuarto(sistema s, char *linha){}
void remocaoDeQuarto(sistema s, char *linha){}
void inserirCandidaturaDeEstudanteQuarto(sistema s, char *linha){}
void aceitacaoDeCandidatura(sistema s, char *linha){}
void listagemDeCandidaturaAQuarto(sistema s, char *linha){}