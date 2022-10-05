#include <stdio.h>
#include <stdlib.h>

int main(){
    int i, n = 0, somaImpar=0;

    printf("Introduza o limite de elementos pretendido: ");
    if(scanf(" %d", &n) != 1){
        printf("Leitura do limite inválida\n");
        exit(1);
    }
    for(i = 0; i <= n; i++){
        if(i % 2 == 0){
            printf("%d, ", i);
        }
        else{
            somaImpar += i;
        }
    }
    printf("e soma = %d\n", somaImpar);
}