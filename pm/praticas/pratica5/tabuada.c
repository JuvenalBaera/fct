#include <stdio.h>
#include <stdlib.h>

int mult (int a, int b){
    return a*b;
}

int main () {
    int n = 1;

    while(1){
        printf ("Que tabuada quer (1 a 9)? : ");
        if (scanf (" %d", &n) != 1) {
            printf ("Leitura do limite inválida\n");
            exit (1);
        }
        if ((n < 1) || (n > 9)) {
            printf ("Número incorrecto. Tente outra vez\n");
            exit (1);
        }
        printf("\n");
        for(int i = 1; i <= 9; i++){
            printf(" %d x %d = %d\n", n, i, mult(i, n));
        }
        printf("\n");
    }
}