#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define boolean int
#define TRUE 1
#define FALSE 0

#define XSLOTE 10       // número da posição x do armazém
#define YSLOTE 10       // número da posicão y do armazém
#define PRATELEIRA 5    // número de prateleira do armazém

#define TAM_TAB 4       // Tamanho do tabuleiro


/***
 * Descriao: estructura com lote
*/
typedef struct {
    int id;
    char destino[30];
    char data[12];
    int quantidade;
    int tipo;
}LOTE;


/***
 * Descriao: Estrutura com um Lote e inteiro que diz se está ocupado ou não
*/
typedef struct{
    LOTE lote;
    boolean ocupado;
}SLOTE;

/***
 * Descriao: estructura com slote [5][10][10] e tamanho que diz diz total de lotes dentro do armazém
*/
typedef struct{
    SLOTE slote[PRATELEIRA][XSLOTE][YSLOTE];
    unsigned int tamanho;
}ARMAZEM;


/***
 * Descriao: Estrutura com coordenadas do armazém
 *         : prt - Prateleira
 *         : xs  - Posição x da armazém
 *         : ys  - Posição y do armazém
*/
typedef struct{
    int prt, xs, ys;
}COORD_ARMAZEM;

// ######################### UTILITIES FUNCTIONS ########################
/***
 * Descriao: Escreve mensagem em caso de ter um erro ao abrir um arquivo
 * Input: None
 * Output: None
*/
void erro_abrir_fich(char nome[]){
    printf("\nErro ao abrir o ficheiro \"%s\"\n", nome);
}


/***
 * Descriao: Procedimento que limpa o buffer até achar ENTER (\n)
 * Input: None
 * Output: None
*/
void limpa_buffer(){
    char ch;
    do{
        ch = getchar();
    }while(ch != '\n');
}


/***
 * Descriao: Função que verifica intervalo de um determinado número
 * Input:   num - Número a ser verificado o intervalo
 *          min - ||     mínimo do intervalo
 *          max - ||     máximo do  ||
 * Output: Verdade(1) em caso do número(num) estar dentro de um intervalo (min) e (max),
 *          caso contrario retorna Falso(0)
*/
int ver_intervalo(int num, int min, int max){
    return (num >= min) && (num <= max) ? TRUE : FALSE;
}

void print_char(int tam, char ch){
    for(int i = 0; i < tam; i++)
        putchar(ch);
    putchar('\n');
}

/***
 * Descriao:  Função que lê um número inteiro dentro de um intervalo 
 * Input:   min - Nr mínimo a ser lido
 *          max - Nr máximo a ser lido
 *          msg - Mensagem a ser mostardo 
 * Output: Um inteiro com o número lido
*/
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


/***
 * Descriao: Função para ler um caractere
 * Input: msg - Mensagem a mostrar
 * Output: caractere lido
*/
char ler_char(char *msg){
    char ch;
    printf("%s", msg);
    ch = getchar();
    limpa_buffer();
    return ch;
}


/***
 * Descriao: Lê um texto até achar ENTER ou até um máximo número
 * Input:   txt - Variável para guardar o texto
 *          tam - Nr máximo a ser lido
 *          str_narray - se True lê string ou coloca (\0) no fim
 *                       se False lê array ou não coloca (\0) no fim
 * Output: None
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


// ########################## HANDLE STRUCTS ###################

/***
 * Descriao: Inicializa o armazém (estar todas as posições desocupadas e ID de cada LOTE ser 0 [flag])
 * Input: endereço de um armazém
 * Output: None
*/
void inicializar_armazem(ARMAZEM *armazem){
    armazem->tamanho = 0;
    for(int i = 0; i < PRATELEIRA ; i++){                   // Percorre as prateieras do armazém
        for(int j = 0; j < XSLOTE; j++){                    //    ||    posição X do SLOTE dentro do armazém
            for(int k = 0; k < YSLOTE ; k++){               //    ||       ||   Y      ||
                armazem->slote[i][j][k].ocupado = FALSE;
                armazem->slote[i][j][k].lote.id = 0;
            }
        }
    }
}


/***
 * Descriao: recebe um tabuleiro (uma matriz de lote [4x4])
 *           coloca todos os id a 0 [flag] para dizer que está vazio
 * Input: matriz de LOTE 4x4 [tabuleiro]
 * Output: None
*/
void inicializar_tabuleiro(LOTE tabuleio[4][4]){
    for(int i = 0; i < TAM_TAB; i++){
        for(int j = 0; j < TAM_TAB; j++){
            tabuleio[i][j].id = 0;
        }
    }
}


/***
 * Descriao: Verifica se um determinado ID existe no Tabuleiro
 * Input: tabuleiro[4][4] - Tabuleiro na qual queremos verificar o ID
 *        id - O id a ser verificado
 * Output: TRUE (1) se existir ou FALSE(0) caso não exista
*/
boolean existe_id_tabuleiro(LOTE tabuleiro[TAM_TAB][TAM_TAB], int id){
    for(int i = 0; i < TAM_TAB; i++){
        for(int j = 0; j < TAM_TAB; j++){
            if(tabuleiro[i][j].id == id)
                return TRUE;
        }
    }
    return FALSE;
}


/***
 * Descriao: Verifica se um determinado ID existe no Armazém
 * Input:   armazem - armazém na qual queremos verificar o ID
 *          id - O id a ser verificado
 *          Endereço de uma struct COOOD (coordenada) para dizer onde o id está localizado em caso de existir
 *          se não existir, as coordenadas são configuradas para -1
 * Output: TRUE (1) em casa de exitir ou FALSE (0) caso não exista
*/
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
    coord->prt = -1;
    coord->xs = -1;
    coord->ys = -1;
    return FALSE;
}


/***
 * Descriao: lê as coordenadas de um armazém
 * Input: endereço da struct COORD_ARMAZEM
 * Output: None
*/
void ler_coord_armazem(COORD_ARMAZEM *coord){
    coord->prt = ler_inteiro(0, PRATELEIRA-1, "Digite a prateleira [0 - 4]: ");
    coord->xs = ler_inteiro(0, XSLOTE-1, "Digite a posição X [0 - 9]: ");
    coord->ys = ler_inteiro(0, YSLOTE-1, "Digite a posição Y [0 - 9]: ");
}


/***
 * Descriao: Função para mostrar as informações de um Lote
 * Input: lote - Lote para mostrar
 * Output: None
*/
void show_one_batch(LOTE lote){
    printf("\tID.........: %d\n", lote.id);
    printf("\tDestination: %s\n", lote.destino);
    printf("\tQuantity...: %d\n", lote.quantidade);
    switch(lote.tipo){
        case 1:
            printf("\tType.......: Cartão\n");
            break;
        case 2:
            printf("\tType.......: Livrete\n");
            break;
    }
    printf("\tExpire Date: %s\n", lote.data);
}


// ########################## FUNCTIONALITIES [MENU] ##########################
/***
 * Descriao: Insere um Lote no armazém numa posição vaga [id > 0]
 * Input:   *armazem - Armazém para qual será inserido o lote
 *          lote - Lote a ser inserido no armazém
 *          show_index -  se TRUE(1) mostra onde o lote foi inserido
 *                        se FALSE(0) não mostra
 * Output:  True em caso de ser inserido ou ID do lote passado não existe e é válido
 *          False caso contrário
*/
boolean inserir_lote_armazem(ARMAZEM *armazem, LOTE lote, boolean show_index){
    COORD_ARMAZEM coord = {-1, -1, -1};

    for(int i = 0; i < PRATELEIRA; i++){
        for(int j = 0; j < XSLOTE; j++){
            for(int k = 0; k < YSLOTE; k++){
                if(armazem->slote[i][j][k].ocupado == FALSE){
                    if(lote.id > 0){
                        if(existe_id_armazem(*armazem, lote.id, &coord) == FALSE){
                            armazem->slote[i][j][k].lote = lote;
                            armazem->slote[i][j][k].ocupado = TRUE;
                            if(show_index == TRUE)
                                printf(" -> Slot: %d %d %d\n", j, k, i);
                            armazem->tamanho++;
                            return TRUE;
                        }
                        else{
                            printf("ID %d já existe\n", lote.id);
                            return FALSE;
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


/***
 * Descriao: Mostra tabuleiro (id e Tipo) guardado num arquivode texto
 * Input:   filename[] - Nome do arquivo representando o tabuleiro
 *          tabuleiro  - para guardar os lotes lidos do arquivo
 * Output: None
*/
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
                printf("%2d_%c  ", tabuleiro[i][j].id, (tabuleiro[i][j].tipo == 1) ? 'C' : 'L');
            }
            printf("\n");
        }
    }
    else
        erro_abrir_fich(filename);
}


/***
 * Descriao: Mostra as informações e a localização de um lote dado um determinado id
 * Input:   armazem - Armazém onde pode estar o id passado
 *          id - ID do lote a ser mostrado em caso de existir no armazém
 * Output: None
*/
void show_batch_info(ARMAZEM armazem, int id){
    COORD_ARMAZEM coord = {0, 0, 0};
    if(existe_id_armazem(armazem, id, &coord) == TRUE){
        printf("\n\t========= PRODUCT =======\n");
        show_one_batch(armazem.slote[coord.prt][coord.xs][coord.ys].lote);
        printf("\tSlot %d %d Shelf: %d\n", coord.xs, coord.ys, coord.prt);
    }
    else
        printf("Id %d Não existe no armazém\n", id);
}


/***
 * Descriao: Mostra todos os lotes existentes num armazem
 * Input: armazem - armazém onde estarão os lotes
 * Output: none
*/
void show_batches(ARMAZEM armazem){
    printf("\n============= SIZE %d ==================\n", armazem.tamanho);
    for(int i = 0; i < PRATELEIRA; i++){
        for(int j = 0; j < XSLOTE; j++){
            for(int k = 0; k < YSLOTE; k++){
                if(armazem.slote[i][j][k].ocupado == TRUE){
                    show_one_batch(armazem.slote[i][j][k].lote);
                    printf("\tSlot %d %d Shelf: %d\n", j, k, i);
                    printf("\n");
                }
            }
        }
    }
}


/***
 * Descriao:  Dado uma prateieira do armazém, mostra 'X' em caso de estar ocupado ou '.' caso contrário
 * Input:   armazem - armazém na qual queremos mostrar
 *          prateleira - prateleira do armazém
 * Output: None
*/
void show_worehouse(ARMAZEM armazem, int prateleira){
    printf("----------- WAREHOUSE %d -----------\n\n", armazem.tamanho);
    for(int i = 0; i < XSLOTE; i++){
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


/***
 * Descriao: Dado um ficheiro representando tabuleiro, lê e guarda no tabuleiro[4][4] e no armazem
 * Input:   filename[] - nome do ficheiro representando o tabuleiro
 *          tabuleiro[4][4] - tabuleiro a guardar os lotes vindo do ficheiro
 *          *armazem - endereço do armazém para guardar os lotes vindo do ficheiro
 * Output: None
*/
void store_tray(char filename[], LOTE tabuleiro[TAM_TAB][TAM_TAB], ARMAZEM *armazem){
    FILE *file = fopen(filename, "r");
    LOTE aux_lote;
    COORD_ARMAZEM coord = {-1, -1, -1};

    if(file){
        for(int i = 0; i < TAM_TAB; i++){
            for(int j = 0; j < TAM_TAB; j++){
                if(!feof(file)){
                    fscanf(file, "%d %s %s %d %d\n", &aux_lote.id, aux_lote.destino, aux_lote.data, 
                                                         &aux_lote.quantidade, &aux_lote.tipo);
                    if(existe_id_tabuleiro(tabuleiro, aux_lote.id) == FALSE){ // FIXE
                        tabuleiro[i][j] = aux_lote;
                        printf("Id: %2d Tray: %d %d", aux_lote.id, i, j);
                    }
                    else
                        printf("Repeated product ID: %d Discarding", aux_lote.id);
                    if(existe_id_armazem(*armazem, aux_lote.id, &coord) == FALSE){
                            inserir_lote_armazem(armazem, aux_lote, TRUE);
                        }
                        else
                            printf("\nRepeated ID %d in WAREHOUSE\n", aux_lote.id);
                }
            }
        }
    }
    else
        erro_abrir_fich(filename);
}


/***
 * Descriao: Troca de lugares dos lotes no armazém dado um id e se o mesmo existir
 * Input:   *armazem - armazém no qual queremos trocar o lugar de um lote
 *          id - ID do lote a trocar
 * Output: None
*/
void swap_batch_placement(ARMAZEM *armazem, int id){
    LOTE tmp_lote;
    COORD_ARMAZEM a_coord = {-1, -1, -1}; // coordenada atual do produto
    COORD_ARMAZEM n_coord = {-1, -1, -1}; // nova coordenadas do produto

    if(existe_id_armazem(*armazem, id, &a_coord) == TRUE){ // se o produto existir no armazém
        ler_coord_armazem(&n_coord);
        if(armazem->slote[n_coord.prt][n_coord.xs][n_coord.ys].ocupado == TRUE){ // nova coordenada já existe produto (trocar)
            tmp_lote = armazem->slote[n_coord.prt][n_coord.xs][n_coord.ys].lote;
            armazem->slote[n_coord.prt][n_coord.xs][n_coord.ys].lote = armazem->slote[a_coord.prt][a_coord.xs][a_coord.ys].lote;
            armazem->slote[a_coord.prt][a_coord.xs][a_coord.ys].lote = tmp_lote;
        }
        else{ // Em caso da nova posição estar vazio
            armazem->slote[n_coord.prt][n_coord.xs][n_coord.ys].lote = armazem->slote[a_coord.prt][a_coord.xs][a_coord.ys].lote;
            armazem->slote[n_coord.prt][n_coord.xs][n_coord.ys].ocupado = TRUE;
            armazem->slote[a_coord.prt][a_coord.xs][a_coord.ys].ocupado = FALSE;
            armazem->slote[a_coord.prt][a_coord.xs][a_coord.ys].lote.id = 0;
        }
    }
    else
        printf("Product with ID: %d does't exist\n", id);
}


/***
 * Descriao: Verifica se um destino existe numa matriz
 * Input: cidades[20][30] : 20 cidades
 *        cidade[]        : cidade a verificar
 * Output: Trye se o destino existe caso contrário False
*/
boolean existe_destino(char destinos[20][30], char destino[]){
    for(int i = 0; i < 20; i++){
        if(strcmp(destinos[i], destino) == 0)
            return TRUE;
    }
    return FALSE;
}

/***
 * Descriao: Mostra as estatíscas de um armazém
 * Input: armazem - armazém para qual queremos mostrar as estatísticas
 * Output: None
*/
void show_statistics(ARMAZEM armazem){
    int total_destino=0;
    char nomes_destino[100][30] = {" "}, destino_n_rep[100][30];
    int *info[3] = {0};
    int i, j, k, h = 0;
    int asterisco = 50, porcem = 100, maior_quant, total_produto;

    // Pega todas as cidades que estão no aramzém
    for(i = 0; i < PRATELEIRA; i++){
        for(j = 0; j < XSLOTE; j++){
            for(k = 0; k < YSLOTE; k++){
                if(armazem.slote[i][j][k].ocupado == TRUE){
                    strcpy(nomes_destino[h++], armazem.slote[i][j][k].lote.destino);
                }
            }
        }
    }

    // Retirar cidades repetidas
    // h fica com total de cidades (repetidos) no armazém
    for(int g = 0, i = 0; i < h; i++){
        if(existe_destino(destino_n_rep, nomes_destino[i]) == FALSE){
            strcpy(destino_n_rep[g++], nomes_destino[i]);
            total_destino++;
        }
    }

    // alocar memória para 
    // 0 - Total de cada cidade
    // 1 -   ||  de Cartões de cada cidade
    // 2 -   ||  de Livretes de cada cidade
    for(i = 0; i < 3; i++)
        info[i] = (int*) calloc(total_destino, sizeof(int));

    for(h = 0; h < total_destino; h++){     // Percorre a cada cidade
        for(i = 0; i < PRATELEIRA; i++){
            for(j = 0; j < XSLOTE; j++){
                for(k = 0; k < YSLOTE; k++){
                    if(armazem.slote[i][j][k].ocupado == TRUE){
                        if(strcmp(destino_n_rep[h], armazem.slote[i][j][k].lote.destino) == 0){
                            info[0][h]++;
                            if(armazem.slote[i][j][k].lote.tipo == 1){      // Em caso de ser Cartão
                                info[1][h] += armazem.slote[i][j][k].lote.quantidade;
                            }
                            else{                                           // Livrete
                                info[2][h] += armazem.slote[i][j][k].lote.quantidade;
                            }
                        }
                    }
                }
            }
        }
    }

    // Mostrar as informações dos destinos 
    for(i=0; i < total_destino; i++){
        printf("%-10s Total: %3d  Cartao: %3d  Livrete: %3d\n",
        destino_n_rep[i], info[0][i],info[1][i], info[2][i]);
    }
    printf("\n");

    // pega a maior quantidade de produtos existente no armazém
    maior_quant = info[1][0] + info[2][0];          // maior fica com o total do peimeiro produto
    for(i = 1; i < total_destino; i++){
        total_produto = info[1][i] + info[2][i];    // total de produto em cada cidade
        if(total_produto >= maior_quant)            // Compara o total de produto atual com o maior
            maior_quant = total_produto;            // guardar maior número de produto (livrete e cartão)
    }

    // Inprimir * na proporção
    for(i=0; i < total_destino; i++){
        total_produto = info[1][i] + info[2][i];
        printf("%-10s (%3d): ",  destino_n_rep[i], total_produto); // imprimi destino e o total de produto
        if(total_produto == maior_quant){                      // o maior imprimi 50 *
            print_char(asterisco, '*');
        }
        else{
            h = (int) (total_produto * porcem) / maior_quant;
            print_char((h * asterisco / porcem), '*');
        }
    }

    // Liberar memória alocada
    for(i = 0; i < 3; i++)
        free(info[i]);
}


/***
 * Descriao: 
 * Input: *armazem : armazém onde será feito a expedição
 *        destino[]: nome do destino
 *        data[]   : data limite dos produtos
 * Output: None
*/
void perform_expedition(ARMAZEM *armazem, char destino[], char data[]){
    int total_product = 0;
    int ids[20], indexId=0, qntTipo=0;
    char confirm = ' ';
    LOTE aux;
    int caixas[20] = {0}, sizeBox = 200, sizeCart=1, sizeLiv = 4;
    int infoIds[20][20] = {0}, indInfo = 0, tipos[20] = {0}, quantys[20]={0};

    putchar('\n');
    for(int i = 0; i < PRATELEIRA; i++){
        for(int j = 0; j < XSLOTE; j++){
            for(int k = 0; k < YSLOTE; k++){
                aux = armazem->slote[i][j][k].lote;
                if(strcmp(aux.destino, destino) == 0){
                    if(strcmp(aux.data, data) <= 0){ // Se está dentro do prazo
                        if(aux.id > 0){
                            ids[indexId++] = aux.id;
                            if(aux.tipo == 1){
                                qntTipo = aux.quantidade * sizeCart;
                                // quantys[indInfo] = qntTipo;
                                tipos[indInfo] = 1;
                            }
                            else{
                                qntTipo = aux.quantidade * sizeLiv;
                                tipos[indInfo] = 2;
                            }
                            quantys[indInfo] = qntTipo;

                            printf("ID: %2d Qnty: %d\n", aux.id, qntTipo);
                            for(int h = 0; h < 20; h++){
                                if((caixas[h] <= sizeBox) && (caixas[h] + qntTipo <= sizeBox)){
                                    caixas[h] += qntTipo;
                                    infoIds[h][indInfo++] = aux.id;
                                    break;
                                }
                            }
                            total_product++;
                        }
                    }
                }
            }
        }
    }
    if(total_product > 0){      // em caso de encontrar um produto com a descrição (nome do destino e a data válida)
        printf("\nCREATING BOXES FOR DESTINATION: %s\n", destino);
        for(int i = 0; i < 20; i++){
            if(caixas[i] > 0){
                printf("BOX %d:\n", i);
                for(int j = 0; j < indInfo; j++){
                    if(infoIds[i][j] > 0){
                        printf("\tID: %2d ", infoIds[i][j]);
                        if(tipos[j] == 1)
                            printf("Qnty: %3d (C)\n", quantys[j]);
                        else
                            printf("Qnty: %3d (L)\n", quantys[j]);
                    }
                }
            }
        }
        putchar('\n');
        do{
            confirm = ler_char("Confirm expedition (y/n): ");
            confirm = toupper(confirm);
        }while(confirm != 'N' && confirm != 'Y');

        if(confirm == 'Y'){
            for(int i = 0; i < PRATELEIRA; i++){
                for(int j = 0; j < XSLOTE; j++){
                    for(int k = 0; k < YSLOTE; k++){
                        for(int h = 0; h < total_product; h++){
                            if(armazem->slote[i][j][k].lote.id == ids[h]){
                                armazem->slote[i][j][k].lote.id = 0;        
                                armazem->slote[i][j][k].ocupado = FALSE;    // retirar do armazém os produtos encontrados
                                armazem->tamanho--;
                            }
                        }
                    }
                }
            }
            printf("Product(s) Removed from Warehouse\n");
        }
        else
            printf("Expedition discarted\n");
    }
    else
        printf("%s doesn't have product in warehouse or product is out of time\n", destino);
}


//########################### HANDLE FILES ########################
/***
 * Descriao: dado nome de um ficheiro texto com os lotes nele, lê e coloca no armazém
 * Input:    filename[] - nome do ficheiro a ler
 *           *armazem - armazém onde queremos inserir os lotes vindo do ficheiro
 * Output: None
*/
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
                        return;         // fim do arquivo, acaba o procedimento
                    }
                }
            }
        }
        fclose(file);
    }
    else
        erro_abrir_fich(filename);
}


/***
 * Descriao: dado nome de um ficheiro binário com os lotes nele, lê e coloca no armazém
 * Input:   filename[] - nome do ficheiro a ler
 *          *armazem - armazém onde queremos inserir os lotes vindo do ficheiro
 * Output: None
*/
void ler_ficheiro_bin(char filename[], ARMAZEM *armazem){
    FILE *file = fopen(filename, "rb");
    SLOTE slote;

    if(file){
        while(!feof(file)){
            if(fread(&slote, sizeof(SLOTE), 1, file)){
                if(slote.lote.id > 0){                            // Id válido
                    inserir_lote_armazem(armazem, slote.lote, FALSE);
                }
            }
        }
        fclose(file);
    }
    else
        erro_abrir_fich(filename);
}


/***
 * Descriao: dado nome de um ficheiro texto, escreve todos os lotes que estão no aramzém
 * Input:   filename[] - nome do ficheiro a escrever
 *          *armazem - armazém onde estão os lotes
 * Output: None
*/
void escrever_fich_bin(char filename[], ARMAZEM armazem){
    FILE *file = fopen(filename, "wb");

    if(file){ // Se o arquivo foi aberto(não houve erro)
        for(int i = 0; i < PRATELEIRA; i++){
            for(int j = 0; j < XSLOTE; j++){
                for(int k = 0; k < YSLOTE; k++){
                    if(armazem.slote[i][j][k].ocupado == TRUE){
                        fwrite(&(armazem.slote[i][j][k]), sizeof(SLOTE), 1, file);
                    }
                }
            }
        }
        fclose(file);
    }
    else
        erro_abrir_fich(filename);
}


/***
 * Descriao: Mostra as opções de escolha (menu)
 * Input:   *opcao - opção de escolha 
 * Output: None
*/
void menu_pricipal(char *opcao){
    printf("\n=============== MENU ===============\n");
    printf("\t1 - Show tray\n");
    printf("\t2 - Show batch info\n");
    printf("\t3 - Show batches\n");
    printf("\t4 - Show warehouse occupancy\n\n");

    printf("\t5 - Store tray\n");
    printf("\t6 - Swap batch placement\n");
    printf("\t7 - Show statistics\n\n");

    printf("\t8 - Perform expedition\n");
    printf("\te - exit");
    printf("\n====================================\n");
    *opcao = ler_char("Choose the option: ");
    printf("\n");
}


//####################### MAIN FUNCTION ####################
/***
 * Descriao: Função principal
 * Input:   argc - total de argumentos passados na linha de comando
 *          *argv[] - os argumentos passados na linha do comando
 * Output: 0
*/
int main(int argc, char *argv[]){

    LOTE tabuleiro[TAM_TAB][TAM_TAB];
    ARMAZEM armazem;                            // armazém
    char opcao;                                 // opção digitada
    char filename[15];                          // general purpose para nome de arquivo pedido
    char file_bin[] = "warehouse.dat";          // nome do arquivo de incialização
    char destino[30], data[12];
    int numero;                                 // general purpose para números

    inicializar_armazem(&armazem);              // todos os Id = 0 e ocupado = False (0)
    inicializar_tabuleiro(tabuleiro);           // ids = 0

    ler_ficheiro_bin(file_bin, &armazem);       // inicializar o programa lendo o arquivo binário
    if(argc > 1){                               // em caso de passar nome do tabuleiro na linha de comando
        ler_ficheiro_txt(argv[1], &armazem);
    }

    do{
        menu_pricipal(&opcao);                  // mostra menu e lê opção

        switch(opcao){
            case '1':
                printf("Entry the filename: ");
                ler_texto(filename, 15, 1);
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
                numero = ler_inteiro(0, PRATELEIRA-1, "Choose shelf [0 - 4]: ");
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
                printf("Destination: ");
                ler_texto(destino, 30, TRUE);
                for(int i = 0; i < strlen(destino); i++)
                    destino[i] = toupper(destino[i]);       // converte parar maiúsculas
                printf("Date: ");
                ler_texto(data, 12, TRUE);
                perform_expedition(&armazem, destino, data);
            break;
            case 'e': case 'E':
                printf("Thank You!! Good Bye\n");
                break;
            default:
                printf("Inválid Option\n");
        }
    }while(opcao != 'e' && opcao != 'E');

    escrever_fich_bin(file_bin, armazem);               // escreve tudo o que está no armazém para o arquivo binário
    return 0;
}
