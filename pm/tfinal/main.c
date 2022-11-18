#include <stdio.h>
#include <stdlib.h>

#define boolean int
#define TRUE 1
#define FALSE 0

#define XSLOTE 10
#define YSLOTE 10
#define PRATELEIRA 5

typedef struct {
    int id;
    char destino[30];
    char data[12];
    int quantidade;
    int tipo;
}LOTE;


typedef struct{
    LOTE lote;
    boolean ocupado;
}UM_ARMAZEM;

typedef struct{
    UM_ARMAZEM slote[XSLOTE][YSLOTE][PRATELEIRA];
    unsigned int tamanho;
}ARMAZEM;

// ######################### FUNÇÕES UTILITÁRIAS ########################
void erro_abrir_fich(char nome[]){
    printf("\nErro ao abrir o ficheiro \"%s\"\n", nome);
}

void limpa_buffer(){
    char ch;
    do{
        ch = getchar();
    }while(ch != '\n');
}

int ver_intervalo(int num, int min, int max){
    return (num >= min) && (num <= max) ? TRUE : FALSE;
}

int ler_inteiro(int min, int max, char *msg){
    int numero, retorno;

    do{
        printf("%s", msg);
        retorno = scanf("%d", &numero);
        limpa_buffer();
        if(retorno != 1)
            continue;
    }while(ver_intervalo(numero, min, max) == FALSE);

    return numero;
}

char ler_char(char *msg){
    char ch;
    printf("%s", msg);
    ch = getchar();
    limpa_buffer();
    return ch;
}

/**
 * Nome......: ler_texto
 * entrada...: char *txt (variável onde o texto vai)
 *             int tam (tamanho a ler)
 *             boolean str_narray (se é string[1] ou array[0])
 * finalidade: Ler um texto [string ou array]
 * retorno...: sem retorno
*/
void ler_texto(char *text, int tam, boolean str_narray){
    char ch;
    int i = 0;

    for(i = 0; i < tam; i++){
        ch = getchar();
        if(ch == '\n')
            break;
        else text[i] = ch;
    }
    if(str_narray == TRUE)  // Em caso de ser string
        text[i] = '\0';
    else
        text[i] = '\n';     // Em caso de ser array
}



// ########################## MAESTRO ##########################

void show_one_batch(LOTE lote){
    printf("ID.........: %d\n", lote.id);
    printf("Destination: %s\n", lote.destino);
    printf("Quantity...: %d\n", lote.quantidade);
    switch(lote.tipo){
        case 1:
            printf("Type.......: Cartão\n");
            break;
        case 2:
            printf("Type.......: Livrete\n");
            break;
    }
    printf("Expire Date: %s\n", lote.data);
}

void show_tray(char filename[], LOTE tabuleiro[4][4]){
    FILE *file = fopen(filename, "r");
    LOTE aux_lote;

    if(file){

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(!feof(file)){
                    fscanf(file, "%d %s %s %d %d\n", &aux_lote.id, aux_lote.destino, aux_lote.data, &aux_lote.quantidade, &aux_lote.tipo);
                    tabuleiro[i][j] = aux_lote;
                }
            }
        }

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                printf("%2d_%c  ", tabuleiro[i][j].id, (tabuleiro[i][j].tipo==1) ? 'C' : 'L');
            }
            printf("\n");
        }
    }
    else
        erro_abrir_fich(filename);
}

void show_batch_info(ARMAZEM armazem, int id){
    for(int i = 0; i < XSLOTE; i++){
        for(int j = 0; j < YSLOTE; j++){
            for(int k = 0; j < PRATELEIRA; k++){
                if(armazem.slote[i][j][k].lote.id == id){
                    show_one_batch(armazem.slote[i][j][k].lote);
                    return;
                }
            }
        }
    }
    printf("Id Não existe no armazem\n");
}

void show_batches(ARMAZEM armazem){
    printf("\n============= SIZE %d ==================\n", armazem.tamanho);
    for(int i = 0; i < XSLOTE; i++){
        for(int j = 0; j < YSLOTE; j++){
            for(int k = 0; j < PRATELEIRA; k++){
                if(armazem.slote[i][j][k].ocupado == TRUE){
                    show_one_batch(armazem.slote[i][j][k].lote);
                    printf("\n");
                }
            }
        }
    }
}

void show_worehouse(ARMAZEM armazem, int prateleira){
    printf("----------- WAREHOUSE -----------\n");
    for(int i = 0; i < YSLOTE; i++){
        printf("  %d", i);
    }
    printf("\n");
    for(int i = 0; i < XSLOTE; i++){
        printf("%d", i);
        for(int j = 0; j < YSLOTE; j++){
            if(armazem.slote[i][j][prateleira].ocupado == TRUE){
                printf(" . ");
            }
            else
                printf(" X ");
        }
        printf("\n");
    }
}

void store_tray(char filename[], ARMAZEM *armazem, int id, int xlote, int ylote, int xslot, int yslot, int prat){}


//########################### FICHEIROS ########################

void ler_ficheiro_txt(char filename[], ARMAZEM *armazem){
    FILE *file = fopen(filename, "r");
    LOTE aux_lote;

    if(file){
        for(int i = 0; i < XSLOTE; i++){
            for(int j = 0; j < YSLOTE; j++){
                for(int k = 0; j < PRATELEIRA; k++){
                    if(!feof(file)){
                        fscanf(file, "%d %s %s %d %d\n", &aux_lote.id, aux_lote.destino, aux_lote.data, 
                                                         &aux_lote.quantidade, &aux_lote.tipo);
                        if(armazem->slote[i][j][k].ocupado == FALSE){
                            armazem->slote[i][j][k].lote = aux_lote;
                            armazem->slote[i][j][k].ocupado = TRUE;
                            armazem->tamanho++;
                        }
                        else
                            printf("Posição Ocupado\n");
                    }
                    else {
                        return;
                    }
                }
            }
        }
    }
    else
        erro_abrir_fich(filename);
}

void ler_ficheiro_bin(char filename[]){
    FILE *file = fopen(filename, "rb");
    LOTE aux_lote;

    if(file){
        printf("Hello ficheiro binário\n");
    }
    else
        erro_abrir_fich(filename);
}

void menu_pricipal(char *opcao){
    printf("\n=============== MENU ===============\n");
    printf("\t1 - Show tray\n");
    printf("\t2 - Show batch info\n");
    printf("\t3 - Show batches\n\n");
    printf("\t4 - Show warehouse occupancy\n");

    printf("\t5 - Store tray\n");
    printf("\t6 - Swap batch placement\n");
    printf("\t7 - Show statitiscs\n");

    printf("\t8 - Perform expedition\n");
    printf("\te - exit\n\n");
    *opcao = ler_char("Choose the option: ");
    printf("\n");
}


void inicializar_armazem(ARMAZEM *armazem){
    armazem->tamanho = 0;
    for(int i = 0; i < XSLOTE; i++){
        for(int j = 0; j < YSLOTE; j++){
            for(int k = 0; k < PRATELEIRA; k++){
                armazem->slote[i][j][k].ocupado = FALSE;
                armazem->slote[i][j][k].lote.id = 0;
            }
        }
    }
}



//####################### MAIN FUNCTION ####################

int main(int argc, char *argv[]){

    LOTE tabuleiro[4][4];
    ARMAZEM armazem;
    char opcao;
    char filename[10];
    int numero;

    inicializar_armazem(&armazem);

    if(argc > 1){
        ler_ficheiro_txt(argv[1], &armazem);
    }

    do{
        menu_pricipal(&opcao);

        switch(opcao){
            case '1':
                printf("Entry the filename: ");
                ler_texto(filename, 10, 1);
                show_tray(filename, tabuleiro);
            break;
            case '2':
                numero = ler_inteiro(1, 32000, "Digite o ID: ");
                show_batch_info(armazem, numero);
            break;
            case '3': 
                show_batches(armazem);
            break;
            case '4': 
                numero = ler_inteiro(0, PRATELEIRA, "Choose shelf: ");
                show_worehouse(armazem, numero);
            break;
            case '5': break;
            case '6': break;
            case '7': break;
            case '8': break;
            case 'e': case 'E':
                printf("Good Bye!!!\n");
                break;
            default:
                printf("Inválid Option\n");
        }

    }while(opcao != 'e' && opcao != 'E');

    return 0;
}
