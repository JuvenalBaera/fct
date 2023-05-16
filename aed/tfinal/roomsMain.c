#include "estudante.h"
#include "sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXL 50

#define TAMANHO_DADOS 50
#define RESTANTE_DADOS 20

// ################## AUXILIARES ##################
void lerDados(char *linha, int numLinhasALer);
void daNomeCompleto(char pnome[], char apelido[], char nome[]);

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
            informacaoDoGerente(s, linha);
        }else if(strcmp(cmd,"IQ")==0){
            lerDados(linha, 5);
            inserirNovoQuarto(s, linha);
        }else if(strcmp(cmd,"DQ")==0){
            // TODO
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


// ################## AUXILIARES ##################
void lerDados(char *linha, int numLinhasALer){
    char aux[TAMANHO_DADOS];
    for(int i = 0; i < numLinhasALer; i++){
        fgets(aux, 50, stdin);
        strcat(linha, aux);
    }
}

void daNomeCompleto(char pnome[], char apelido[], char nome[]){
    nome[0] = '\0';
    strcat(nome, pnome);
    strcat(nome, " ");
    strcat(nome, apelido); 
}


// ################## ESTUDANTE ##################
void inserirNovoEstudante(sistema s, char *linha){
    estudante e;
    char cmd[3], login[RESTANTE_DADOS], pnome[RESTANTE_DADOS], apelido[RESTANTE_DADOS];
    char local[TAMANHO_DADOS], uni[TAMANHO_DADOS], nome[TAMANHO_DADOS];
    int idade;
    // TODO Espaço (universidade e localidade) está a nos foder
    if(sscanf(linha, "%s %s %s %s\n%d %s\n%s\n", cmd, login, pnome, apelido, &idade, local, uni) == 7){
        daNomeCompleto(pnome, apelido, nome);
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
    }
}

void informacaoDoEstudante(sistema s, char *linha){
    char cmd[3], login[30];
    estudante e;

    if(sscanf(linha, "%s %s\n", cmd, login) == 2){
        e = daEstudantePorLoginDoSistema(s, login);
        if(e == NULL)
            printf("Inexistencia do estudante referido.\n\n");
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


// ################## GERENTE ##################
void inserirNovoGerente(sistema s, char *linha){
    gerente g;

    char cmd[3], login[RESTANTE_DADOS], pnome[RESTANTE_DADOS], apelido[RESTANTE_DADOS];
    char uni[TAMANHO_DADOS], nome[TAMANHO_DADOS];
    
    if(sscanf(linha, "%s %s %s %s\n%s\n",cmd, login, pnome, apelido, uni)==5){
        daNomeCompleto(pnome, apelido, nome);
        g = criaGerente(login, nome, uni);
        if(g != NULL){
            if(existeGerenteNoSistema(s, g)==1){
                printf("utilizador ja existente\n\n");
                destroiGerente(g);
            }
            else{
                inserirGerenteSistema(s, g);
                printf("Registo de gerente executado\n\n");
            }

        }
    }
}

void informacaoDoGerente(sistema s, char *linha){
    char cmd[3], login[30];
    gerente g;

    if(sscanf(linha, "%s %s\n", cmd, login) == 2){
        g = daGerentePorLoginDoSistema(s, login);
        if( g == NULL)
            printf("Inexistencia do gerente referido\n\n");
        else{
            printf("%s, %s\n%s\n\n",daLogin(daDadosGerente(g)), 
                                    daNome(daDadosGerente(g)),
                                    daUniversidade(daDadosGerente(g)));
        }
    }
}

// ################## Quarto ##################

void inserirNovoQuarto(sistema s, char *linha){
    quarto q;
    gerente g;
    char cmd[3], codigoQuarto[RESTANTE_DADOS],  loginGerente[RESTANTE_DADOS], nomeRes[TAMANHO_DADOS];
    char uni[TAMANHO_DADOS], localidade[TAMANHO_DADOS], descricao[200];
    int andar;
    // FIXME
    printf("entrei1\n\n");
    if(sscanf(linha, "%s %s %s\n%s\n%s\n%s\n%d\n%s\n",cmd, codigoQuarto, loginGerente,
                                                     nomeRes, uni, localidade, andar, descricao)==8){
        g = daGerentePorLoginDoSistema(s, loginGerente);
        if( g == NULL)
            printf("Inexistencia do gerente referido\n\n");
        else {
            if(existeCodigoDoQuartoNoSistema(s, codigoQuarto)){
              printf("Quarto existente\n\n");  
            }
            else{
                if(strcmp(daUniversidade(daDadosGerente(g)), uni) == 0)
                    printf("Operacao nao autorizada\n\n");
                else{
                    q = criaQuarto(codigoQuarto, g, uni, localidade, andar, descricao);
                    if( q!= NULL){
                        inserirQuartoSistema(s, q);
                        printf("Registo de quarto executado\n\n");
                    }
                }
            }
        }
    }   
    
}

// TODO
void informacaoDoQuarto(sistema s, char *linha){}
void modificaEstadoDeQuarto(sistema s, char *linha){}
void remocaoDeQuarto(sistema s, char *linha){}
// TODO
void inserirCandidaturaDeEstudanteQuarto(sistema s, char *linha){}
void aceitacaoDeCandidatura(sistema s, char *linha){}
void listagemDeCandidaturaAQuarto(sistema s, char *linha){}
