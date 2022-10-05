#include <stdio.h>
#include <stdlib.h>

int main(){
    char opcAtual, opcAnterior = '0', saveAnterior='0';

    do{
        printf(" \n           MENU para broncos\n\n");
        printf("1 - A opção que escolheu foi 1\n");
        printf("2 - Escolheu a segunda opção\n");
        printf("3 - Agora escreveu um três\n");
        printf("4 - A tecla que carregou foi um quatro\n");
        printf("s - Escreveu um 's'\n");
        printf("t - esta foi a opção do 't'\n");
        printf("f - sair\n");

        printf("\nEscolha uma opção: ");
        scanf(" %c", &opcAtual);
        getchar();

        if(opcAtual == '1'){
            printf("1 - A opção que escolheu foi 1\n");
        }
        else if(opcAtual == '2'){
            printf("2 - Escolheu a segunda opção\n");
        }
        else if(opcAtual == '3'){
            printf("3 - Agora escreveu um três\n");
        }
        else if(opcAtual == '4'){
            printf("4 - A tecla que carregou foi um quatro\n");
        }
        else if(opcAtual == 's'){
            printf("s - Escreveu um 's'\n");
        }
        else if(opcAtual == 't'){
            printf("t - esta foi a opção do 't'\n");
        }
        else if(opcAtual == 'f'){
            printf("f - sair\n");
        }
        else{
            printf("Opção inválida\n");
        }

        printf("\nQual foi a opção que escolheu antes desta? ");
        opcAnterior = getchar();

        if(saveAnterior == opcAnterior){
            printf("Muito bem\n");
            saveAnterior = opcAtual;
        }
        else{
            printf("\nFalhou! A opção era %c!!!\n", saveAnterior);
        }
    }while(opcAtual != 'f');
    return 0;
}