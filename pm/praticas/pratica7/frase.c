#include <stdio.h>
#include <string.h>

#define bool int
#define TRUE 1
#define FALSE 0

#define MAX_WORD_LENGTH 21
#define MAX_TEXT_LENGTH 81
#define MAX_WORD 20

//  código aqui

void banco(int *nrConta, int valor){
    printf("Valor antes: %d\n", *nrConta);
    *nrConta += valor;
    printf("Adicionado %d, novo valor: %d\n", valor, *nrConta);
}

int main() {
    int joao, ana, mariana, catarina, pedro, filipa, margarida, jose, jorge, susana, cristina;
    // char **nomes = {"joao", "ana", "mariana", "catarina", "pedro", "filipa", "margarida", "jose", "jorge", "susana", "cristina"};

    joao = 1000;
    ana = 2500;
    mariana = 3000;
    catarina = 1200;
    pedro = 2500;
    filipa = 340;
    margarida = 3400;
    jose = 120;
    jorge = 340;
    susana = 120;
    cristina = 1290;

    int *ptr = &joao;    
    banco(ptr, 100);
    printf("\n");
    ptr = &pedro;
    banco(ptr, 1200);
}