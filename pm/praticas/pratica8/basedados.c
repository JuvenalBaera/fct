#include <stdio.h>
#include <stdlib.h>

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
    }while(*num < min || *num > max);
}

void le_text(char *text, int tam){
    char ch;
    int i = 0;

    for(i = 0; i < tam; i++){
        ch = getchar();
        if(ch == '\n'){
            break;;
        }
        else
            text[i] = ch;
    }
    text[i] = '\0';
}


// #####################################################

void le_nss(struct NUM_SERV_SEC *nss){
    le_inteiro(&(nss->num_serie), 1, 30000, "Digite o NSS: ");
}

void le_info_pessoal(struct INFO_PESSOAL *infp){
    printf("INTRODUZA OS DADOS PESSOAS\n");
    printf("\tNome.........: ");
    le_text(infp->nome, TAM_DADOS);
    le_inteiro(&(infp->dia_nasc), 1, 31, "\tDia..........: ");
    le_inteiro(&(infp->mes_nasc), 1, 12, "\tMes..........: ");
    le_inteiro(&(infp->ano_nasc), 1900, 2022, "\tAno..........: ");
    le_inteiro(&(infp->altura), 1, 3, "\tAltura.......: ");
    printf("\tCor dos olhos: ");
    le_text(infp->olhos, TAM_DADOS);
    printf("\tCor do cabelo: ");
    le_text(infp->cabelo, TAM_DADOS);
}

void le_info_number(struct INFO_NUMBER *infn){
    printf("INTRODUZA DOS NUMEROS\n");
    le_inteiro(&(infn->bi), 1, 30000, "\tNumero de BI......: ");
    le_inteiro(&(infn->contribuinte), 1, 30000, "\tnr de contribuente: ");
    le_inteiro(&(infn->seg_social), 1, 30000, "\tSeg social........: ");
    le_inteiro(&(infn->carta_cond), 1, 30000, "\tNr da carta_cond..: ");
}

void le_morada(struct MORADA *address){
    printf("INTRODUZA OS DADOS DA MORADA\n");
    printf("\tRua...........: ");
    le_text(address->rua, TAM_DADOS);
    le_inteiro(&(address->cod_postal1), 1, 9999, "\tCodigo postal1: ");
    le_inteiro(&(address->cod_postal2), 1, 9999, "\tCodigo postal2: ");
    printf("\tCodigo postal3: ");
    le_text(address->cod_postal3, TAM_DADOS);
}

void le_confidencial(struct CONFID *clubes){
    printf("DADOS CONFIDENCIAIS\n");
    printf("\tPartido: ");
    le_text(clubes->partido, TAM_DADOS);
    printf("\tClube..: ");
    le_text(clubes->clube, TAM_DADOS);
}

void le_cidadao(struct CIDADAO *cid){
    le_nss(&(cid->nss));
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
    printf("INFORMACAO PESSOAL\n");
    printf("\tNome......: %s\n", infp.nome);
    printf("\tData......: %02d/%02d/%04d\n", infp.dia_nasc, infp.mes_nasc, infp.ano_nasc);
    printf("\tAltura....: %d\n", infp.altura);
    printf("\tCor Olhos.: %s\n", infp.olhos);
    printf("\tCor Cabelo: %s\n", infp.cabelo);
}

void print_info_number(struct INFO_NUMBER infn){
    printf("INFORMACAO DE NUMERO\n");
    printf("\tBI...............: %d\n", infn.bi);
    printf("\tNr. Contribuente.: %d\n", infn.contribuinte);
    printf("\tSeguranca Social.: %d\n", infn.seg_social);
    printf("\tCarta de conducao: %d\n", infn.carta_cond);
}

void print_morada(struct MORADA address){
    printf("INFORMACAO DE MORADA\n");
    printf("\tRua...........: %s\n", address.rua);
    printf("\tCodigo Postal1: %d\n", address.cod_postal1);
    printf("\tCodigo Postal2: %d\n", address.cod_postal2);
    printf("\tCodigo Postal3: %s\n", address.cod_postal3);
}

void print_confidencial(struct CONFID clubes){
    printf("INFORMACAO CONFIDENCIAL\n");
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
    printf("\nBASE DE DADOS ESTA VAZIA\n\n");
}

void mostrar_nss(BASEDADOS base){
    if(base.tamanho > 0){
        for(int i = 0; i < base.tamanho; i++){
            if(base.cidadaos[i].nss.num_serie != 0){
                print_nss(base.cidadaos[i].nss);
            }
        }
    }
    else
        base_vazia();
}

void mostrar_info_cidadao(BASEDADOS base, int nss){
    for(int i = 0; i < base.tamanho; i++){
        if(base.cidadaos[i].nss.num_serie == nss){
            print_cidadao(base.cidadaos[i]);
            return;
        }
    }
    printf("\nO Cidadao com NSS %d Nao existe\n", nss);
}

void modificar_cidadao(BASEDADOS *base, int nss){
    for(int i = 0; i < base->tamanho; i++){
        if(base->cidadaos[i].nss.num_serie == nss){
            le_info_pessoal(&(base->cidadaos[i].infp));
            le_info_number(&(base->cidadaos[i].infn));
            le_morada(&(base->cidadaos[i].address));
            le_confidencial(&(base->cidadaos[i].clubes));
            return;
        }
    }
    printf("\nCidadao com NSS %d nao existe\n", nss);
}

void novo_registo(BASEDADOS *base){
    if(base->tamanho <= MAX_CIDADAO){
        for(int i = 0; i < MAX_CIDADAO; i++){
            if(base->cidadaos[i].nss.num_serie == 0 && i != base->tamanho){
                le_cidadao(&(base->cidadaos[i]));    
                base->tamanho++;
                return;
            }
            else
                break;
        }
        le_cidadao(&(base->cidadaos[base->tamanho]));
        base->tamanho++;
    }
    else
        printf("\nA BASE DE DADOS ESTA CHEIA\n");
}

void apagar_registo(BASEDADOS *base, int nss){
    for(int i = 0; i < base->tamanho; i++){
        if(base->cidadaos[i].nss.num_serie == nss){
            base->cidadaos[i].nss.num_serie = 0;
            base->tamanho--;
            return;
        }
    }
    printf("\nCidadao com NSS %d, nao existe\n\n", nss);
}


void menu(char *opcao){
    printf("--------------------------------------------------------------------------\n");
    printf("|   /*********** PROGRAMA SIRP - Registo dos cidadaos **********/        |\n");
    printf("--------------------------------------------------------------------------\n");
    printf("|                                                                        |\n");
    printf("| a - Mostrar os numero de serie de todos os elementos da base de dados  |\n");
    printf("| b - Mostrar toda a informacao do cidadao com um certo numero (a pedir) |\n");
    printf("| c - Modificar a informacao do cidadao com um certo numero (a pedir)    |\n");
    printf("| d - Criar um novo registo para um novo cidadao                         |\n");
    printf("| e - Apagar o registo com um certo numero (a pedir)                     |\n");
    printf("| s - Sair do programa                                                   |\n");
    printf("|                                                                        |\n");
    printf("--------------------------------------------------------------------------\n");

    printf("Qual e a opcao: ");
    *opcao = getchar();
    clear_buffer();
}


// ########################## MAIN/START ###################
int main(){

    BASEDADOS basedados;
    int numero;
    char opcao;
    system("cls");
    incializar_base(&basedados);
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
                    le_inteiro(&numero, 1, 30000, "Digite o NSS a Ver: ");
                    mostrar_info_cidadao(basedados, numero);
                }
                else
                    base_vazia();
            break;
            case 'c': case 'C':
                if(basedados.tamanho > 0){
                    le_inteiro(&numero, 1, 30000, "Digite o NSS a Ver: ");
                    modificar_cidadao(&basedados, numero);
                }
                else
                    base_vazia();
            break;
            case 'd': case 'D':
                printf("\n");
                novo_registo(&basedados);
            break;
            case 'e': case 'E':
                if(basedados.tamanho > 0){
                    le_inteiro(&numero, 1, 30000, "Digite o NSS a Apagar: ");
                    apagar_registo(&basedados, numero);
                }
                else
                    base_vazia();
            break;
            case 's': case 'S':
                printf("\n|========= MUITO OBRIGADO ==========|\n");
                exit(0);
            break;
            default:
                printf("\nOPCAO INVALIDA\n\n");
        }
    }while(1);

    return 0;
}
