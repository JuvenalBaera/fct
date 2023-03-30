#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* TADs usados */

#include "ticket.h"
#include "parque.h"

#define MAXL 25
/* protótipos das funções usadas no main */

void interpretador(parque t);
void cmdEntradaCarro(parque p, char * linha);
void cmdSaidaCarro(parque p,char * linha);
void cmdListaCarros(parque p);
void cmdDinheiro(parque p);
/*
e <matricula> <hh:mm> -> entrada dum carro no estacionamento.
s <matricula> <hh:mm> -> saída dum carro no estacionamento, e apresentação do valor a pagar.
l -> listagem de todos os carros que entraram no estacionamento e ainda não saíram. Os carros devem aparecer pela ordem de registo de entrada.
c -> consulta do dinheiro em caixa no estacionamento.
x -> saida da aplicação, e apresentação do valor em caixa e do número de carros no estacionamento.
*/

int main(void){
	parque fctParque = criaParque();
	interpretador(fctParque);
	destroiParqueETickets(fctParque);
	return 0;
}

void interpretador(parque p){
	char linha[MAXL], cmd;

	do {
		fgets(linha,MAXL,stdin);
		cmd = toupper(linha[0]);
		/* Tratar comando */
		switch (cmd){
			case 'E': cmdEntradaCarro(p,linha);break;
			case 'S': cmdSaidaCarro(p,linha); break;
			case 'C': cmdDinheiro(p);break;
			case 'L': cmdListaCarros(p);break;
			case 'X': break;
			default: printf("Comando invalido.\n");break;
		}
        // printf("\n");
	}while (cmd!='X');
	
	cmdDinheiro(p);
	printf("%d carros no parque.\n", daLotacaoParque(p));
}

void cmdDinheiro(parque p){
	printf("Dinheiro em caixa : %.2f euros.\n", daCaixaParque(p));
}

void cmdEntradaCarro(parque p, char * linha){
	char c, mat[MAXMAT];
	int h,m;
	if (sscanf(linha,"%c %s %d:%d",&c,mat,&h,&m) != 4)
		printf("Dados invalidos.\n");
	else
		if (entradaCarroParque(p,mat,h,m) != 1)
			printf("Carro ja no parque.\n");
		else
			printf("Entrada autorizada.\n");
}

void cmdSaidaCarro(parque p,char * linha){
	//completar
	char c, mat[MAXMAT];
	int h,m, pos;
    float preco;
    ticket carroTirado;

	if (sscanf(linha,"%c %s %d:%d",&c,mat,&h,&m) != 4)
		printf("Dados invalidos.\n");
    else{
        pos = posCarro(p, mat);
        if(pos == -1)
            printf("Carro nao existe no parque.\n");
        else{
            preco = daPrecoParque(p, mat, h, m);
            printf("Carro com matricula %s deve pagar %.2f euros.\n", pegaMatriculaParque(p, pos), preco);
			tiraCarroParque(p, pos);
        }
    }
}

void cmdListaCarros(parque p){
	int i = 0;
	int cont = daLotacaoParque(p);
	ticket t;
	if (cont == 0)
		printf("Parque sem carros.\n");
    
	for (; i < cont; i++){
        printf("Matricula: %s\n", pegaMatriculaParque(p, i));
	}
}
