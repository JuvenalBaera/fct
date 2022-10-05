#include <stdio.h>
#include <stdlib.h>

int main(){

    int hora=0, minuto=0, segundo=0, num=0, controlo=1;
    int ch=0, cm=0, cs=0;
    long int totalSegundos = 0;
    char tipo=' ';

    printf("Introduza o tempo no formato h(horas) m(minutos) s(segundos):\n");
    
    while(controlo<=3){
        scanf("%c%d", &tipo, &num);

        if(ch > 1){
            printf("Erro: número de horas repetidos\n");
            exit(1);
        }
        if(cm > 1){
            printf("Erro: número de minutos repetidos\n");
            exit(1);
        }
        if(cs > 1){
            printf("Erro: número de segundos repetidos\n");
            exit(1);
        }
        switch(tipo){
            case 'h':
                hora = num;
                ch++;
                break;
            case 'm':
                if(num > 59){
                    printf("Erro: número de minutos inválidos\n");
                    exit(1);
                }
                minuto = num;
                cm++;
                break;
            case 's':
                if(num > 59){
                    printf("Erro: número de segundos inválidos\n");
                    exit(1);
                }
                segundo = num;
                cs++;
                break;
            default:
                break;
        }
        if(!(tipo != 'h' || tipo != 'm' || tipo != 's')){
            break;
        }
        controlo++;
        //getchar();
    }
    totalSegundos = hora * 60 * 60 + minuto * 60 + segundo;
    printf("Leu: %dh %dm %ds = %ld segundos\n", hora, minuto, segundo, totalSegundos);
    return 0;
}