#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define boolean int
#define TRUE 1
#define FALSE 0

#define XSLOTE 10
#define YSLOTE 10
#define PRATELEIRA 5

#define TAM_TAB 4

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
    UM_ARMAZEM slote[PRATELEIRA][XSLOTE][YSLOTE];
    unsigned int tamanho;
}ARMAZEM;

typedef struct{
    int prt, xs, ys;
}COORD_ARMAZEM;

// ######################### UTILITIES FUNCTIONS ########################
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


// ########################## HANDLE STRUCTS ###################

void inicializar_armazem(ARMAZEM *armazem){
    armazem->tamanho = 0;
    for(int i = 0; i < PRATELEIRA ; i++){
        for(int j = 0; j < XSLOTE; j++){
            for(int k = 0; k < YSLOTE ; k++){
                armazem->slote[i][j][k].ocupado = FALSE;
                armazem->slote[i][j][k].lote.id = 0;
            }
        }
    }
}

void inicializar_tabuleiro(LOTE tabuleio[4][4]){
    for(int i = 0; i < TAM_TAB; i++){
        for(int j = 0; j < TAM_TAB; j++){
            tabuleio[i][j].id = 0;
        }
    }
}

boolean existe_id_tabuleiro(LOTE tabuleiro[TAM_TAB][TAM_TAB], int id){
    for(int i = 0; i < TAM_TAB; i++){
        for(int j = 0; j < TAM_TAB; j++){
            if(tabuleiro[i][j].id == id)
                return TRUE;
        }
    }
    return FALSE;
}

boolean existe_id_armazem(ARMAZEM armazem, int id, COORD_ARMAZEM *coord){
    for(int i = 0; i < PRATELEIRA; i++){
        for(int j = 0; j < XSLOTE; j++){
            for(int k = 0; k < YSLOTE; k++){
                if(armazem.slote[i][j][k].lote.id == id){
                    coord->prt = i;
                    coord->xs = j;
                    coord->ys = k;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

void ler_coord_armazem(COORD_ARMAZEM *coord){
    coord->prt = ler_inteiro(0, PRATELEIRA-1, "Digite a prateleira: ");
    coord->xs = ler_inteiro(0, XSLOTE-1, "Digite a posição X: ");
    coord->ys = ler_inteiro(0, YSLOTE-1, "Digite a posição Y: ");
}


// ########################## FUNCTIONALITIES [MENU] ##########################

boolean inserir_lote_armazem(ARMAZEM *armazem, LOTE lote, boolean show_index){
    COORD_ARMAZEM coord = {0,0,0};

    for(int i = 0; i < PRATELEIRA; i++){
        for(int j = 0; j < XSLOTE; j++){
            for(int k = 0; k < YSLOTE; k++){
                if(armazem->slote[i][j][k].ocupado == FALSE){
                    if(lote.id > 0){
                        if(existe_id_armazem(*armazem, lote.id, &coord) == FALSE){
                            armazem->slote[i][j][k].lote = lote;
                            armazem->slote[i][j][k].ocupado = TRUE;
                            if(show_index == TRUE)
                                printf("Slot: %d %d %d\n", j, k, i);
                            armazem->tamanho++;
                            return TRUE;
                        }
                    }
                    else{
                        printf("ID %d Inválido, Não inserido\n", lote.id);
                        return FALSE;
                    }
                }
            }
        }
    }
    return FALSE;
}

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
        for(int i = 0; i < TAM_TAB; i++){
            for(int j = 0; j < TAM_TAB; j++){
                if(!feof(file)){
                    fscanf(file, "%d %s %s %d %d\n", &aux_lote.id, aux_lote.destino, aux_lote.data, &aux_lote.quantidade, &aux_lote.tipo);
                    tabuleiro[i][j] = aux_lote;
                }
            }
        }
        for(int i = 0; i < TAM_TAB; i++){
            for(int j = 0; j < TAM_TAB; j++){
                printf("%2d_%c  ", tabuleiro[i][j].id, (tabuleiro[i][j].tipo==1) ? 'C' : 'L');
            }
            printf("\n");
        }
    }
    else
        erro_abrir_fich(filename);
}

void show_batch_info(ARMAZEM armazem, int id){
    for(int i = 0; i < PRATELEIRA; i++){
        for(int j = 0; j < XSLOTE; j++){
            for(int k = 0; k < YSLOTE; k++){
                if(armazem.slote[i][j][k].lote.id == id){
                    show_one_batch(armazem.slote[i][j][k].lote);
                    printf("Slot %d %d Shelf: %d\n", j, k, i);
                    return;
                }
            }
        }
    }
    printf("Id %d Não existe no armazem\n", id);
}

void show_batches(ARMAZEM armazem){
    printf("\n============= SIZE %d ==================\n", armazem.tamanho);
    for(int i = 0; i < PRATELEIRA; i++){
        for(int j = 0; j < XSLOTE; j++){
            for(int k = 0; k < YSLOTE; k++){
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
            if(armazem.slote[prateleira][i][j].ocupado == TRUE){
                printf(" X ");
            }
            else
                printf(" . ");
        }
        printf("\n");
    }
}

void store_tray(char filename[], LOTE tabuleiro[TAM_TAB][TAM_TAB], ARMAZEM *armazem){
    FILE *file = fopen(filename, "r");
    LOTE aux_lote;
    COORD_ARMAZEM coord = {0, 0, 0};

    if(file){
        for(int i = 0; i < TAM_TAB; i++){
            for(int j = 0; j < TAM_TAB; j++){
                if(!feof(file)){
                    fscanf(file, "%d %s %s %d %d\n", &aux_lote.id, aux_lote.destino, aux_lote.data, 
                                                         &aux_lote.quantidade, &aux_lote.tipo);
                    if(existe_id_tabuleiro(tabuleiro, aux_lote.id) == FALSE){
                        tabuleiro[i][j] = aux_lote;
                        printf("Id: %2d Tray: %d %d -> ", aux_lote.id, i, j);
                        
                        if(existe_id_armazem(*armazem, aux_lote.id, &coord) == FALSE){
                            inserir_lote_armazem(armazem, aux_lote, TRUE);
                        }
                        else
                            printf("\nRepeated ID %d in WAREHOUSE\n", aux_lote.id);
                    }
                    else
                        printf("Repeated product ID: %d Discarding\n", aux_lote.id);
                }
            }
        }
    }
    else
        erro_abrir_fich(filename);
}

void swap_batch_placement(ARMAZEM *armazem, int id){
    LOTE tmp_lote;
    COORD_ARMAZEM a_coord = {0, 0, 0};
    COORD_ARMAZEM n_coord = {0, 0, 0};

    if(existe_id_armazem(*armazem, id, &a_coord) == TRUE){
        ler_coord_armazem(&n_coord);

        if(armazem->slote[n_coord.prt][n_coord.xs][n_coord.ys].ocupado == TRUE){
            tmp_lote = armazem->slote[n_coord.prt][n_coord.xs][n_coord.ys].lote;
            armazem->slote[n_coord.prt][n_coord.xs][n_coord.ys].lote = armazem->slote[a_coord.prt][a_coord.xs][a_coord.ys].lote;
            armazem->slote[a_coord.prt][a_coord.xs][a_coord.ys].lote = tmp_lote;
        }
        else{
            armazem->slote[n_coord.prt][n_coord.xs][n_coord.ys].lote = armazem->slote[a_coord.prt][a_coord.xs][a_coord.ys].lote;
            armazem->slote[n_coord.prt][n_coord.xs][n_coord.ys].ocupado = TRUE;
            armazem->slote[a_coord.prt][a_coord.xs][a_coord.ys].ocupado = FALSE;
        }
    }
    else
        printf("Product with ID: %d does't exist\n", id);
}

int quant_total(ARMAZEM armazem, char n_cid[], int *t_cid, int *t_car, int *t_liv){
    for(int i = 0; i < PRATELEIRA; i++){
        for(int j = 0; j < XSLOTE; j++){
            for(int k = 0; k < YSLOTE; k++){
                if(armazem.slote[i][j][k].ocupado == TRUE){
                    if(strcmp(n_cid, armazem.slote[i][j][k].lote.destino) == 0){
                        *t_cid++;
                        if(armazem.slote[i][j][k].lote.tipo == 1)
                            *t_car++;
                        else
                            *t_liv++;
                    }
                }
            }
        }
    }
}

void est_1(ARMAZEM armazem, char nome[], int t_cid, int t_car, int t_liv){
    char novo_array[100][100];
    int h = 0;
    for(int i = 0; i < PRATELEIRA; i++){
        for(int j = 0; j < XSLOTE; j++){
            for(int k = 0; k < YSLOTE; k++){
                if(armazem.slote[i][j][k].ocupado == TRUE){
                    if(strcmp(nome, armazem.slote[i][j][k].lote.destino) == 0){
                        strcpy(novo_array[h], nome);
                    }
                }
            }
        }
    }
}

void show_statistics(ARMAZEM armazem){
    int total_cidades=0, total_cartao=0, total_livrete=0;
    char nomes[30];

    for(int i = 0; i < PRATELEIRA; i++){
        for(int j = 0; j < XSLOTE; j++){
            for(int k = 0; k < YSLOTE; k++){
                if(armazem.slote[i][j][k].ocupado == TRUE){
                    strcpy(nomes, armazem.slote[i][j][k].lote.destino);
                    
                }
            }
        }
    }
}

void perform_expedition(){}


//########################### HANDLE FILES ########################

void ler_ficheiro_txt(char filename[], ARMAZEM *armazem){
    FILE *file = fopen(filename, "r");
    LOTE aux_lote;

    if(file){
        for(int i = 0; i < PRATELEIRA; i++){
            for(int j = 0; j < XSLOTE; j++){
                for(int k = 0; k < YSLOTE; k++){
                    if(!feof(file)){
                        fscanf(file, "%d %s %s %d %d\n", &aux_lote.id, aux_lote.destino, aux_lote.data, 
                                                         &aux_lote.quantidade, &aux_lote.tipo);
                        inserir_lote_armazem(armazem, aux_lote, FALSE);
                    }
                    else {
                        return;
                    }
                }
            }
        }
        fclose(file);
    }
    else
        erro_abrir_fich(filename);
}

void ler_ficheiro_bin(char filename[], ARMAZEM *armazem){
    FILE *file = fopen(filename, "rb");
    LOTE aux_lote;
    int tot=0;

    if(file){
        while(!feof(file)){
            fread(&aux_lote, sizeof(LOTE), 1, file);
            //show_one_batch(aux_lote);
            //exit(1);
            if(inserir_lote_armazem(armazem, aux_lote, FALSE) == TRUE)
                tot++;
        }
        printf("\nTotaL: %d\n", tot);
        fclose(file);
    }
    else
        erro_abrir_fich(filename);
}

void escrever_fich_bin(char filename[], ARMAZEM armazem){
    FILE *file = fopen(filename, "wb");

    if(file){
        for(int i = 0; i < PRATELEIRA; i++){
            for(int j = 0; j < XSLOTE; j++){
                for(int k = 0; k < YSLOTE; k++){
                    if(armazem.slote[i][j][k].ocupado == TRUE){
                        fwrite(&(armazem.slote[i][j][k].lote), sizeof(LOTE), 1, file);
                    }
                }
            }
        }
        fclose(file);
    }
    else
        erro_abrir_fich(filename);
}

void menu_pricipal(char *opcao){
    printf("\n=============== MENU ===============\n");
    printf("\t1 - Show tray\n");
    printf("\t2 - Show batch info\n");
    printf("\t3 - Show batches\n");
    printf("\t4 - Show warehouse occupancy\n\n");

    printf("\t5 - Store tray\n");
    printf("\t6 - Swap batch placement\n");
    printf("\t7 - Show statitiscs\n\n");

    printf("\t8 - Perform expedition\n");
    printf("\te - exit\n\n");
    *opcao = ler_char("Choose the option: ");
    printf("\n");
}


//####################### MAIN FUNCTION ####################

int main(int argc, char *argv[]){

    LOTE tabuleiro[TAM_TAB][TAM_TAB];
    ARMAZEM armazem;
    char opcao;
    char filename[15];
    char file_bin[] = "warehouse.dat";
    int numero;

    inicializar_armazem(&armazem);
    inicializar_tabuleiro(tabuleiro);

    if(argc > 1){
        ler_ficheiro_txt(argv[1], &armazem);
    }

    //######################################### TO FIX ##########################################################
    ler_ficheiro_bin(file_bin, &armazem);

    do{
        menu_pricipal(&opcao);

        switch(opcao){
            case '1':
                printf("Entry the filename: ");
                ler_texto(filename, 15, 1);
                show_tray(filename, tabuleiro);
            break;
            case '2':
                numero = ler_inteiro(1, 32000, "Digite o ID: ");
                printf("========= PRODUCT =======\n");
                show_batch_info(armazem, numero);
            break;
            case '3': 
                show_batches(armazem);
            break;
            case '4': 
                numero = ler_inteiro(0, PRATELEIRA, "Choose shelf: ");
                show_worehouse(armazem, numero);
            break;
            case '5':
                printf("Entry the filename: ");
                ler_texto(filename, 15, 1);
                store_tray(filename, tabuleiro, &armazem);
            break;
            case '6':
                numero = ler_inteiro(1, 32000, "Digite o ID do produto: ");
                swap_batch_placement(&armazem, numero);
            break;
            case '7':
                show_statistics(armazem);
            break;
            case '8':
                perform_expedition();
            break;
            case 'e': case 'E':
                printf("Good Bye!!!\n");
                break;
            default:
                printf("Inválid Option\n");
        }

    }while(opcao != 'e' && opcao != 'E');

    escrever_fich_bin("test.dat", armazem);

    return 0;
}
