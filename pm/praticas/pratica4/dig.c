#include <stdio.h>
#include <stdlib.h>

int main(){

    int numero, ciclo;
    int centenas;
    int dezenas;
    int unidades;

    while(1){
        printf("Introduza um número com três algarismos: ");
        if(scanf("%d", &numero) != 1){
            printf("Erro na entrada de dados\n");
            exit(1);
        }

        if(numero < 100 || numero > 1000)
            printf("Erro. Não tem três algarismos.\n");
        else{
            centenas = numero / 100;
            dezenas = (numero % 100) / 10;
            unidades = numero % 10;

            for(int i = 0; i < 3; i++){
                if(i == 0){
                    printf("O algarismo das centenas é o ");
                    ciclo = centenas;
                }
                else if(i == 1){
                    printf("O algarismo das dezenas é o ");
                    ciclo = dezenas;
                }
                else{
                    printf("O algarismo das unidades é o ");
                    ciclo = unidades;
                }
                switch(ciclo){
                    case 0: printf("zero"); break;
                    case 1: printf("um"); break;
                    case 2: printf("dois"); break;
                    case 3: printf("três"); break;
                    case 4: printf("quatro"); break;
                    case 5: printf("cinco"); break;
                    case 6: printf("seis"); break;
                    case 7: printf("sete"); break;
                    case 8: printf("oito"); break;
                    case 9: printf("nove"); break;
                }
                printf("\n");
            }
            break;
        }
    }

    return 0;
}