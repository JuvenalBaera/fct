// import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.sql.*;
import java.time.LocalDate;
import java.util.NoSuchElementException;
import java.util.Scanner;

import com.mysql.cj.protocol.Resultset;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static Scanner scanner = new Scanner(System.in);
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

            // USER PROMPT
            // menuPrincipal();
            // usuarioOpcao();

            do{
                menu_principal();
                opcao = lerString("Qual opção: ");

                if(opcao.equals("s")){
                    sair = true;
                }
                else if(opcao.equals("i")){
                    // Inserir
                }
                else if(opcao.equals("a")){
                    // atualizar
                }
                else if(opcao.equals("l")){
                    usuario_requisito_funcional(conn);
                }
                else if(opcao.equals("d")){
                    // deletar
                }
                else{
                    mensagem_erro();
                }
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

    public static void mensagem_erro(){
        System.out.println("ERROOOOOOOOOOOOOOO");
    }

    public static void linha(int tamanho, char ch){
        for(int i = 0; i < tamanho; i++)
            System.out.printf("%c", ch);
        System.out.println();
    }


 

    // User
    public static int lerInteiro(String prompt){
        int num;
        System.out.print(prompt);
        num = scanner.nextInt();
        return num;
    }

    public static String lerString(String prompt){
        String str;
        System.out.print(prompt);
        str = scanner.next();
        return str;
    }

    public static LocalDate lerData(String prompt){
        String str = lerString(prompt);
        LocalDate data = LocalDate.parse(str);
        return data;
    }


    public static void menu_principal(){
        System.out.println("i \t-\t Inserir novo");
        System.out.println("a \t-\t atualizar");
        System.out.println("d \t-\t Deletar");
        System.out.println("l \t-\t Ler dados (RF's)");
        System.out.println("s \t-\t Sair");
    }

    public static void menu_requisito_funcional(){
        for(int i = 4; i <= 12; i++){
            System.out.printf("%2d \t-\t Requisito Funcional %d\n", i, i);
        }
        System.out.println(" v \t-\t Voltar");
        System.out.println(" s \t-\t Sair");
    }


    public static void usuario_requisito_funcional(Connection conn){
        String opcao, str_entrada;
        int int_entrada;
        LocalDate d_inicio, d_final;
        boolean sair = false;
        do{
            menu_requisito_funcional();
            opcao = lerString("Escolhe uma opçao: ");
            opcao = opcao.toLowerCase();

            System.out.println();
            if(opcao.equals("v")){
                sair = true;
            }
            else if(opcao.equals("s")){
                conn.close();
                System.exit(0);
            }
            else if(opcao.equals("4")){
                str_entrada = lerString("Introduza o tipo de instalação: ");
                requisito_funcional4(conn, str_entrada);
            }
            else if(opcao.equals("5")){
                str_entrada = lerString("Introduza o tipo de serviço: ");
                requisito_funcional5(conn, str_entrada);
            }
            else if(opcao.equals("6")){
                int_entrada = lerInteiro("Digite id do cliente: ");
                d_inicio = lerData("Data inicio [aaaa-mm-dd]: ");
                d_final =  lerData("Data fim    [aaaa-mm-dd]: ");
                requisito_funcional6(conn, int_entrada, d_inicio, d_final);
            }
            else if(opcao.equals("7")){
                int_entrada = lerInteiro("Digite id da instalação: ");
                d_inicio = lerData("Data inicio [aaaa-mm-dd]: ");
                d_final =  lerData("Data fim    [aaaa-mm-dd]: ");
                requisito_funcional7(conn, 22,  d_inicio, d_final, true);
            }
            else if(opcao.equals("8")){
                
            }
            else if(opcao.equals("9")){
                int_entrada = lerInteiro("Digite id da instalação: ");
                requisito_funcional9(conn, int_entrada);
            }
            else if(opcao.equals("10")){
                int_entrada = lerInteiro("Quantos top client queres ver: ");
                requisito_funcional10(conn, int_entrada);
            }
            else if(opcao.equals("11")){
                str_entrada = lerString("Introduza o tipo de serviço: ");
                requisito_funcional11(conn, str_entrada);
            }
            else if(opcao.equals("12")){

            }
            else{
                System.out.println("\nERRO: OPÇÃO INVÁLIDA\n");
            }
        }while(!sair);
        System.out.println("Obrigado\n");
    }


    // public static void messageReceived(String topic, MqttMessage message) {
    //     System.out.println("Message arrived. Topic: " + topic + " Message: " + message.toString());
    // }
}