#include "messages.h"
#include "estudante.h"
#include "sistema.h"
#include "dicionario.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXL 50
#define TAMANHO_CMD 3

#define TAMANHO_DADOS 50
#define RESTANTE_DADOS 20
#define MAX_DESCRICAO 200

// ################## AUXILIARES ##################

/* protótipos das funções usadas no main */
void interpretador(sistema s);

// ################## ESTUDANTE ##################
void inserirNovoEstudante(sistema s);
void informacaoDoEstudante(sistema s, char *login);

// ################## GERENTE ##################
void inserirNovoGerente(sistema s);
void informacaoDoGerente(sistema s, char *login);

// ################## QUARTO ##################
void inserirNovoQuarto(sistema s);
void informacaoDoQuarto(sistema s, char *codigo); // TODO
void modificaEstadoDeQuarto(sistema s);
void remocaoDeQuarto(sistema s);

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
    char linha[MAXL], cmd[TAMANHO_CMD];
    do {
        printf("> ");
        scanf("%s", cmd);
        cmd[0] = toupper(cmd[0]);
        cmd[1] = toupper(cmd[1]);
        cmd[2] = '\0';
        if (strcmp(cmd,"IE")==0){
            getchar();
            inserirNovoEstudante(s);
        }else if(strcmp(cmd,"DE")==0){
            getchar();
            if(scanf("%s", linha) == 1)
                informacaoDoEstudante(s, linha);
        }else if(strcmp(cmd,"IG")==0){
            getchar();
            inserirNovoGerente(s);
        }else if(strcmp(cmd,"DG")==0){
            getchar();
            if(scanf("%s", linha) == 1){
                informacaoDoGerente(s, linha);
            }
        }else if(strcmp(cmd,"IQ")==0){
            // lerDados(linha, 5);
            getchar();
            inserirNovoQuarto(s);
        }else if(strcmp(cmd,"DQ")==0){
            if(scanf("%s", linha)){
                informacaoDoQuarto(s, linha);
            }
        }else if(strcmp(cmd,"MQ")==0){
            modificaEstadoDeQuarto(s);
        }else if(strcmp(cmd,"RQ")==0){ 
            remocaoDeQuarto(s);
        }else if(strcmp(cmd,"IC")==0){
            inserirCandidaturaDeEstudanteQuarto(s, linha);
        }else if(strcmp(cmd,"AC")==0){
            aceitacaoDeCandidatura(s, linha);
        }else if(strcmp(cmd,"LC")==0){
            listagemDeCandidaturaAQuarto(s, linha);
        }else if(strcmp(cmd,"LQ")==0){

        }else if(strcmp(cmd,"LL")==0){

        }else if(strcmp(cmd,"LT")==0){

        }else if(strcmp(cmd, "XS")==0){
            printf("%s\n\n", MSG_SAIR);
        }else if(strcmp(cmd,"#")==0){
            printf("\n");
        }
        else {
            printf("%s\n\n", MSG_COMANDO_INVALIDO);
        } 
    }while (strcmp(cmd, "XS") != 0);

}


// ################## AUXILIARES ##################
char* formatacaoLeitura(int tamanho){
    char str[10];
    char *format = malloc(sizeof(char) * 10);
    strcpy(format, "%");
    sprintf(str, "%d[^\n]", tamanho);
    strcat(format, str);
    return format;
}


// ################## ESTUDANTE ##################
void inserirNovoEstudante(sistema s){
    estudante e;
    char  login[RESTANTE_DADOS], local[TAMANHO_DADOS], uni[TAMANHO_DADOS], nome[TAMANHO_DADOS];
    int idade, lido=0;

    char *formatacao = formatacaoLeitura(TAM_DADOS);

    lido += scanf("%s ", login); // Nome Estudante
    lido += scanf(formatacao, nome); // 19\n
    lido += scanf("%d ", &idade);
    lido += scanf(formatacao, local); getchar();
    lido += scanf(formatacao, uni);

    if(lido == 5){
        e = criaEstudante(login, nome, idade, local, uni);
        if(e != NULL){
            if(existeEstudanteNoSistema(s, e) == 1){
                printf("%s\n\n", MSG_UTILIZADOR_EXISTENTE);
                destroiEstudante(e);
            }
            else{
                if(inserirEstudanteSistema(s, e) == 1)
                    printf("%s\n\n", MSG_REGISTO_ESTUDANTE_OK);
            }
        }
    }
    free(formatacao);
}

void informacaoDoEstudante(sistema s, char *login){
    estudante e = daEstudantePorLoginDoSistema(s, login);
    if(e == NULL){
        printf("%s\n\n", MSG_ESTUDANTE_INEXISTENTE);
    }
    else{
        printf("%s, %s, %d anos, %s\n%s\n\n", daLogin(daDadosEstudante(e)),
                                            daNome(daDadosEstudante(e)),
                                            daIdadeEstudante(e),
                                            daLocalidadeEstudante(e),
                                            daUniversidade(daDadosEstudante(e))
        );
    }
}


// ################## GERENTE ##################
void inserirNovoGerente(sistema s){
    gerente g;

    char login[RESTANTE_DADOS], uni[TAMANHO_DADOS], nome[TAMANHO_DADOS];
    int lido = 0;

    char *formatacao = formatacaoLeitura(TAM_DADOS);

    lido += scanf("%s ", login);
    lido += scanf(formatacao, nome); getchar();
    lido += scanf(formatacao, uni);

    if(lido == 3){
        g = criaGerente(login, nome, uni);
        if(g != NULL){
            if(existeGerenteNoSistema(s, g)==1){
                printf("%s\n\n", MSG_UTILIZADOR_EXISTENTE);
                destroiGerente(g);
            }
            else{
                inserirGerenteSistema(s, g);
                printf("%s\n\n", MSG_REGISTO_GERENTE_OK);
            }

        }
    }
}

void informacaoDoGerente(sistema s, char *login){
    gerente g = daGerentePorLoginDoSistema(s, login);
    if( g == NULL){
        printf("%s\n\n", MSG_GERENTE_INEXISTENTE);
    }
    else{
        printf("%s, %s\n%s\n\n",daLogin(daDadosGerente(g)), 
                                daNome(daDadosGerente(g)),
                                daUniversidade(daDadosGerente(g)));
    }
}


// ################## QUARTO ##################
void inserirNovoQuarto(sistema s){
    quarto q;
    gerente g;
    char codigoQuarto[RESTANTE_DADOS],  loginGerente[RESTANTE_DADOS], residencia[TAMANHO_DADOS];
    char uni[TAMANHO_DADOS], localidade[TAMANHO_DADOS], descricao[MAX_DESCRICAO];
    int andar, lido = 0;

    char *formatacao = formatacaoLeitura(TAM_DADOS);
    lido += scanf("%s ",codigoQuarto);
    lido += scanf(formatacao,loginGerente); getchar();
    lido += scanf(formatacao,residencia); getchar();
    lido += scanf(formatacao,uni); getchar();
    lido += scanf(formatacao,localidade); getchar();
    lido += scanf("%d ", &andar);

    free(formatacao);
    formatacao = formatacaoLeitura(MAX_DESCRICAO);

    lido += scanf(formatacao,descricao);

    if(lido == 7){
        g = daGerentePorLoginDoSistema(s, loginGerente);
        if( g == NULL){
            printf("%s\n\n", MSG_GERENTE_INEXISTENTE);
        }
        else {
            if(existeCodigoDoQuartoNoSistema(s, codigoQuarto)){
              printf("%s\n\n", MSG_QUARTO_EXISTENTE);
            }
            else{
                if(strcmp(daUniversidade(daDadosGerente(g)), uni) == 0){
                    q = criaQuarto(codigoQuarto, g, uni, residencia, localidade, andar, descricao);
                    if(q != NULL){
                        inserirQuartoSistema(s, q);
                        printf("%s\n\n", MSG_REGISTO_QUARTO_OK);
                    }
                }
                else{
                    printf("%s\n\n", MSG_OP_NAO_AUTORIZADA);
                }
            }
        }
    }   
    free(formatacao);
}

void informacaoDoQuarto(sistema s, char *codigo){
    quarto q;
    
    q = daQuartoPorCodigoDoSistema(s, codigo);
    if(q == NULL){
        printf("%s\n\n", MSG_INEXISTENCIA_QUARTOS);
    }
    else{
        printf("%s, %s\n%s\n%s\n%d\n%s\n%s\n\n", daCodigoQuarto(q), daResidenciaQuarto(q),
                                            daUniversidadeQuarto(q), daLocalidadeQuarto(q),
                                            daAndarQuarto(q), daDescricaoQuarto(q),daOcupadoQuarto(q));
    }
    
}

void modificaEstadoDeQuarto(sistema s){
    char codigo[RESTANTE_DADOS], loginGerente[RESTANTE_DADOS], estado[RESTANTE_DADOS];
    quarto q;
    gerente g;
    if(scanf("%s %s %s\n", codigo, loginGerente, estado) == 3){
        q = daQuartoPorCodigoDoSistema(s, codigo);
        if(q == NULL){
            printf("%s\n\n", MSG_INEXISTENCIA_QUARTOS);
        }
        else{
            g=daGerentePorLoginDoSistema(s,loginGerente);
            if(g == NULL){
                printf("%s\n\n", MSG_GERENTE_INEXISTENTE);
            }
            else{
                if(strcmp(daLogin(daDadosGerente(daGerenteQuarto(q))), loginGerente) == 0){
                    if(strcmp(estado, "ocupado") == 0){
                        if(vazioDicionario(daCanditadurasDoQuarto(q)) == 1){
                            ocuparDesocuparQuarto(q, estado);
                            printf("%s\n\n", MSG_QUARTO_ATUALIZADO);
                        }
                        else{
                            printf("%s\n\n", MSG_CANDIDATURAS_ACTIVAS);
                        }
                    }
                    else{
                        ocuparDesocuparQuarto(q, estado);
                        printf("%s\n\n", MSG_QUARTO_ATUALIZADO);
                    }
                }
                else{
                    printf("%s\n\n", MSG_OP_NAO_AUTORIZADA);
                }
            }
        }
    }
}

void remocaoDeQuarto(sistema s){
    char codigo[RESTANTE_DADOS], loginGerente[RESTANTE_DADOS];
    quarto q;
    gerente g;
    if(scanf("%s %s\n", codigo, loginGerente) == 2){
        q = daQuartoPorCodigoDoSistema(s, codigo);
        if(q == NULL){
            printf("%s\n\n", MSG_INEXISTENCIA_QUARTOS);
        }
        else{
            g = daGerentePorLoginDoSistema(s, loginGerente);
            if(g == NULL){
                printf("%s\n\n", MSG_GERENTE_INEXISTENTE);
            }
             else{
                if(strcmp(daLogin(daDadosGerente(daGerenteQuarto(q))), loginGerente) == 0){
                    if(vazioDicionario(daCanditadurasDoQuarto(q)) == 1){
                        if(remocaoDoQuartoNoSistema(s, q) == 1){
                            printf("%s\n\n", MSG_REMOCAO_QUARTO_OK);
                        }
                    }
                    else{
                        printf("%s\n\n", MSG_CANDIDATURAS_ACTIVAS);
                    }
                }
                else{
                    printf("%s\n\n", MSG_OP_NAO_AUTORIZADA);
                }
            }
        }
    }
}
// TODO
void inserirCandidaturaDeEstudanteQuarto(sistema s, char *linha){}
void aceitacaoDeCandidatura(sistema s, char *linha){}
void listagemDeCandidaturaAQuarto(sistema s, char *linha){}
