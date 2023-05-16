#include "estudante.h"
#include "sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXL 50

// ################## auxiliares ##################
void lerDados(char *linha, int numLinhasALer);
void nomeCompleto(char pnome[], char apelido[], char nome[]);

/* protótipos das funções usadas no main */
void interpretador(sistema s);

// ################## ESTUDANTE ##################
void inserirNovoEstudante(sistema s, char *linha);
void informacaoDoEstudante(sistema s, char *linha);

// ################## GERENTE ##################
void inserirNovoGerente(sistema s, char *linha);
void informacaoDoGerente(sistema s, char *linha);

// ################## QUARTO ##################
void inserirNovoQuarto(sistema s, char *linha);
void informacaoDoQuarto(sistema s, char *linha);
void modificaEstadoDeQuarto(sistema s, char *linha);
void remocaoDeQuarto(sistema s, char *linha);

// ################## OUTRAS ##################
void inserirCandidaturaDeEstudanteQuarto(sistema s, char *linha);
void aceitacaoDeCandidatura(sistema s, char *linha);
void listagemDeCandidaturaAQuarto(sistema s, char *linha);


// ################## FUNÇÃo PRINCIPAL
int main(){
    sistema s = criaSistema();
    interpretador(s);
    // destroiSistemaCompleto(s);
    destroiSistema(s);
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
            lerDados(linha,2);
            inserirNovoEstudante(s, linha);
        }else if(strcmp(cmd,"DE")==0){
            informacaoDoEstudante(s, linha);
        }else if(strcmp(cmd,"IG")==0){
            lerDados(linha, 1);
            inserirNovoGerente(s, linha);
        }else if(strcmp(cmd,"DG")==0){
            // TODO
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

        }else if(strcmp(cmd, "XS")==0){
            printf("Adeus\n\n");
        }
        else {
            printf("Dados invalidos\n\n");
        } 
    }while (strcmp(cmd, "XS") != 0);

}

void lerDados(char *linha, int numLinhasALer){
    char aux[50];
    for(int i = 0; i < numLinhasALer; i++){
        fgets(aux, 50, stdin);
        strcat(linha, aux);
    }
}

void inserirNovoEstudante(sistema s, char *linha){
    estudante e;
    char cmd[3], login[30], pnome[30], apelido[30], local[30], uni[30], nome[30];
    int idade;
    // TODO Espaço (universidade e localidade) está a nos foder
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
            if(existeEstudanteNoSistema(s, e) == 1){
                printf("Utilizador ja existente\n\n");
                destroiEstudante(e);
            }
            else{
                inserirEstudanteSistema(s, e);
                printf("Registo de estudante executado\n\n");
            }
        }
        else{
            printf("Erro ao criar estudante\n");
        }
    }
}


void informacaoDoEstudante(sistema s, char *linha){
    char cmd[3], login[30];
    estudante e;

    if(sscanf(linha, "%s %s\n", cmd, login) != 2){
        printf("Comando invalido\n\n");
    }
    else{
        e = daEstudantePorLoginDoSistema(s, login);
        if(e == NULL)
            printf("Inexistente do estudante referido.\n\n");
        else{
            printf("%s, %s, %d anos, %s\n%s\n\n", daLogin(daDadosEstudante(e)),
                                                daNome(daDadosEstudante(e)),
                                                daIdadeEstudante(e),
                                                daLocalidadeEstudante(e),
                                                daUniversidade(daDadosEstudante(e))
            );
        }
    }
}

void inserirNovoGerente(sistema s, char *linha){
    gerente g;
    char cmd[3], login[30], pnome[30], apelido[30], uni[30], nome[30];
    if(sscanf(linha, "%s %s %s %s\n%s\n",cmd, login, pnome, apelido, uni)==5){
        nome[0] = '\0';
        strcat(nome, pnome);
        strcat(nome, " ");
        strcat(nome, apelido); 
        g = criaGerente(login, nome, uni);
    }
}
// TODO
void informacaoDoGerente(sistema s, char *linha){}
void inserirNovoQuarto(sistema s, char *linha){}
void informacaoDoQuarto(sistema s, char *linha){}
void modificaEstadoDeQuarto(sistema s, char *linha){}
void remocaoDeQuarto(sistema s, char *linha){}
void inserirCandidaturaDeEstudanteQuarto(sistema s, char *linha){}
void aceitacaoDeCandidatura(sistema s, char *linha){}
void listagemDeCandidaturaAQuarto(sistema s, char *linha){}