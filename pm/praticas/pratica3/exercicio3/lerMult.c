#include <stdio.h>

int main(){
    const int NUMERO = 3;

    int val1 =0, val2 = 0, val3 = 0;
    int total;
    int media;
    int result=0;

    printf("Introduza os três valores: ");
    result = scanf(" %d %d %d", &val1, &val2, &val3);

    printf("Fora: Result = %d\n", result);

    while(result != 3){
        printf("Erro na leitura dos dados.\n");
        printf("Por favor, escreva novamente os valores\n");
        result = scanf(" %d %d %d", &val1, &val2, &val3);
        printf("Dento: Result = %d\n", result);
    }

    total = val1 + val2 + val3;
    media = total / NUMERO;

    printf("\nA soma dos valores é %d e a média é %d\n", total, media);
    return 0;
}