#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXL 50

/* protótipos das funções usadas no main */
void inserirNovoEstudante();
void informacaoDoEstudante();
void inserirNovoGerente();
void informacaoDoGerente();
void inserirNovoQuarto();
void informacaoDoQuarto();
void modificaEstadoDeQuarto();
void remocaoDeQuarto();
void inserirCandidaturaDeEstudanteQuarto();
void aceitacaoDeCandidatura();
void listagemDeCandidaturaAQuarto();


int main(){
    
}



void interpretador(/*sistema s*/){
    char linha[MAXL], cmd[2];

    do {
        fgets(linha,MAXL,stdin);
        cmd[0] = toupper(linha[0]);
        cmd[1] = toupper(linha[1]);
        if (strcmp(cmd,"IE")==0){

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