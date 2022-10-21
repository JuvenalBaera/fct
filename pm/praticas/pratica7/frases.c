#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define TRUE 1
#define FALSE 0

#define MAX_WORD_LENGTH 21
#define MAX_TEXT_LENGTH 81
#define MAX_WORD 20

void limpa_buffer(){
    char ch;
    do{
        ch = getchar();
    }while(ch != '\n');
}

void readInt(int *num, char msg[]){
    int ret = 0;
    do{
        printf("%s", msg);
        ret = scanf("%d", num);
        limpa_buffer();
    }while(ret == 0);
}

void escolha(int *num_frase, int *num_palavra){
    printf("\n");
    do{
        readInt(num_frase, "Digite o nr de frase (-1 = sair): ");
    }while(*num_frase < -1 || *num_frase > MAX_WORD);

    if(*num_frase == -1)
        exit(1);

    do{
        readInt(num_palavra, "Digite o nr de palavras (-1 = sair): ");
    }while(*num_palavra < -1 || *num_palavra > MAX_WORD);

    if(*num_palavra == -1)
        exit(1);

    printf("\n");
}

void ver_se_contem (char *frase, char *palavra){
    printf("Frase..: "); puts(frase);
    printf("Palavra: "); puts(palavra);

    if(strstr(frase, palavra))
        printf("SIM EXISTE\n");
    else
        printf("NAO EXISTE\n");
}

int main() {
        
    char frase1   [MAX_TEXT_LENGTH] = "A string that contains a dog and a cat";
    char frase2   [MAX_TEXT_LENGTH] = "A string that contains camel and mouse";
    char frase3   [MAX_TEXT_LENGTH] = "The dog was eating with the horse";
    char frase4   [MAX_TEXT_LENGTH] = "The camel drunk all the water";
    char frase5   [MAX_TEXT_LENGTH] = "The mouse entered into the pipe";
    char frase6   [MAX_TEXT_LENGTH] = "Uma string que pode conter dog ou camel";
    char frase7   [MAX_TEXT_LENGTH] = "The horse is bigger than the dog";

    char palavra1 [MAX_WORD_LENGTH] = "dog";
    char palavra2 [MAX_WORD_LENGTH] = "horse";
    char palavra3 [MAX_WORD_LENGTH] = "cat";
    char palavra4 [MAX_WORD_LENGTH] = "mouse";
    char palavra5 [MAX_WORD_LENGTH] = "camel";
    char palavra6 [MAX_WORD_LENGTH] = "pig";
    char palavra7 [MAX_WORD_LENGTH] = "bigger";

    char *frase_ptr [MAX_WORD];                 // para apontar a frases
    char *pal_ptr [MAX_WORD];                   // para apontar a palavras
    char ** frase, ** palavra;
    int num_frase=0, num_palavra=0;             // para conter a escolha do util.

    frase_ptr [0] = frase1;
    frase_ptr [1] = frase2;
    frase_ptr [2] = frase3;
    frase_ptr [3] = frase4;
    frase_ptr [4] = frase5;
    frase_ptr [5] = frase6;
    frase_ptr [6] = frase7;

    pal_ptr   [0] = palavra1;
    pal_ptr   [1] = palavra2;
    pal_ptr   [2] = palavra3;
    pal_ptr   [3] = palavra4;
    pal_ptr   [4] = palavra5;
    pal_ptr   [5] = palavra6;
    pal_ptr   [6] = palavra7;

    frase = frase_ptr;
    palavra = pal_ptr;

    while (1) {
        escolha (&num_frase, &num_palavra);
        ver_se_contem (*(frase + num_frase), *(palavra + num_palavra));
    }
    return 0;
}