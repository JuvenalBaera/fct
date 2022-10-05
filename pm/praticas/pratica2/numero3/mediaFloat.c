#include <stdio.h>

int main(){
    const int NUMERO = 3;

    float val1 = 0, val2 = 0, val3 = 0;
    float total;
    float media;

    printf("Introduza os três valores: ");
    scanf("%f %f %f", &val1, &val2, &val3);

    total = val1 + val2 + val3;
    media = total / NUMERO;

    printf("A soma dos valores é %f e a média vale %f\n", total, media);
    return 0;
}