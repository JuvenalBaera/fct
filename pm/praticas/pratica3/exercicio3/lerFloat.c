#include <stdio.h>
#include <stdlib.h>

int main(){
    char k;
    int i=0;
    float num = 0.0;

    printf("Digite número no formato ccc,cc: ");
    while(i < 6){
        scanf("%c", &k);
        if(i != 3 && k == ','){
            printf("Erro no formato dos números\n");
            exit(1);
        }
        else {
            if(((k>='0') && (k<= '9')) || k==','){ // if is digit
                if(i == 0){
                    num += (k-'0') * 100;
                }
                if(i == 1){
                    num += (k-'0') * 10;
                }
                if(i == 2){
                    num += (k-'0');
                }
                if(i == 4){
                    num += ((k-'0') * 0.1);
                }
                if(i == 5){
                    num += ((k-'0') * 0.01);
                }
            }
        }
        i++;
    }
    printf("Número digitado: %.2f e em notação científica: %e\n", num,num);
    printf("Obrigado!\n");

    return 0;
}