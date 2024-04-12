// import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.sql.*;
import java.time.LocalDate;

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
                    // Inserir
                    // System.out.println("Inserir");
                    inserir_dados(conn);
                }
                else if(opcao.equals("a")){
                    System.out.println("Atualizar");
                    // atualizar
                }
                else if(opcao.equals("l")){
                    usuario_requisito_funcional(conn);
                }
                else if(opcao.equals("d")){
                    // deletar
                    System.out.println("Apagar");
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
            else if(opcao.equals("in")){}
            else if(opcao.equals("di")){}
            else if(opcao.equals("co")){
                int_entrada = Inserir.inserirContrato(conn);
                if(int_entrada != 0){
                    System.out.printf("Contrato inserido id: %d\n", int_entrada);
                }
                else{
                    System.out.println("Erro ao inserir contrato");
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
            else if(opcao.equals("cs")){
                int_entrada = Inserir.inserirContratoServico(conn);
                if(int_entrada != 0){
                    System.out.printf("Contrato serviço inserido, id: %d\n", int_entrada);
                }
                else{
                    System.out.println("Erro ao inserir CS");
                }
            }
            else if(opcao.equals("se")){
                int_entrada = Inserir.inserirServico(conn);
                if(int_entrada != 0){
                    System.out.printf("Serviço inserido com sucesso, id: %d\n", int_entrada);
                }
                else{
                    System.err.println("Erro ao inserir serviço");
                }
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
                System.out.println("PORRR FAZERRRRRRRRRRRRRRR 12");
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