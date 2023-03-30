#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAMTEXTO 100

void lerDados(char *texto, int *codigo);
void cifrarTexto(char *texto, char *cifrado, int codigo);

int main(){

    int codigo;
    char texto[TAMTEXTO];
    char cifrado[TAMTEXTO];

    lerDados(texto, &codigo);
    cifrarTexto(texto, cifrado, codigo);
    printf("Texto cifrado: %s\n", cifrado);
    return 0;
}

void clearBuffer(){
    char ch;
    do{
        ch = getchar();
    }while(ch != '\n');
}

void lerDados(char *texto, int *codigo){
    printf("Codigo: ");
    scanf("%d", codigo);
    clearBuffer();
    printf("Texto: ");
    fgets(texto, TAMTEXTO, stdin);
}

void cifrarTexto(char *texto, char *cifrado, int codigo){
    char aux;
    for(int i = 0; i < strlen(texto); i++){
        aux = texto[i];
        if(islower(aux)){
            cifrado[i] = aux + codigo;
        }
        else
            cifrado[i] = aux;
    }
}