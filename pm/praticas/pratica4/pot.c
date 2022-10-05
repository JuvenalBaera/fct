#include <stdio.h>
#include <stdlib.h>

int main(){
    int i, n = 0;

    printf("Introduza o limite de elementos pretendido: ");
    if(scanf(" %d", &n) != 1){
        printf("Leitura do limite inválida\n");
        exit(1);
    }
    for(i = 1; i <= n; i++){
        printf("%d %d\n", i, i * i);
    }
}