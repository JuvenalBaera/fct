#include <stdio.h> 
 
int main() { 
    unsigned int ano1, mes1, dia1; 
    unsigned int ano2, mes2, dia2; 
 
    printf("Escreva para a data1 o dia mês ano como inteiros: "); 
    scanf(" %d %d %d", &dia1, &mes1, &ano1); 
    printf("Escreva para a data2 o dia mês ano como inteiros: "); 
    scanf(" %d %d %d", &dia2, &mes2, &ano2); 
 
    if(ano1 < 1000 || ano2 < 1000){
        printf("Ano Introduzido é Inválido\n");
    }
    else if(mes1 > 12 || mes1 <= 0 || mes2 > 12 || mes2 <= 0) {
        printf("Mês Introduzido é inválido\n");
    }
    else if(dia1 > 31 || dia1 <= 0 || dia2 > 31 || dia2 <= 0){
        printf("Introduziu Dia Inválido\n");
    }
    else{
        if(ano1 == ano2){
            if(mes1 == mes2){
                if((dia2 - dia1) == 1){
                    printf("DATA_1 é antiorior a DATA_2\n");
                }
                else{
                    printf("DATA_1 não é anterior a DATA_2\n");
                }
            }
            else{
                if((mes2 - mes1) == 1){
                    if(dia1 == 31 && dia2 == 1){
                        printf("DATA_1 é antiorior a DATA_2\n");
                    }
                }
                else{
                    printf("DATA_1 é antiorior a DATA_2\n");
                }
            }
        }
        else{
            if((ano2 - ano1) == 1){
                if(mes1 == 12 && mes2 == 1){
                    if(dia1 == 31 && dia2 == 1){
                        printf("DATA_1 é antiorior a DATA_2\n");
                    }
                    else{
                        printf("DATA_1 não é anterior a DATA_2\n");
                    }
                }
            }else{
                printf("DATA_1 não é anterior a DATA_2\n");
            }
        }
    }
}