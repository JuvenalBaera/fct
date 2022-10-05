#include <stdio.h>

int main(){
    const int NUMERO = 3;

    unsigned long int val1 = 0, val2 = 0, val3 = 0;
    unsigned long int total;
    float media;

    printf("Introduza os três valores: ");
    scanf("%ld %ld %ld", &val1, &val2, &val3);

    total = val1 + val2 + val3;
    media = (float) total / NUMERO;

    printf("\nO valor médio de \"%ld+%ld+%ld\" é \"%f ou %ld %ld/%d\"\n", val1, val2, val3, media, (long) media, total%NUMERO, NUMERO);
    return 0;
}