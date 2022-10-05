#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ####################### FUNÇÕES AUXILIARES #######################

int numAleatorio(int min, int max){
    srand(time(NULL));
    return (rand() % (max - min + 1)) + min;
}

void erroDados(){
    printf("Erro na introdução de dados.\n");
}

int getInt(){
    int num;
    while(scanf("%d", &num) != 1){
        erroDados();
        getchar();
    }
    return num;
}

int checkRange(int num, int min, int max){
    if(num < min || num > max)
        return 0;
    else
        return 1;
}

//########################## FUNÇÕES DO JOGO ##########################


int tipoJogo(){
    int tipo;
    while(1){
        printf("\nValores por sorteio(1) ou manuais(2): ");
        tipo = getInt();
        if(!checkRange(tipo, 1, 2)){
            erroDados();
            continue;
        }
        return tipo;
    }
}

int numMisterioNivel(int tipo, int nivel, int maximo){
    int misterio;
    if(tipo == 1){
        if(nivel == 1)
            misterio = numAleatorio(1, 100);
        else if(nivel == 2) 
            misterio = numAleatorio(1, 1000);
        else
            misterio = numAleatorio(1, 10000);
    }
    else{
        do{
            printf("Digite o número mistério(1 - %d): ", maximo);
            misterio = getInt();
        }while(!checkRange(misterio, 1, maximo));
    }
    return misterio;
}

int maxPossivel(int nivel){
    if(nivel == 1)return 100;
    else if(nivel == 2) return 1000;
    return 10000;
}

int tentativasJogo(int tipo){
    int tentativa;

    if(tipo == 1) tentativa = numAleatorio(1, 3);
    else{
        do{
            printf("Número de tentativas [1=10, 2=15, 3=20]: ");
            tentativa = getInt();
        }while(!checkRange(tentativa, 1, 3));
    }

    if(tentativa == 1) tentativa = 10;
    else if(tentativa == 2) tentativa = 15;
    else tentativa = 20;
    return tentativa;
}

int nivelJogo(int tipo){
    int nivel;

    if(tipo == 1)
        nivel = numAleatorio(1, 3);
    else{
        printf("\n");
        do{
            printf("Qual o nível(1, 2, 3): ");
            nivel = getInt();
        }while(!checkRange(nivel, 1, 3));
    }
    return nivel;
}

void jogo(){
    int tipo, nivel, numMisterio, tentativas, maximo, user, contTentativa=0;

    printf("/********* JOGO DO SOBE E DESCE **************/\n");

    tipo = tipoJogo();
    nivel = nivelJogo(tipo);
    maximo = maxPossivel(nivel);
    numMisterio = numMisterioNivel(tipo, nivel, maximo);
    tentativas = tentativasJogo(tipo);

    printf("\nEstamos a jogar com o nível %d(1 - %d) e com um máximo de tentativas de %d.\n\n", nivel, maximo, tentativas);

    do{
        printf("Diga um número: ");
        user = getInt();
        contTentativa++;

        if(user > numMisterio)
            printf("O número mistério está abaixo.\n");
        else if(user < numMisterio)
            printf("O número mistério está acima.\n");
        else break;

        tentativas--;
        printf("Ainda tem %d tentativas\n\n", tentativas);
    }while(tentativas > 0);

    if(tentativas == 0){
        printf("Opaaa, Não foi desta, o número mistério era %d\n", numMisterio);
    }
    else
        printf("Parabéns!\nAcertou em %d tentativas\n", contTentativa);
}


// ##################### PRINCIPAL/INÍCIO ############################
int main(){
    char vez;
    do{
        system("clear");
        jogo();
        printf("\n");
        do{
            printf("Quer jogar outra vez (s ou n): ");
            scanf(" %c", &vez);
        }while(vez != 'n' && vez != 's');
    }while(vez != 'n');

    printf("Adeus.\n");
    return 0;
}