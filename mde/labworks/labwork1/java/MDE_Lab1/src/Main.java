
import java.sql.*;
import java.time.LocalDate;

import dados.Atualizar;
import dados.Deletar;
import dados.Inserir;
import interacao.Leitura;
import interacao.Menu;
import interacao.Utilitario;

public class Main {
    
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        // TIP Press <shortcut actionId="ShowIntentionActions"/> with your caret at the highlighted text
        // to see how IntelliJ IDEA suggests fixing it.
        System.out.println("MDE Lab1 - Welcome to the Java Project");

        //Database information
        // String url = "jdbc:mysql://192.168.1.67/test?useSSL=false";
        String url = "jdbc:mysql://localhost/labwork1?useSSL=false";
        String username = "root";   //Replace with your database username
        String password = "";       //Replace with user password

        //For testing only the MQTT connection, comment until start the MQTT part
        //Test database integration
        try {
            //Start Connection
            Connection conn = MySQL_Integration.createConnection(url,username,password);
            
            String opcao;
            boolean sair = false;
            /* 
            requisito_funcional4(conn, "escritório");
            requisito_funcional5(conn, "Normal");
            requisito_funcional6(conn, 22,  LocalDate.of(2022, 01, 10), LocalDate.of(2028, 12, 31));
            requisito_funcional7(conn, 22,  LocalDate.of(2022, 01, 10), LocalDate.of(2028, 12, 31), true);
            requisito_funcional9(conn, 15);
            requisito_funcional10(conn, 5);
            requisito_funcional11(conn, "Lowcost");
            requisito_funcional11(conn, "Normal");
            requisito_funcional11(conn, "Profissional");
            */


            do{
                Menu.menu_principal();
                opcao = Leitura.opcao_usuario();

                if(opcao.equals("s")){
                    sair = true;
                }
                else if(opcao.equals("i")){
                    inserir_dados(conn);
                }
                else if(opcao.equals("a")){
                    atualizar_dados(conn);
                }
                else if(opcao.equals("l")){
                    usuario_requisito_funcional(conn);
                }
                else if(opcao.equals("d")){
                    deletar_dados(conn);
                }
                else{
                    Utilitario.mensagem_erro();
                }
                System.out.println();
            }while(!sair);
            System.out.println("Obrigado\n");


            //Close Connection
            MySQL_Integration.closeConnection(conn);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        //MQTT Broker information
        //ATTENTION!!!
        //Comment the following line for testing WITHOUT real data
        //String broker = "tcp://192.168.250.201:1883";

        //Start Subscription
        //ATTENTION!!!
        //Comment the following line for testing WITHOUT real data
        //MQTTLibrary.createSubscriber(broker);
    }
 

    public static void fechar_conexao(Connection conn){
        try{
            conn.close();
        }
        catch(SQLException e){
            e.printStackTrace();
        }
    }

    public static void inserir_dados(Connection conn){
        String opcao, str_entrada;
        int int_entrada;
        LocalDate d_inicio, d_fim;
        boolean sair = false;

        do{
            Menu.menu_inserir();
            opcao = Leitura.opcao_usuario();

            if(opcao.equals("s")){
                fechar_conexao(conn);
                System.exit(0);
            }
            else if(opcao.equals("v")){
                sair = true;
            }
            else if(opcao.equals("cl")){
                int_entrada = Inserir.inserirCliente(conn);
                if(int_entrada != 0){
                    System.out.printf("Cliente inserido com sucesso, id : %d\n", int_entrada);
                }
                else{
                    System.out.println("Erro ao inserir cliente");
                }
            }
            else if(opcao.equals("in")){
                int_entrada = Inserir.inserirInstalacao(conn);
                if(int_entrada != 0){
                    System.out.printf("Instalação inserido, id: %d\n", int_entrada);
                }
                else{
                    System.out.println("ERRO AO INSERIR INSTALAÇÃO");
                }
            }
            else if(opcao.equals("di")){
                int_entrada = Inserir.inserirDispositivo(conn);
                if(int_entrada != 0){
                    System.out.printf("Dispositivo inserido: %d\n", int_entrada);
                }
                else{
                    System.out.println("ERRO AO INSERIR DISPOSITIVO");
                }
            }
            else if(opcao.equals("fa")){
                int_entrada = Inserir.inserirFaturacao(conn);
                if(int_entrada != 0){
                    System.out.printf("Faturação id: %d\n", int_entrada);
                }
                else{
                    System.out.println("Erro ao emitir a fatura");
                }
            }
            System.out.println();
        }while(!sair);
    }

    public static void atualizar_dados(Connection conn){
        String opcao, str_entrada;
        int int_entrada;
        boolean sair = false;

        do{
            Menu.menu_atualizar();
            opcao = Leitura.opcao_usuario();

            if(opcao.equals("s")){
                fechar_conexao(conn);
                System.exit(0);
            }
            else if(opcao.equals("v")){
                sair = true;
            }
            else if(opcao.equals("pf")){
                if(Atualizar.pagarFactura(conn)){
                    System.out.println("Fatura pago com sucesso");
                }
                else{
                    System.out.println("Erro ao pagar a factura");
                }
            }
            else if(opcao.equals("ai")){
                int_entrada = Atualizar.alugarInstalacao(conn);
                if(int_entrada == -1){
                    System.out.println("Cliente inexistente");
                }
                else if(int_entrada == 1){
                    System.out.println("Erro ao pagar a factura");
                }
                else{
                    System.out.printf("Id do contrato: %d\n", int_entrada);
                }
            }
            else if(opcao.equals("ad")){
                Atualizar.activarDispositivo(conn);
            }
            else if(opcao.equals("id")){
                Atualizar.instalarDispositivo(conn);
            }
            System.out.println();
        }while(!sair);
    }

    public static void deletar_dados(Connection conn){
        String opcao;
        boolean sair = false;
        int int_entrada;

        do{
            Menu.menu_inserir();
            opcao = Leitura.opcao_usuario();

            if(opcao.equals("s")){
                fechar_conexao(conn);
                System.exit(0);
            }
            else if(opcao.equals("v")){
                sair = true;
            }
            else if(opcao.equals("cl")){
                if(Deletar.deletar(conn, "cliente"))
                    System.out.println("Cliente apagado");
                else
                    System.out.println("ERRO AO APAGAR CLIENTE");
            }
            else if(opcao.equals("in")){
                if(Deletar.deletar(conn, "instalacao"))
                    System.out.println("Instalação apagada");
                else
                    System.out.println("ERRO AO APAGAR INSTALAÇÃO");
            }
            else if(opcao.equals("di")){
                if(Deletar.deletar(conn, "dispositivo"))
                    System.out.println("dispositivo apagado");
                else
                    System.out.println("ERRO AO APAGAR O DISPOSITIVO");
            }
            else if(opcao.equals("co")){
                if(Deletar.deletar(conn, "contrato"))
                    System.out.println("Contrato apagado");
                else
                    System.out.println("ERRO AO APAGAR O CONTRATO");
            }
            else if(opcao.equals("fa")){
                if(Deletar.deletar(conn, "faturacao"))
                    System.out.println("Fatura apagada");
                else
                    System.out.println("ERRO AO APAGAR A FACTURA");
            }
            System.out.println();
        }while(!sair);
    }

    public static void usuario_requisito_funcional(Connection conn){
        String opcao, str_entrada;
        int int_entrada;
        LocalDate d_inicio, d_final;
        boolean sair = false;
        do{
            Menu.menu_requisito_funcional();
            opcao = Leitura.opcao_usuario(); 
            
            if(opcao.equals("v")){
                sair = true;
            }
            else if(opcao.equals("s")){
                fechar_conexao(conn);
                System.exit(0);
            }
            else if(opcao.equals("rf4")){
                str_entrada = Leitura.lerString("Introduza o tipo de instalação: ");
                MySQL_Integration.requisito_funcional4(conn, str_entrada);
            }
            else if(opcao.equals("rf5")){
                str_entrada = Leitura.lerString("Introduza o tipo de serviço: ");
                MySQL_Integration.requisito_funcional5(conn, str_entrada);
            }
            else if(opcao.equals("rf6")){
                int_entrada = Leitura.lerInteiro("Digite id do cliente: ");
                d_inicio = Leitura.lerData("Data inicio [aaaa-mm-dd]: ");
                d_final =  Leitura.lerData("Data fim    [aaaa-mm-dd]: ");
                MySQL_Integration.requisito_funcional6(conn, int_entrada, d_inicio, d_final);
            }
            else if(opcao.equals("rf7")){
                int_entrada = Leitura.lerInteiro("Digite id da instalação: ");
                d_inicio = Leitura.lerData("Data inicio [aaaa-mm-dd]: ");
                d_final =  Leitura.lerData("Data fim    [aaaa-mm-dd]: ");
                MySQL_Integration.requisito_funcional7(conn, 22,  d_inicio, d_final, true);
            }
            else if(opcao.equals("rf8")){
                System.out.println("PORRR FAZERRRRRRRRRRRRRRR 8");
            }
            else if(opcao.equals("rf9")){
                int_entrada = Leitura.lerInteiro("Digite id da instalação: ");
                MySQL_Integration.requisito_funcional9(conn, int_entrada);
            }
            else if(opcao.equals("rf10")){
                int_entrada = Leitura.lerInteiro("Quantos top client queres ver: ");
                MySQL_Integration.requisito_funcional10(conn, int_entrada);
            }
            else if(opcao.equals("rf11")){
                str_entrada = Leitura.lerString("Introduza o tipo de serviço: ");
                MySQL_Integration.requisito_funcional11(conn, str_entrada);
            }
            else if(opcao.equals("rf12")){
                int_entrada = Leitura.lerInteiro("Digite id do cliente: ");
                MySQL_Integration.requisito_funcional12(conn, int_entrada);
            }
            else{
                Utilitario.mensagem_erro();
            }
            System.out.println();
        }while(!sair);
    }


    // public static void messageReceived(String topic, MqttMessage message) {
    //     System.out.println("Message arrived. Topic: " + topic + " Message: " + message.toString());
    // }
}