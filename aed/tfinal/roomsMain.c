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
    char linha[MAXL], cmd[TAMANHO_CMD];
    do {
        printf("> ");
        // fgets(linha,MAXL,stdin);
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
            informacaoDoQuarto(s, linha);
        }else if(strcmp(cmd,"MQ")==0){
            modificaEstadoDeQuarto(s, linha);
        }else if(strcmp(cmd,"RQ")==0){
            remocaoDeQuarto(s, linha);
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



// ################## ESTUDANTE ##################
void inserirNovoEstudante(sistema s){
    estudante e;
    char  login[RESTANTE_DADOS], local[TAMANHO_DADOS], uni[TAMANHO_DADOS], nome[TAMANHO_DADOS];
    int idade, lido=0;

    lido += scanf("%s ", login);
    lido += scanf("%50[^\n]", nome);
    lido += scanf("%d ", &idade);
    lido += scanf("%50[^\n] ", local);
    lido += scanf("%50[^\n]", uni);

    if(lido == 5){
        // daNomeCompleto(pnome, apelido, nome);
        e = criaEstudante(login, nome, idade, local, uni);
        if(e != NULL){
            if(existeEstudanteNoSistema(s, e) == 1){
                // printf("Utilizador ja existente\n\n");
                printf("%s\n\n", MSG_UTILIZADOR_EXISTENTE);
                destroiEstudante(e);
            }
            else{
                inserirEstudanteSistema(s, e);
                // printf("Registo de estudante executado\n\n");
                printf("%s\n\n", MSG_REGISTO_ESTUDANTE_OK);
            }
        }
    }
}

void informacaoDoEstudante(sistema s, char *login){
    estudante e = daEstudantePorLoginDoSistema(s, login);
    if(e == NULL){
        // printf("Inexistencia do estudante referido.\n\n");
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
    lido += scanf("%s ", login);
    lido += scanf("%50[^\n] ", nome);
    lido += scanf("%50[^\n]", uni);

    if(lido == 3){
        g = criaGerente(login, nome, uni);
        if(g != NULL){
            if(existeGerenteNoSistema(s, g)==1){
                // printf("utilizador ja existente\n\n");
                printf("%s\n\n", MSG_UTILIZADOR_EXISTENTE);
                destroiGerente(g);
            }
            else{
                inserirGerenteSistema(s, g);
                // printf("Registo de gerente executado\n\n");
                printf("%s\n\n", MSG_REGISTO_GERENTE_OK);
            }

        }
    }
}

void informacaoDoGerente(sistema s, char *login){
    gerente g = daGerentePorLoginDoSistema(s, login);
    if( g == NULL){
        // printf("Inexistencia do gerente referido\n\n");
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
    char uni[TAMANHO_DADOS], localidade[TAMANHO_DADOS], descricao[200];
    int andar;
    int lido = 0;
    lido += scanf("%s ",codigoQuarto);
    lido += scanf("%50[^\n] ",loginGerente);
    lido += scanf("%50[^\n] ",residencia);
    lido += scanf("%50[^\n] ",uni);
    lido += scanf("%50[^\n] ",localidade);
    lido += scanf("%d ", &andar);
    lido += scanf("%200[^\n]",descricao);
    if(lido == 7){
        g = daGerentePorLoginDoSistema(s, loginGerente);
        if( g == NULL){
            // printf("Inexistencia do gerente referido\n\n");
            printf("%s\n\n", MSG_GERENTE_INEXISTENTE);
        }
        else {
            if(existeCodigoDoQuartoNoSistema(s, codigoQuarto)){
            //   printf("Quarto existente\n\n");
              printf("%s\n\n", MSG_QUARTO_EXISTENTE);
            }
            else{
                if(strcmp(daUniversidade(daDadosGerente(g)), uni) == 0){
                    q = criaQuarto(codigoQuarto, g, uni, residencia, localidade, andar, descricao);
                    if(q != NULL){
                        inserirQuartoSistema(s, q);
                        // printf("Registo de quarto executado\n\n");
                        printf("%s\n\n", MSG_REGISTO_QUARTO_OK);
                    }
                }
                else{
                    // printf("Operacao nao autorizada\n\n");
                    printf("%s\n\n", MSG_OP_NAO_AUTORIZADA);
                }
            }
        }
    }   
    
}

void informacaoDoQuarto(sistema s, char *linha){
    char cmd[TAMANHO_CMD], codigo[RESTANTE_DADOS];
    quarto q;
    if(sscanf(linha, "%s %s\n", cmd, codigo) == 2){
        q = daQuartoPorCodigoDoSistema(s, codigo);
        if(q == NULL){
            // printf("Inexistencia do quarto referido\n\n");
            printf("%s\n\n", MSG_INEXISTENCIA_QUARTOS);
        }
        else{
            printf("%s, %s\n%s\n%s\n%d\n%s\n%s\n\n", daCodigoQuarto(q), daResidenciaQuarto(q),
                                               daUniversidadeQuarto(q), daLocalidadeQuarto(q),
                                               daAndarQuarto(q), daDescricaoQuarto(q),daOcupadoQuarto(q));
        }
    }
}

void modificaEstadoDeQuarto(sistema s, char *linha){
    char cmd[TAMANHO_CMD], codigo[RESTANTE_DADOS], loginGerente[RESTANTE_DADOS], estado[RESTANTE_DADOS];
    quarto q;
    gerente g;
    if(sscanf(linha, "%s %s %s %s\n", cmd, codigo, loginGerente, estado)==4){
        q =daQuartoPorCodigoDoSistema(s, codigo);
        if(q == NULL){
            // printf("Inexistencia do quarto referido\n\n");
            printf("%s\n\n", MSG_INEXISTENCIA_QUARTOS);
        }
        else{
            g=daGerentePorLoginDoSistema(s,loginGerente);
            if(g == NULL){
                // printf("Inexistencia do gerente referido\n\n");
                printf("%s\n\n", MSG_GERENTE_INEXISTENTE);
            }
            else{
                if(strcmp(daLogin(daDadosGerente(daGerenteQuarto(q))), loginGerente) == 0){
                    if(strcmp(estado, "ocupado") == 0){
                        if(vazioDicionario(daCanditadurasDoQuarto(q)) == 1){
                            ocuparDesocuparQuarto(q, estado);
                            // printf("Estado de quarto atualizado\n\n");
                            printf("%s\n\n", MSG_QUARTO_ATUALIZADO);
                        }
                        else{
                            printf("%s\n\n", MSG_CANDIDATURAS_ACTIVAS);
                            // printf("Candidaturas activas\n\n");
                        }
                    }
                    else{
                        ocuparDesocuparQuarto(q, estado);
                        // printf("Estado de quarto atualizado\n\n");
                        printf("%s\n\n", MSG_QUARTO_ATUALIZADO);
                    }
                }
                else{
                    // printf("Operacao nao autorizada\n\n");
                    printf("%s\n\n", MSG_OP_NAO_AUTORIZADA);
                }
            }
        }
    }
}

void remocaoDeQuarto(sistema s, char *linha){
    char cmd[TAMANHO_CMD], codigo[RESTANTE_DADOS], loginGerente[RESTANTE_DADOS];
    quarto q;
    gerente g;
    if(sscanf(linha, "%s %s %s\n", cmd, codigo, loginGerente) == 3){
        q = daQuartoPorCodigoDoSistema(s, codigo);
        if(q == NULL){
            // printf("Inexistencia do quarto referido\n\n");
            printf("%s\n\n", MSG_INEXISTENCIA_QUARTOS);
        }
        else{
            g = daGerentePorLoginDoSistema(s, loginGerente);
            if(g == NULL){
                // printf("Inexistencia do gerente referido\n\n");
                printf("%s\n\n", MSG_GERENTE_INEXISTENTE);
            }
             else{
                if(strcmp(daLogin(daDadosGerente(daGerenteQuarto(q))), loginGerente) == 0){
                    if(vazioDicionario(daCanditadurasDoQuarto(q)) == 1){
                        if(remocaoDoQuartoNoSistema(s, q) == 1){
                            // printf("Remocao de quarto executada\n\n");
                            printf("%s\n\n", MSG_REMOCAO_QUARTO_OK);
                        }
                    }
                    else{
                        // printf("Candidaturas activas\n\n");
                        printf("%s\n\n", MSG_CANDIDATURAS_ACTIVAS);
                    }
                }
                else{
                    // printf("Operacao nao autorizada\n\n");
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
