#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CIDADAO 50
#define TAM_DADOS 100

struct NUM_SERV_SEC{
    int num_serie;
};

struct INFO_PESSOAL{
    char nome [TAM_DADOS];
    int dia_nasc;
    int mes_nasc;
    int ano_nasc;
    int altura;
    char olhos [TAM_DADOS];
    char cabelo [TAM_DADOS];
};

struct INFO_NUMBER{
    int bi;
    int contribuinte;
    int seg_social;
    int carta_cond;
};

struct MORADA{
    char rua [TAM_DADOS];
    int cod_postal1;
    int cod_postal2;
    char cod_postal3 [TAM_DADOS];
};

struct CONFID{
    char partido [TAM_DADOS];
    char clube [TAM_DADOS];
};

struct CIDADAO{
    struct NUM_SERV_SEC nss;
    struct INFO_PESSOAL infp;
    struct INFO_NUMBER infn;
    struct MORADA address;
    struct CONFID clubes;
};

typedef struct{
    int tamanho;
    struct CIDADAO cidadaos[MAX_CIDADAO];
}BASEDADOS;


// #################### AUXILIAR FUNCTION ######################
void clear_buffer(){
    char ch;
    do{
        ch = getchar();
    }while(ch != '\n');
}

void le_inteiro(int *num, int min, int max, char *msg){
    int ret=0;
    do{
        printf("%s", msg);
        ret = scanf("%d", num);
        clear_buffer();
    }while(ret != 1 || (*num < min || *num > max));
}

void le_text(char *text, int tam){
    char ch;
    int i = 0;

    for(i = 0; i < tam; i++){
        ch = getchar();
        if(ch == '\n'){
            break;
        }
        else
            text[i] = ch;
    }
    text[i] = '\0';
}

void tira_enter(char txt[]){
    txt[strlen(txt)-1] = ' ';
}


// #####################################################

int verifica_nss(BASEDADOS base, int nss){
    for(int i = 0; i < MAX_CIDADAO; i++){
        if(nss == base.cidadaos[i].nss.num_serie)
            return 1;
    }
    return 0;
}

void le_nss(struct NUM_SERV_SEC *nss, BASEDADOS base){
    int controlo = 1;
    do{
        controlo = 1;
        le_inteiro(&(nss->num_serie), 1, 30000, "Digite o NSS: ");
        for(int i = 0; i < TAM_DADOS; i++){
            if(nss->num_serie == base.cidadaos[i].nss.num_serie){
                printf("\nNÚMERO DE SÉRIE JÁ EXISTE\n");
                controlo = 0;
                break;
            }
        }
        if(controlo)
            return;
    }while(1);
}

void le_info_pessoal(struct INFO_PESSOAL *infp){
    printf("INTRODUZA OS DADOS PESSOAS\n");
    printf("\tNome.........: ");
    le_text(infp->nome, TAM_DADOS);
    le_inteiro(&(infp->dia_nasc), 1, 31, "\tDia..........: ");
    le_inteiro(&(infp->mes_nasc), 1, 12, "\tMês..........: ");
    le_inteiro(&(infp->ano_nasc), 1900, 2022, "\tAno..........: ");
    le_inteiro(&(infp->altura), 1, 270, "\tAltura.......: ");
    printf("\tCor dos olhos: ");
    le_text(infp->olhos, TAM_DADOS);
    printf("\tCor do cabelo: ");
    le_text(infp->cabelo, TAM_DADOS);
}

void le_info_number(struct INFO_NUMBER *infn){
    printf("INTRODUZA OS DADOS NUMÉRICOS\n");
    le_inteiro(&(infn->bi), 1, 30000, "\tNúmero de BI......: ");
    le_inteiro(&(infn->contribuinte), 1, 30000, "\tNr de contribuente: ");
    le_inteiro(&(infn->seg_social), 1, 30000, "\tSeg social........: ");
    le_inteiro(&(infn->carta_cond), 1, 30000, "\tNr da carta_cond..: ");
}

void le_morada(struct MORADA *address){
    printf("INTRODUZA OS DADOS DA MORADA\n");
    printf("\tRua...........: ");
    le_text(address->rua, TAM_DADOS);
    le_inteiro(&(address->cod_postal1), 1, 9999, "\tCódigo postal1: ");
    le_inteiro(&(address->cod_postal2), 1, 9999, "\tCódigo postal2: ");
    printf("\tCódigo postal3: ");
    le_text(address->cod_postal3, TAM_DADOS);
}

void le_confidencial(struct CONFID *clubes){
    printf("DADOS CONFIDENCIAIS\n");
    printf("\tPartido: ");
    le_text(clubes->partido, TAM_DADOS);
    printf("\tClube..: ");
    le_text(clubes->clube, TAM_DADOS);
}

void le_cidadao(struct CIDADAO *cid, BASEDADOS base){
    le_nss(&(cid->nss), base);
    le_info_pessoal(&(cid->infp));
    le_info_number(&(cid->infn));
    le_morada(&(cid->address));
    le_confidencial(&(cid->clubes));
}


// ##################### IMPRESSÃO DOS DADOS ##############

void print_nss(struct NUM_SERV_SEC nss){
    printf("NSS: %d\n", nss.num_serie);
}

void print_info_pessoal(struct INFO_PESSOAL infp){
    printf("INFORMAÇÃO PESSOAL\n");
    printf("\tNome......: %s\n", infp.nome);
    printf("\tData......: %02d/%02d/%04d\n", infp.dia_nasc, infp.mes_nasc, infp.ano_nasc);
    printf("\tAltura....: %d\n", infp.altura);
    printf("\tCor Olhos.: %s\n", infp.olhos);
    printf("\tCor Cabelo: %s\n", infp.cabelo);
}

void print_info_number(struct INFO_NUMBER infn){
    printf("INFORMAÇÃO DE NÚMERO\n");
    printf("\tBI...............: %d\n", infn.bi);
    printf("\tNr. Contribuente.: %d\n", infn.contribuinte);
    printf("\tSeguranca Social.: %d\n", infn.seg_social);
    printf("\tCarta de condução: %d\n", infn.carta_cond);
}

void print_morada(struct MORADA address){
    printf("INFORMAÇÃO DE MORADA\n");
    printf("\tRua...........: %s\n", address.rua);
    printf("\tCódigo Postal1: %d\n", address.cod_postal1);
    printf("\tCódigo Postal2: %d\n", address.cod_postal2);
    printf("\tCódigo Postal3: %s\n", address.cod_postal3);
}

void print_confidencial(struct CONFID clubes){
    printf("INFORMAÇÃO CONFIDENCIAL\n");
    printf("\tPartido: %s\n", clubes.partido);
    printf("\tClube..: %s\n", clubes.clube);
}

void print_cidadao(struct CIDADAO cid){
    printf("DADOS DO CIDADAO\n");
    print_nss(cid.nss);
    print_info_pessoal(cid.infp);
    print_info_number(cid.infn);
    print_morada(cid.address);
    print_confidencial(cid.clubes);
}


// ########################## MENUS #######################

void incializar_base(BASEDADOS *base){
    base->tamanho = 0;
    for(int i = 0; i < MAX_CIDADAO; i++)
        base->cidadaos[i].nss.num_serie = 0;
}

void base_vazia(){
    printf("\nBASE DE DADOS ESTÁ VAZIA\n\n");
}

void nao_existe_nss(int nss){
    printf("\nCIDADÃO COM NSS %d NÃO EXISTE\n", nss);
}

void mostrar_nss(BASEDADOS base){
    if(base.tamanho > 0){
        for(int i = 0; i < MAX_CIDADAO; i++){
            if(base.cidadaos[i].nss.num_serie != 0){
                print_nss(base.cidadaos[i].nss);
            }
        }
    }
    else
        base_vazia();
}

void mostrar_info_cidadao(BASEDADOS base, int nss){
    for(int i = 0; i < MAX_CIDADAO; i++){
        if(base.cidadaos[i].nss.num_serie == nss){
            print_cidadao(base.cidadaos[i]);
            return;
        }
    }
    nao_existe_nss(nss);
}

void modificar_cidadao(BASEDADOS *base, int nss){
    for(int i = 0; i < MAX_CIDADAO; i++){
        if(base->cidadaos[i].nss.num_serie == nss){
            le_info_pessoal(&(base->cidadaos[i].infp));
            le_info_number(&(base->cidadaos[i].infn));
            le_morada(&(base->cidadaos[i].address));
            le_confidencial(&(base->cidadaos[i].clubes));
            return;
        }
    }
    nao_existe_nss(nss);
}

void novo_registo(BASEDADOS *base){
    if(base->tamanho <= MAX_CIDADAO){
        for(int i = 0; i < MAX_CIDADAO; i++){
            if(base->cidadaos[i].nss.num_serie == 0){
                le_cidadao(&(base->cidadaos[i]), *base);
                base->tamanho++;
                return;
            }
        }
    }
    else
        printf("\nA BASE DE DADOS ESTÁ CHEIA\n");
}

int apagar_registo(BASEDADOS *base, int nss){
    for(int i = 0; i < MAX_CIDADAO; i++){
        if(base->cidadaos[i].nss.num_serie == nss){
            base->cidadaos[i].nss.num_serie = 0;
            base->tamanho--;
            return 1;
        }
    }
    nao_existe_nss(nss);
    return 0;
}


// #################### ARQUIVOS ##########################

void erro_abrir_fich(char arq[]){
    printf("\nERRP AO ABRIR O ARQUIVO %s\n", arq);
}

void inserir_cid_ficheiro(BASEDADOS *base, struct CIDADAO cidadao){
    if(base->tamanho < MAX_CIDADAO){
        if(!verifica_nss(*base, cidadao.nss.num_serie)){
            base->cidadaos[base->tamanho++] = cidadao;
        }
        else
            printf("\nCIDADÃO COM NSS %d JÁ EXISTE\n", cidadao.nss.num_serie);
    }
    else
        printf("\nA BASE DE DADOS ESTA CHEIA\n");
}

void ler_binario(BASEDADOS *base, char arq[]){
    FILE *file = fopen(arq, "rb");
    struct CIDADAO cid_aux;

    if(file){
        while(!feof(file)){
            fread(&cid_aux, sizeof(struct CIDADAO), 1, file);
            inserir_cid_ficheiro(base, cid_aux);
        }
        fclose(file);
    }
    else
        erro_abrir_fich(arq);
}

void ler_texto(BASEDADOS *base, char arq[]){
    FILE *file = fopen(arq, "r");
    struct CIDADAO cid_aux;

    if(file){
        while(!feof(file)){
            fscanf(file, "%d\n", &cid_aux.nss.num_serie);

            fgets(cid_aux.infp.nome, TAM_DADOS, file);
            tira_enter(cid_aux.infp.nome);
            fscanf(file, "%d\n", &cid_aux.infp.dia_nasc);
            fscanf(file, "%d\n", &cid_aux.infp.mes_nasc);
            fscanf(file, "%d\n", &cid_aux.infp.ano_nasc);
            fscanf(file, "%d\n", &cid_aux.infp.altura);

            fgets(cid_aux.infp.olhos, TAM_DADOS, file);
            tira_enter(cid_aux.infp.olhos);
            fgets(cid_aux.infp.cabelo, TAM_DADOS, file);
            tira_enter(cid_aux.infp.cabelo);

            fscanf(file, "%d\n", &cid_aux.infn.bi);
            fscanf(file, "%d\n", &cid_aux.infn.contribuinte);
            fscanf(file, "%d\n", &cid_aux.infn.seg_social);
            fscanf(file, "%d\n", &cid_aux.infn.carta_cond);

            fgets(cid_aux.address.rua, TAM_DADOS, file);
            tira_enter(cid_aux.address.rua);
            fscanf(file, "%d\n", &cid_aux.address.cod_postal1);
            fscanf(file, "%d\n", &cid_aux.address.cod_postal2);
            fgets(cid_aux.address.cod_postal3, TAM_DADOS, file);
            tira_enter(cid_aux.address.cod_postal3);

            fgets(cid_aux.clubes.partido, TAM_DADOS, file);
            tira_enter(cid_aux.clubes.partido);
            fgets(cid_aux.clubes.clube, TAM_DADOS, file);

            inserir_cid_ficheiro(base, cid_aux);
        }
        fclose(file);
    }
    else
        erro_abrir_fich(arq);
}

void escrever_binario(BASEDADOS base, char arq[]){
    FILE *file = fopen(arq, "wb");
    if(file){
        for(int i = 0; i < MAX_CIDADAO; i++){
            if(base.cidadaos[i].nss.num_serie != 0){
                fwrite(&(base.cidadaos[i]), sizeof(struct CIDADAO), 1, file);
            }
        }
        fclose(file);
    }
    else
        erro_abrir_fich(arq);
}

void escrever_texto(BASEDADOS base, char arq[]){
    FILE *file = fopen(arq, "w");
    int i = 0;

    if(file){
        for(i = 0; i < MAX_CIDADAO; i++){
            if(base.cidadaos[i].nss.num_serie != 0){
                fprintf(file, "%d\n", base.cidadaos[i].nss.num_serie);

                fprintf(file, "%s\n", base.cidadaos[i].infp.nome);
                fprintf(file, "%d\n", base.cidadaos[i].infp.dia_nasc);
                fprintf(file, "%d\n", base.cidadaos[i].infp.mes_nasc);
                fprintf(file, "%d\n", base.cidadaos[i].infp.ano_nasc);
                fprintf(file, "%d\n", base.cidadaos[i].infp.altura);
                fprintf(file, "%s\n", base.cidadaos[i].infp.olhos);
                fprintf(file, "%s\n", base.cidadaos[i].infp.cabelo);

                fprintf(file, "%d\n", base.cidadaos[i].infn.bi);
                fprintf(file, "%d\n", base.cidadaos[i].infn.contribuinte);
                fprintf(file, "%d\n", base.cidadaos[i].infn.seg_social);
                fprintf(file, "%d\n", base.cidadaos[i].infn.carta_cond);

                fprintf(file, "%s\n", base.cidadaos[i].address.rua);
                fprintf(file, "%d\n", base.cidadaos[i].address.cod_postal1);
                fprintf(file, "%d\n", base.cidadaos[i].address.cod_postal2);
                fprintf(file, "%s\n", base.cidadaos[i].address.cod_postal3);

                fprintf(file, "%s\n", base.cidadaos[i].clubes.partido);
                fprintf(file, "%s\n", base.cidadaos[i].clubes.clube);
            }
        }
        fclose(file);
    }
    else
        erro_abrir_fich(arq);
}


// ########################### inserção < ###################

void ler_stdin_fich(BASEDADOS *base){

    struct CIDADAO cid;
    
    for(int i = 0; i < 5; i++){
        scanf("%d\n", &cid.nss.num_serie);
        le_text(cid.infp.nome, TAM_DADOS);
        scanf("%d\n", &cid.infp.dia_nasc);
        scanf("%d\n", &cid.infp.mes_nasc);
        scanf("%d\n", &cid.infp.ano_nasc);
        scanf("%d\n", &cid.infp.altura);
        le_text(cid.infp.olhos, TAM_DADOS);
        le_text(cid.infp.cabelo, TAM_DADOS);

        scanf("%d\n", &cid.infn.bi);
        scanf("%d\n", &cid.infn.contribuinte);
        scanf("%d\n", &cid.infn.seg_social);
        scanf("%d\n", &cid.infn.carta_cond);

        le_text(cid.address.rua, TAM_DADOS);
        scanf("%d\n", &cid.address.cod_postal1);
        scanf("%d\n", &cid.address.cod_postal2);
        le_text(cid.address.cod_postal3, TAM_DADOS);

        le_text(cid.clubes.partido, TAM_DADOS);
        le_text(cid.clubes.clube, TAM_DADOS);

        print_cidadao(cid);
        base->cidadaos[i] = cid;
    }
    escrever_binario(*base, "resultado.dat");
    exit(1);
}

// ################## EXERCÍCIO 4.4 ###################3
void mundo_verde(BASEDADOS *base, char arq[], char esc[]){
    ler_texto(base, arq);
    for(int i = 0; i < MAX_CIDADAO; i++){
        if(base->cidadaos[i].nss.num_serie != 0){
            strcpy(base->cidadaos[i].clubes.clube, "Sporting Clube de Portugal");
        }
    }
    escrever_texto(*base, esc);
}


void isolar_cidadao(){
    BASEDADOS aux_base, base;
    incializar_base(&aux_base);
    incializar_base(&base);
    ler_texto(&aux_base, "cobaia.txt");
    
    for(int i = 0; i < MAX_CIDADAO; i++){
        if(aux_base.cidadaos[i].infp.altura >= 160){
            base.cidadaos[i] = aux_base.cidadaos[i];
            base.tamanho++;
        }
    }

    escrever_texto(base, "maior_160cm.txt");
}


// ########################## MENU ##########################
void menu(char *opcao){
    printf("---------------------------------------------------------------------------\n");
    printf("|   /*********** PROGRAMA SIRP - Registo dos cidadãos **********/          |\n");
    printf("----------------------------------------------------------------------------\n");
    printf("|                                                                          |\n");
    printf("| a - Mostrar os números de série de todos os elementos da base de dados   |\n");
    printf("| b - Mostrar toda a informação do cidadão com um certo número (a pedir)   |\n");
    printf("| c - Modificar a informação do cidadão com um certo número (a pedir)      |\n");
    printf("| d - Criar um novo registo para um novo cidadão                           |\n");
    printf("| e - Apagar o registo com um certo número (a pedir)                       |\n");
    printf("| f - Ler a base de dados de um ficheiro em modo binário (nome a pedir)    |\n");
    printf("| g - Ler a base de dados de um ficheiro em modo de texto (nome a pedir)   |\n");
    printf("| h - Escrever a base de dados num ficheiro em modo binário (nome a pedir) |\n");
    printf("| i - Escrever a base de dados num ficheiro em modo de text (nome a pedir) |\n");
    printf("| j - Tornar o mundo verde                                                 |\n");
    printf("| k - Isolar cidadãos                                                      |\n");
    printf("| s - Sair do programa                                                     |\n");
    printf("| z - Mostrar todos (EXTRA)                                                |\n");
    printf("|                                                                          |\n");
    printf("----------------------------------------------------------------------------\n");

    printf("Qual é a opção: ");
    *opcao = getchar();
    clear_buffer();
    printf("\n");
}


// ########################## MAIN/START ###################
int main(int argc, char *argv[]){

    BASEDADOS basedados;
    int nss;
    char opcao;
    char arquivo[TAM_DADOS], arq_ex_4_4[TAM_DADOS];

    system("clear");

    incializar_base(&basedados);
    
    if(argc == 2){
        if(strcmp(strrchr(argv[1], '.'),  ".dat") == 0){
            ler_binario(&basedados, argv[1]);
        }
        else if(strcmp(strrchr(argv[1], '.'), ".txt") == 0){
            ler_texto(&basedados, argv[1]);
        }
    }

    do{
        menu(&opcao);
        switch(opcao){
            case 'a': case 'A':
                if(basedados.tamanho > 0)
                    mostrar_nss(basedados);
                else
                    base_vazia();
            break;
            case 'b': case 'B':
                if(basedados.tamanho > 0){
                    printf("\n");
                    le_inteiro(&nss, 1, 30000, "Digite o NSS a Ver: ");
                    mostrar_info_cidadao(basedados, nss);
                    printf("\n");
                }
                else
                    base_vazia();
            break;
            case 'c': case 'C':
                if(basedados.tamanho > 0){
                    le_inteiro(&nss, 1, 30000, "Digite o NSS a Modificar: ");
                    modificar_cidadao(&basedados, nss);
                }
                else
                    base_vazia();
            break;
            case 'd': case 'D':
                printf("\n");
                novo_registo(&basedados);
                printf("\nREGISTRO INSERIDO COM SUCESSO\n\n");
            break;
            case 'e': case 'E':
                if(basedados.tamanho > 0){
                    le_inteiro(&nss, 1, 30000, "Digite o NSS a Apagar: ");
                    if(apagar_registo(&basedados, nss) == 1)
                        printf("\nREGISTRO REMOVIDO COM SUCESSO\n\n");
                }
                else
                    base_vazia();
            break;
            case 'f': case 'F':
                printf("Digite o nome do arquivo: ");
                le_text(arquivo, TAM_DADOS);
                ler_binario(&basedados, arquivo);
            break;
            case 'g': case 'G':
                printf("Digite o nome do arquivo: ");
                le_text(arquivo, TAM_DADOS);
                ler_texto(&basedados, arquivo);
            break;
            case 'h': case 'H':
                if(basedados.tamanho != 0){
                    printf("Digite o nome do arquivo: ");
                    le_text(arquivo, TAM_DADOS);
                    escrever_binario(basedados, arquivo);
                }
                else
                    base_vazia();
            break;
            case 'i': case 'I':
                if(basedados.tamanho != 0){
                    printf("Digite o nome do arquivo: ");
                    le_text(arquivo, TAM_DADOS);
                    escrever_texto(basedados, arquivo);
                }
                else
                    base_vazia();
            break;
            case 'j': case 'J':
                printf("Digite o nome do arquivo a ler: ");
                le_text(arquivo, TAM_DADOS);
                printf("Nome do arquivo a escrever: ");
                le_text(arq_ex_4_4, TAM_DADOS);
                mundo_verde(&basedados, arquivo, arq_ex_4_4);
            break;
            case 'k': case 'K':
                isolar_cidadao();
            break;
            case 'w': case 'W':
                ler_stdin_fich(&basedados);
            break;
            case 's': case 'S':
                printf("\n|========= MUITO OBRIGADO ==========|\n");
                exit(0);
            break;
            case 'z': case 'Z':
                printf("\nTAMANHO DA BASE: %d\n", basedados.tamanho);
                for(int i = 0; i < MAX_CIDADAO; i++)
                    printf("NSS: %2d = %d\n", i, basedados.cidadaos[i].nss.num_serie);
                printf("\n");
            break;
            default:
                printf("\nOPÇÃO INVÁLIDA\n\n");
        }
    }while(1);

    return 0;
}
