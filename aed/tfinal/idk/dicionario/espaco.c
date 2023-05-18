#include <stdio.h>
#include <stdlib.h>

int main(){
    char cmd[3], login[50], nome[50];
    int idade;
    char localidade[50], universidade[50];

    scanf("%s %s ", cmd, login);
    fgets(nome, 50, stdin);

    scanf("%d ", &idade);
    fgets(localidade, 50, stdin);
    fgets(universidade, 50, stdin);

    printf("\n\n==========================\n");
    printf("%s %s %s", cmd, login, nome);
    printf("%d %s", idade, localidade);
    printf("%s", universidade);
	printf("Hello\n");
    return 0;
}
