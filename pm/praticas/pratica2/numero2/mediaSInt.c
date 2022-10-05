#include <stdio.h>

int main(){
    const int NUMERO = 3;

    short int val1 =0, val2 = 0, val3 = 0;
    short int total;
    short int media;

    printf("Introduza os três valores: ");
    scanf("%hd %hd %hd", &val1, &val2, &val3);

    total = val1 + val2 + val3;
    media = total / NUMERO;

    printf("\nA soma dos valores é %hd e a média é %hd\n", total, media);
    return 0;
}