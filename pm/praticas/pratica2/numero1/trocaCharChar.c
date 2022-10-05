#include <stdio.h>

int main(){

    char character1 = ' ', character2 = ' ', character3 = ' ';

    printf("Introduza três caracteres: ");
    character1 = getchar();
    getchar();
    character2 = getchar();
    getchar();
    character3 = getchar();

    printf("\nInvertendo a ordem dis caracteres obtemos: ");
    putchar(character3); putchar(' ');
    putchar(character2); putchar(' ');
    putchar(character1);
    putchar('\n');
    //printf("'%c' '%c' '%c'\n", character3, character2, character1);

    return 0;
}