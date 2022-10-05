#include <stdio.h> 
 
int main() { 
 
    unsigned int nota_teorica= 0, nota_pratica= 0, faltas= 0;
    float media;
    unsigned int nota_final;
 
    printf("Cálculo da nota final a PM\n\n"); 
    printf("Introduza os seguintes dados:\n"); 
    printf("\tNúmero de faltas nos trabalhos práticos: "); 
    scanf("%d", &faltas); 
    printf("\tNota dos trabalhos práticos: "); 
    scanf(" %d", &nota_pratica); 
    printf("\tNota dos testes e exames: "); 
    scanf(" %d", &nota_teorica);

    if (faltas > 3) { 
        printf("Reprovou à disciplina por faltas\n"); 
    } else {
        media= 0.5*nota_pratica + 0.5*nota_teorica; 

        if(faltas == 2){
            printf("Máxima nota é de 14 valores\n");
            if(media > 14){
                media = 14.0;
            }
        }
        else{
            if(faltas == 3){
                printf("Máxima nota é de 12 valores\n");
                if(media > 12){
                    media = 12.0;
                }
            }
        }
        nota_final= (int)(media+0.5); 
        printf("Aprovado com a nota final de %d valores (%.1f)\n", nota_final, media);
    } 
}