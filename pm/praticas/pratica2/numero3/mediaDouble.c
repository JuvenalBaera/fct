#include <stdio.h>

int main(){
    const int NUMERO = 3;

    double val1 = 0, val2 = 0, val3 = 0;
    double total;
    double media;

    printf("Introduza os três valores: ");
    scanf("%lf %lf %lf", &val1, &val2, &val3);

    total = val1 + val2 + val3;
    media = total / NUMERO;

    printf("A soma dos valores é %lf e a média vale %lf\n", total, media);
    return 0;
}