// import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.sql.*;
import java.time.LocalDate;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
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

            // requisito_funcional4(conn, "escritório");
            // requisito_funcional5(conn, "Normal");
            // "2022-01-01", "2028-12-31"
            requisito_funcional6(conn, 22,  LocalDate.of(2022, 01, 10), 
                                            LocalDate.of(2028, 12, 31));

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

    public static void linha(int tamanho, char ch){
        for(int i = 0; i < tamanho; i++)
            System.out.printf("%c", ch);
        System.out.println();
    }


    public static void requisito_funcional4(Connection conn, String tipo_instalacao){
        String sql = """
            SELECT c.nome, c.endereco, c.nif, c.telefone, i.tipo  
            FROM cliente as c 
            JOIN instalacao AS i ON c.id = i.cliente_id WHERE i.tipo = ?
        """;

        try{
            PreparedStatement preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setString(1, tipo_instalacao);

            ResultSet resultSet = preparedStatement.executeQuery();
            String nome, endereco, nif, telefone, tipo;

            if(!resultSet.isBeforeFirst()){
                System.out.printf("Não existe instalação do tipo: %s\n", tipo_instalacao);
            }
            else{
                linha(100, '-');
                System.out.printf("%-20s  %-10s \t %-10s \t %s \t %-10s\n", "nome", "telefone", "nif", "tipo", "endereco");
                linha(100, '-');
                
                while(resultSet.next()){
                    nome = resultSet.getString("nome");
                    endereco = resultSet.getString("endereco");
                    telefone = resultSet.getString("telefone");
                    nif = resultSet.getString("nif");
                    tipo = resultSet.getString("tipo");
                    System.out.printf("%-20s \t %s \t %s \t %s \t %s\n", nome, telefone, nif, tipo, endereco);
                }   
                linha(100, '-');
            }
        }
        catch(SQLException e){
            e.printStackTrace();
        }
    }

    public static void requisito_funcional5(Connection conn, String tipo_servico){

        String sql;
        PreparedStatement preparedStatement;
        ResultSet resultSet;

        sql = """
            SELECT c.id, c.nome, s.nivel, COUNT(*) AS qtd FROM cliente AS c JOIN instalacao AS i 
            on c.id = i.cliente_id JOIN contrato AS ct
            ON i.contrato_id = ct.id JOIN contrato_servico AS cs
            ON ct.id = cs.contrato_id JOIN servico AS s
            ON cs.servico_id = s.id
            where s.nivel = ?
            GROUP BY c.id
            ORDER BY qtd DESC
        """;

        try{
            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setString(1, tipo_servico);
            resultSet = preparedStatement.executeQuery();

            if(!resultSet.isBeforeFirst()){
                System.out.printf("Não foi encontrado um serviçço de nível: %s\n", tipo_servico);
            }
            else{
                linha(60, '-');
                System.out.printf("id \t %-25s \t %s \t Qtd\n", "Nome", "Tipo Sercviço");
                linha(60, '-');
                while(resultSet.next()){
                    System.out.printf("%d \t %-25s \t %s \t %d\n", resultSet.getInt("id"), 
                    resultSet.getString("nome"), 
                    resultSet.getString("nivel"),
                    resultSet.getInt("qtd"));
                }
                linha(60, '-');
            }
        }
        catch(SQLException e){
            e.printStackTrace();
        }
    }

    public static void requisito_funcional6(Connection conn, int id_instalacao, LocalDate d_inicio, LocalDate d_fim){

        String sql;
        PreparedStatement preparedStatement;
        ResultSet resultSet;

        try{
            sql = """
                select i.id, d.data_instalacao, d.tipo from dispositivo as d join instalacao as i
                on d.instalacao_id = i.id where i.id = ? and d.data_instalacao between ? and ?;
            """;
            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setInt(1, id_instalacao);
            preparedStatement.setDate(2, Date.valueOf(d_inicio));
            preparedStatement.setDate(3, Date.valueOf(d_fim));
            

            resultSet = preparedStatement.executeQuery();

            if(!resultSet.isBeforeFirst()){
                System.out.printf("Nenhum dispositivo com id %d instalado nesse intervalo (%s - %s)\n", id_instalacao,
                                                                                    String.valueOf(d_inicio),
                                                                                    String.valueOf(d_fim));
            }
            else{
                linha(32, '-');
                System.out.printf("id \t d_Instalação \t tipo\n");
                linha(32, '-');
                while(resultSet.next()){
                    System.out.printf("%d \t %s \t %s\n", resultSet.getInt("id"), 
                    resultSet.getDate("data_instalacao").toString(),
                    resultSet.getString("tipo"));
                }
                linha(32, '-');
            }
        }
        catch(SQLException e){
            e.printStackTrace();
        }
    }

    // public static void messageReceived(String topic, MqttMessage message) {
    //     System.out.println("Message arrived. Topic: " + topic + " Message: " + message.toString());
    // }
}