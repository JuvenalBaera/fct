#include <stdio.h>
#include <stdlib.h>

int main(){

    int primeiro=1, segundo=3, termo=1, tam=0;

    printf("Sequência até quanto: ");

    if(scanf("%d", &tam) != 1){
        printf("Erro na entrada do dados\n");
        exit(1);
    }
    printf("1, 3, ");
    for(int i = 0; i < tam; i++){
        termo = primeiro + segundo;
        printf("%d, ", termo);
        primeiro = segundo;
        segundo = termo;
    }
    printf("\n");
    return 0;
}