package interacao;
public class Menu {
    public static void menu_principal(){
        System.out.println("-------- MENU PRINCIPAL ---------");
        System.out.println("i \t-\t Inserir novo");
        System.out.println("a \t-\t atualizar");
        System.out.println("d \t-\t Deletar");
        System.out.println("l \t-\t Ler dados (RF's)");
    }
    
    public static void menu_requisito_funcional(){
        System.out.println("-------------- MENU RF's --------------");
        for(int i = 4; i <= 12; i++){
            System.out.printf("rf%d \t-\t Requisito Funcional %d\n", i, i);
        }
        System.out.println("v \t-\t Voltar");
    }

    public static void menu_inserir(){
        System.out.println("---- Menu Inserir -----");
        System.out.println("cl \t-\t cliente");
        System.out.println("in \t-\t instalação");
        System.out.println("di \t-\t dispositivo");
        System.out.println("co \t-\t contrato");
        System.out.println("fa \t-\t faturação");
        System.out.println("v \t-\t voltar");
    }

    public static void menu_atualizar(){
        System.out.println("pf \t-\t Pagar factura");
        System.out.println("ai \t-\t Alugar instalação");
        System.out.println("ad \t-\t Activar dispositivo");
        System.out.println("id \t-\t Instalar dispositivo");
        System.out.println("v \t-\t voltar");
    }
}
