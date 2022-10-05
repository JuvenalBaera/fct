#include <stdio.h>

int main(){

    char character1 = ' ', character2 = ' ', character3 = ' ';

    printf("Introduza três caracteres: ");
    scanf("%c", &character1);
    scanf(" %c", &character2);
    scanf(" %c", &character3);

    printf("\nInvertendo a ordem dis caracteres obtemos: ");
    printf("'%c' '%c' '%c'\n", character3, character2, character1);

    return 0;
}