#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAMTEXTO 100

void lerDados(char *texto, int *codigo, int *linhas);
void cifrarTexto(char *texto, char *cifrado, int codigo);

int main(){

    int codigo, linhas;
    char texto[TAMTEXTO];
    char cifrado[TAMTEXTO];

    lerDados(texto, &codigo, &linhas);
    cifrarTexto(texto, cifrado, codigo);
    printf("Texto cifrado: %s", cifrado);
    return 0;
}

void clearBuffer(){
    char ch;
    do{
        ch = getchar();
    }while(ch != '\n');
}

void lerDados(char *texto, int *codigo, int *linhas){
    int end = 0;
    char aux[TAMTEXTO];
    texto[0] = '\0';
    printf("Codigo: ");
    scanf("%d", codigo);
    printf("Linhas: ");
    scanf("%d", linhas);
    clearBuffer();
    printf("Texto:\n");

    for(int i = 0; i < *linhas; i++){
        fgets(aux, TAMTEXTO, stdin);
        aux[strlen(aux)-1] = '\0';
        texto = strcat(texto, aux);
    }
}

void cifrarTexto(char *texto, char *cifrado, int codigo){
    int i = 0;

    // codigo %= 26;
    // codigo++;
    // printf("Codigo: %d\n", codigo);
    for(; i < strlen(texto); i++){
        if(isalpha(texto[i]) && islower(texto[i])){
            cifrado[i] = ((texto[i] - 'a' + codigo) % 26) + 'a';
        }
        else{
            cifrado[i] = texto[i];
        }
    }
    cifrado[i] = '\0'; 
}



/*
void cifrarTexto(char *texto, char *cifrado, int codigo){

    char aux;
    int i=0;

    codigo %= 27;
    codigo++;

    printf("Codigo: %d\n", codigo);

    for(; i < strlen(texto); i++){
        aux = texto[i];
        if(islower(aux)){
            if((aux + codigo) > 'z'){
                cifrado[i] = 'a' + ((aux + codigo - 'z') -1);
            }
            else cifrado[i] = aux + codigo;
        }
        else
            cifrado[i] = aux;
    }
    cifrado[i] = '\0';
}
*/