#include <stdio.h>

typedef struct{
    int largura;
    int comprimento;
}Superficie;

void lerSuperficie(Superficie *superficie){
    scanf("%d %d", &(superficie->largura), &(superficie->comprimento));
}

int calculaTotalAzulejos(int tamanho, Superficie sup){
    int total_linha = 0;
    int total_coluna = 0;

    total_linha = (int) sup.comprimento / tamanho;
    total_coluna = (int) sup.largura / tamanho;

    return (total_coluna * total_linha);
}

void saidaDados(int total){
    printf("Azulejos inteiros: %d\n", total);
}

int main(){
    int tamanho, total;
    Superficie sup;
    scanf("%d", &tamanho);
    lerSuperficie(&sup);
    total = calculaTotalAzulejos(tamanho, sup);
    saidaDados(total);

    return 0;
}