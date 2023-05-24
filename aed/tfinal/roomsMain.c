#include "messages.h"
#include "estudante.h"
#include "sistema.h"

#include "sequencia.h"
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
void mostrarEstudante(estudante e);

// ################## GERENTE ##################
void mostrarGerente(gerente g);
void inserirNovoGerente(sistema s);
void informacaoDoGerente(sistema s, char *login);

// ################## QUARTO ##################
void mostrarQuarto(quarto q);
void inserirNovoQuarto(sistema s);
void informacaoDoQuarto(sistema s, char *codigo);
void modificaEstadoDeQuarto(sistema s);
void remocaoDeQuarto(sistema s, char *linha);

// ################## OUTRAS ##################
void inserirCandidaturaDeEstudanteQuarto(sistema s, char *linha);
void aceitacaoDeCandidatura(sistema s, char *linha);
void listagemDeCandidaturaAQuarto(sistema s, char *linha);


// ################## FUNÇÃo PRINCIPAL
int main(){
    sistema s = criaSistema();
    interpretador(s);
    destroiSistema(s);
    return 0;
}


void interpretador(sistema s){
    char linha[MAXL], cmd[TAMANHO_CMD], comentario[MAX_DESCRICAO];
    do {
        printf("> ");
        scanf("%s", cmd);
        cmd[0] = toupper(cmd[0]);
        cmd[1] = toupper(cmd[1]);
        cmd[2] = '\0';
        if (strcmp(cmd,"IE")==0){
            getchar();
            inserirNovoEstudante(s);
            printf("\n\n");
        }else if(strcmp(cmd,"DE")==0){
            getchar();
            if(scanf("%s", linha) == 1)
                informacaoDoEstudante(s, linha);
            else
                printf("%s", MSG_COMANDO_INVALIDO);
            printf("\n\n");
        }else if(strcmp(cmd,"IG")==0){
            getchar();
            inserirNovoGerente(s);
            printf("\n\n");
        }else if(strcmp(cmd,"DG")==0){
            getchar();
            if(scanf("%s", linha) == 1)
                informacaoDoGerente(s, linha);
            else
                printf("%s", MSG_COMANDO_INVALIDO);
            printf("\n\n");
        }else if(strcmp(cmd,"IQ")==0){
            getchar();
            inserirNovoQuarto(s);
            printf("\n\n");
        }else if(strcmp(cmd,"DQ")==0){
            if(scanf("%s", linha)){
                informacaoDoQuarto(s, linha);
            }
            printf("\n\n");
        }else if(strcmp(cmd,"MQ")==0){
            modificaEstadoDeQuarto(s);
            printf("\n\n");
        }else if(strcmp(cmd,"RQ")==0){ 
            fgets(linha, MAXL, stdin);
            remocaoDeQuarto(s, linha);
            printf("\n\n");
        }else if(strcmp(cmd,"IC")==0){
            fgets(linha, MAXL, stdin);
            inserirCandidaturaDeEstudanteQuarto(s, linha);
            printf("\n\n");
        }else if(strcmp(cmd,"AC")==0){
            fgets(linha, MAXL, stdin);
            aceitacaoDeCandidatura(s, linha);
            printf("\n\n");
        }else if(strcmp(cmd,"LC")==0){
            fgets(linha, MAXL, stdin);
            listagemDeCandidaturaAQuarto(s, linha);
            printf("\n");
        }else if(strcmp(cmd,"LQ")==0){

        }else if(strcmp(cmd,"LL")==0){

        }else if(strcmp(cmd,"LT")==0){

        }else if(strcmp(cmd, "XS")==0){
            printf("%s", MSG_SAIR);
            printf("\n\n");
        }else if(strcmp(cmd,"#")==0){
            fgets(comentario, MAX_DESCRICAO, stdin);
            printf("\n\n");
        }
        else {
            fgets(comentario, MAX_DESCRICAO, stdin);
            printf("%s", MSG_COMANDO_INVALIDO);
            printf("\n\n");
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
void mostrarEstudante(estudante e){
    printf("%s, ", daLogin(daDadosEstudante(e)));
    printf("%s, ", daNome(daDadosEstudante(e)));
    printf("%d anos, ", daIdadeEstudante(e));
    printf("%s\n", daLocalidadeEstudante(e));
    printf("%s", daUniversidade(daDadosEstudante(e)));
}

void inserirNovoEstudante(sistema s){
    estudante e;
    char  login[RESTANTE_DADOS], local[TAMANHO_DADOS], uni[TAMANHO_DADOS], nome[TAMANHO_DADOS];
    int idade, lido=0;

    char *formatacao = formatacaoLeitura(TAM_DADOS);

    lido += scanf("%s ", login);
    lido += scanf(formatacao, nome);
    lido += scanf("%d ", &idade);
    lido += scanf(formatacao, local); getchar();
    lido += scanf(formatacao, uni);

    if(lido == 5){
        e = criaEstudante(login, nome, idade, local, uni);
        if(e != NULL){
            if(existeEstudanteNoSistema(s, e) == 0){
                if(inserirEstudanteSistema(s, e) == 1)
                    printf("%s", MSG_REGISTO_ESTUDANTE_OK);
            }
            else{
                printf("%s", MSG_UTILIZADOR_EXISTENTE);
                destroiEstudante(e);
            }
        }
    }
    else
        printf("%s", MSG_COMANDO_INVALIDO);
    free(formatacao);
}

void informacaoDoEstudante(sistema s, char *login){
    estudante e = daEstudantePorLoginDoSistema(s, login);
    if(e != NULL)
        mostrarEstudante(e);
    else
        printf("%s", MSG_ESTUDANTE_INEXISTENTE);
}


// ################## GERENTE ##################
void mostrarGerente(gerente g){
    printf("%s, ", daLogin(daDadosGerente(g)));
    printf("%s\n", daNome(daDadosGerente(g)));
    printf("%s", daUniversidade(daDadosGerente(g)));
}

void inserirNovoGerente(sistema s){
    char login[RESTANTE_DADOS], uni[TAMANHO_DADOS], nome[TAMANHO_DADOS];
    gerente g;
    int lido = 0;
    char *formatacao = formatacaoLeitura(TAM_DADOS);

    lido += scanf("%s ", login);
    lido += scanf(formatacao, nome); getchar();
    lido += scanf(formatacao, uni);

    if(lido == 3){
        g = criaGerente(login, nome, uni);
        if(g != NULL){
            if(existeGerenteNoSistema(s, g)==0){
                inserirGerenteSistema(s, g);
                printf("%s", MSG_REGISTO_GERENTE_OK);
            }
            else{
                printf("%s", MSG_UTILIZADOR_EXISTENTE);
                destroiGerente(g);
            }
        }
    }
    else
        printf("%s", MSG_COMANDO_INVALIDO);
}

void informacaoDoGerente(sistema s, char *login){
    gerente g = daGerentePorLoginDoSistema(s, login);
    if( g != NULL)
        mostrarGerente(g);
    else
        printf("%s", MSG_GERENTE_INEXISTENTE);
}


// ################## QUARTO ##################
void mostrarQuarto(quarto q){
    printf("%s, ", daCodigoQuarto(q));
    printf("%s\n", daResidenciaQuarto(q));
    printf("%s\n", daUniversidadeQuarto(q));
    printf("%s\n", daLocalidadeQuarto(q));
    printf("%d\n", daAndarQuarto(q));
    printf("%s\n", daDescricaoQuarto(q));
    printf("%s", daOcupadoQuarto(q));
}

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
        if(existeCodigoDoQuartoNoSistema(s, codigoQuarto) == 0){
            g = daGerentePorLoginDoSistema(s, loginGerente);
            if(g != NULL){ 
                if(strcmp(daUniversidade(daDadosGerente(g)), uni) == 0){
                    q = criaQuarto(codigoQuarto, g, uni, residencia, localidade, andar, descricao);
                    if(inserirQuartoSistema(s, q) == 1)
                        printf("%s", MSG_REGISTO_QUARTO_OK);
                }
                else
                    printf("%s", MSG_OP_NAO_AUTORIZADA);
            }
            else
                printf("%s", MSG_GERENTE_INEXISTENTE);
        }
        else
            printf("%s", MSG_QUARTO_EXISTENTE);
    }   
    else
        printf("%s", MSG_COMANDO_INVALIDO);
    free(formatacao);
}

void informacaoDoQuarto(sistema s, char *codigo){
    quarto q;
    q = daQuartoPorCodigoDoSistema(s, codigo);
    if(q != NULL)
        mostrarQuarto(q);
    else
        printf("%s", MSG_QUARTO_INEXISTENTE);
}

void modificaEstadoDeQuarto(sistema s){
    char codigo[RESTANTE_DADOS], loginGerente[RESTANTE_DADOS], estado[RESTANTE_DADOS];
    quarto q;
    gerente g;
    if(scanf("%s %s %s", codigo, loginGerente, estado) == 3){
        q = daQuartoPorCodigoDoSistema(s, codigo);
        if(q != NULL){
            g=daGerentePorLoginDoSistema(s,loginGerente);
            if(g != NULL){
                if(strcmp(daLogin(daDadosGerente(daGerenteQuarto(q))), loginGerente) == 0){
                    if(strcmp(estado, MSG_OCUPADO) == 0){
                        if(vaziaSequencia(daCanditadurasDoQuarto(q)) == 1){
                            ocuparDesocuparQuarto(q, MSG_OCUPADO);
                            printf("%s", MSG_QUARTO_ATUALIZADO);
                        }
                        else
                            printf("%s", MSG_CANDIDATURAS_ACTIVAS);
                    }
                    else{
                        ocuparDesocuparQuarto(q, MSG_LIVRE);
                        printf("%s", MSG_QUARTO_ATUALIZADO);
                    }
                }
                else
                    printf("%s", MSG_OP_NAO_AUTORIZADA);
            }
            else
                printf("%s", MSG_OP_NAO_AUTORIZADA);
        }
        else
            printf("%s", MSG_QUARTO_INEXISTENTE);
    }
    else
        printf("%s", MSG_COMANDO_INVALIDO);
}

void remocaoDeQuarto(sistema s, char *linha){
    char codigo[RESTANTE_DADOS], loginGerente[RESTANTE_DADOS];
    quarto q;
    gerente g;
    
    if(sscanf(linha, "%s %s", codigo, loginGerente) == 2){
        q = daQuartoPorCodigoDoSistema(s, codigo);
        if(q != NULL){
            g = daGerentePorLoginDoSistema(s, loginGerente);
            if(g != NULL){
                if(strcmp(daLogin(daDadosGerente(daGerenteQuarto(q))), loginGerente) == 0){
                    if(tamanhoSequencia(daCanditadurasDoQuarto(q)) == 0){
                        if(remocaoDoQuartoNoSistema(s, q) != NULL){
                            printf("%s", MSG_REMOCAO_QUARTO_OK);
                            destroiQuarto(q);
                        }
                    }
                    else
                        printf("%s", MSG_CANDIDATURAS_ACTIVAS);
                }
                else
                    printf("%s", MSG_OP_NAO_AUTORIZADA);
            }
            else
                printf("%s", MSG_OP_NAO_AUTORIZADA);
        }
        else
            printf("%s", MSG_QUARTO_INEXISTENTE);
    }
    else
        printf("%s", MSG_COMANDO_INVALIDO);
}

void inserirCandidaturaDeEstudanteQuarto(sistema s, char *linha){
    char login[RESTANTE_DADOS], codigo[RESTANTE_DADOS];
    estudante e;
    quarto q;
    int tam;

    if(sscanf(linha, "%s %s", login, codigo) == 2){
        e = daEstudantePorLoginDoSistema(s, login);
        if(e != NULL){
            if(daQuantidadeDeCandidaturaEstudante(e) < MAX_CANDIDATURA){
                q = daQuartoPorCodigoDoSistema(s, codigo);
                if(q != NULL){
                    if(strcmp(daOcupadoQuarto(q), MSG_LIVRE) == 0){
                        if(candidaturaExisteEstudante(e, q) == 0){
                            adicionaCandidaturaEstudante(e, q);
                                tam = tamanhoSequencia(daCanditadurasDoQuarto(q));
                                adicionaPosSequencia(daCanditadurasDoQuarto(q), e, tam+1);
                              /*  printf("--------------");
                                printf("tamanho: %d\n", tam);
                                for(int h=0; h < tamanhoSequencia(daCanditadurasDoQuarto(q))-1; h++){
                                    printf("h: %d  %s  %s  %s\n",h,daLogin(daDadosEstudante(elementoPosSequencia(daCanditadurasDoQuarto(q), h))), daNome(daDadosEstudante(elementoPosSequencia(daCanditadurasDoQuarto(q), h))),daUniversidade(daDadosEstudante(elementoPosSequencia(daCanditadurasDoQuarto(q), h))));
                                    // printf("%s\n",daCodigoQuarto(daQuartosQueCandidatouEstudante(elementoPosSequencia(daCanditadurasDoQuarto(q), h))));
                                   // printf("--------------");
                                }  */
                              //  printf(""); 
                            
                                printf("%s", MSG_REGISTO_CANDIDATURA_OK);
                            // }
                           /* else{
                                printf("%s", MSG_OP_NAO_AUTORIZADA);
                            } */
                        }
                        else
                            printf("%s", MSG_CANDIDATURA_EXISTENTE);
                    }
                    else
                        printf("%s", MSG_QUARTO_OCUPADO);
                }
                else
                    printf("%s", MSG_QUARTO_INEXISTENTE);
            }
            else
                printf("%s", MSG_OP_NAO_AUTORIZADA);
        }
        else
            printf("%s", MSG_ESTUDANTE_INEXISTENTE);
    }
    else
        printf("%s", MSG_COMANDO_INVALIDO);
}

void aceitacaoDeCandidatura(sistema s, char *linha){
    char codigoQ[RESTANTE_DADOS], loginE[RESTANTE_DADOS], loginG[RESTANTE_DADOS];
    quarto q;
    gerente g;
    estudante e;
    if(sscanf(linha, "%s %s %s", codigoQ, loginG, loginE) == 3){
        q = daQuartoPorCodigoDoSistema(s, codigoQ);
        if(q != NULL){
            g = daGerentePorLoginDoSistema(s, loginG);
            if(g != NULL){
                // printf("\n\nAC --> %s\n\n", loginE);
                e = daEstudantePorLoginDoSistema(s, loginE);
                if(e != NULL){
                    if(strcmp(daLogin(daDadosGerente(daGerenteQuarto(q))), loginG) == 0){
                        if(existeCandidaturaQuartoEstudante(e, q) == 1){
                            apagaCandidaturasDoQuarto(q);
                            apagaCanditadurasDoEstudante(e);
                            apagaTodasCandidaturasDoEstudanteNoSistema(s, q, e);
                         //   apagaTodasCandidaturasDoEstudanteNoSistema(s, q, e);
                            ocuparDesocuparQuarto(q, MSG_OCUPADO);
                            printf("%s", MSG_ACEITAR_CANDIDATURA);
                        }
                        else
                            printf("%s", MSG_CANDIDATURA_INEXISTENTE);
                    }
                    else
                        printf("%s", MSG_OP_NAO_AUTORIZADA);
                }
                else
                    printf("%s", MSG_CANDIDATURA_INEXISTENTE);
            }
            else
                printf("%s", MSG_OP_NAO_AUTORIZADA);
        }
        else
            printf("%s", MSG_QUARTO_INEXISTENTE);
    }
    else
        printf("%s", MSG_COMANDO_INVALIDO);
}

void listagemDeCandidaturaAQuarto(sistema s, char *linha){
    char codigoQ[RESTANTE_DADOS], loginG[RESTANTE_DADOS];
    quarto q;
    gerente g;
    iterador it;
    estudante e;
    if(sscanf(linha, "%s %s", codigoQ, loginG) == 2){
        q = daQuartoPorCodigoDoSistema(s, codigoQ);
        if(q != NULL){
            g = daGerentePorLoginDoSistema(s, loginG);
            if(g != NULL){
                if(strcmp(daLogin(daDadosGerente(daGerenteQuarto(q))), loginG) == 0){
                    if(vaziaSequencia(daCanditadurasDoQuarto(q)) == 0){
                        it = iteradorSequencia(daCanditadurasDoQuarto(q));
                        while(temSeguinteIterador(it)){
                            e = (estudante) seguinteIterador(it);
                            printf("%s, ", daLogin(daDadosEstudante(e)));
                            printf("%s, ", daNome(daDadosEstudante(e)));
                            printf("%s\n", daUniversidade(daDadosEstudante(e)));
                        }
                    }
                    else
                        printf("%s\n", MSG_INEXISTENCIA_CANDIDATURAS);
                }
                else{
                    printf("%s\n", MSG_OP_NAO_AUTORIZADA);
                }
            }
            else
                printf("%s\n", MSG_OP_NAO_AUTORIZADA);
        }
        else
            printf("%s\n", MSG_QUARTO_INEXISTENTE);
    }
    else
        printf("%s\n", MSG_COMANDO_INVALIDO);
}
