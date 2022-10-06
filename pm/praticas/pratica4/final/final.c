#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int hora=0, minuto=0, segundo=0;
    int h=0, m=0, s=0, controlo=1;
    long int totSegundo;
    char ch;
    printf("Introduza o tempo no formato h(hora) m(minuto) s(segundo):\n");
    
    while(controlo){
        scanf(" %c", &ch);
        switch(ch){
            case 'h':
                h++;
                if(h > 1){
                    printf("Erro: Campo hora duplicado\n");
                    exit(1);
                }
                scanf("%d", &hora);
                break;
            case 'm':
                scanf("%d", &minuto);
                if(minuto > 59){
                    printf("Erro: número de minutos inválidos\n");
                    exit(1);
                }
                if(m > 1){
                    printf("Erro: Campo minuto duplicado\n");
                    exit(1);
                }
                m++;
                break;
            case 's':
                scanf("%d", &segundo);
                if(segundo > 59){
                    printf("Erro: número de segundos inválidos\n");
                    exit(1);
                }
                if(s > 1){
                    printf("Erro: Campo segundo duplicado\n");
                    exit(1);
                }
                s++;
                break;
            default:
                controlo = 0;
                break;
        }
    }
    totSegundo = (hora * 60 * 60) + (minuto * 60) + segundo;
    printf("Leu %dh %dm %ds = %ld\n", hora, minuto, segundo, totSegundo);

    return 0;
}
