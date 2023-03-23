#include <stdio.h>

typedef struct{
    int dia, mes, ano;
}Data;

void lerData(Data *data){
    printf("Introduza uma data (ano, mes, dia):\n");
    scanf("%d%d%d", &(data->ano), &(data->mes), &(data->dia));
}

int verificaBisexto(int ano){
    if((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0))
        return 1;
    return 0;
}

int calcTotalDias(Data data){
    int dias = data.dia;
    for(int i = 1; i < data.mes; i++){
        switch(i){
            case 1: case 3: case 5: case 7: 
            case 8: case 10: case 12: 
                dias += 31; break;
            case 2:
                if(verificaBisexto(data.ano)) dias += 29;
                else dias += 28;
            break;
            case 4: case 6: case 9: case 11: 
            dias += 30; break;
        }
    }
    return dias;
}


int main(){
    Data data;
    lerData(&data);
    printf("%d\n", calcTotalDias(data));
    return 0;
}