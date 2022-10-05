#include <stdio.h>

int main(){
    
    //VARIÁVEIS NECESSÁRIAS
    short int dias1=0, horas1=0, minutos1=0, segundos1=0;
    short int dias2=0, horas2=0, minutos2=0, segundos2=0;

    long int total_segundos1 = 0, total_segundos2 = 0;
    long int diff_segundos = 0;

    short int s_dias=0, s_horas=0, s_minutos=0, s_segundos=0;

    printf("Introduza o tempo no.1 (dia)d (hora)h (minuto)m (segundo)s:\n");
    scanf("%hdd %hdh %hdm %hds", &dias1, &horas1, &minutos1, &segundos1);
    printf("Introduza o tempo no.2 (dia)d (hora)h (minuto)m (segundo)s:\n");
    scanf("%hdd %hdh %hdm %hds", &dias2, &horas2, &minutos2, &segundos2);

    total_segundos1 = dias1 * 24 * 60 * 60 + horas1 * 60 * 60 + minutos1 * 60 + segundos1;
    total_segundos2 = dias2 * 24 * 60 * 60 + horas2 * 60 * 60 + minutos2 * 60 + segundos2;

    diff_segundos = total_segundos2 - total_segundos1;

    s_dias = diff_segundos / 60 / 60 / 24;
    s_horas = diff_segundos / 60 / 60 % 24;
    s_minutos = diff_segundos / 60 % 60;
    s_segundos = diff_segundos % 60 % 60;

    printf("A diferença entre os dois tempos é de %ld segundos = %hdd %hdh %hdm %hds\n", diff_segundos, s_dias, s_horas,s_minutos, s_segundos);

    return 0;
}