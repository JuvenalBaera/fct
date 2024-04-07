// import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.sql.*;
import java.time.LocalDate;

import com.mysql.cj.protocol.Resultset;

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

            /* 
            requisito_funcional4(conn, "escritório");
            requisito_funcional5(conn, "Normal");
            requisito_funcional6(conn, 22,  LocalDate.of(2022, 01, 10), LocalDate.of(2028, 12, 31));
            requisito_funcional7(conn, 22,  LocalDate.of(2022, 01, 10), LocalDate.of(2028, 12, 31), true);
            requisito_funcional9(conn, 15);
            requisito_funcional10(conn, 5);
            */

            requisito_funcional11(conn, "Lowcost");
            requisito_funcional11(conn, "Normal");
            requisito_funcional11(conn, "Profissional");

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
        String sql;
        PreparedStatement preparedStatement;
        ResultSet resultSet;

        try{
            sql = """
                SELECT c.nome, c.endereco, c.nif, c.telefone, i.tipo  
                FROM cliente AS c 
                JOIN instalacao AS i ON c.id = i.cliente_id WHERE i.tipo = ?
            """;

            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setString(1, tipo_instalacao);
            resultSet = preparedStatement.executeQuery();

            if(!resultSet.isBeforeFirst()){
                System.out.printf("Não existe instalação do tipo: %s\n", tipo_instalacao);
            }
            else{
                linha(100, '-');
                System.out.printf("%-20s \t %-10s \t %-10s \t %-10s \t %-10s\n", "nome", "telefone", "nif", "tipo", "endereco");
                linha(100, '-');
                
                while(resultSet.next()){
                    System.out.printf("%-20s \t %s \t %s \t %s \t %s\n", 
                        resultSet.getString("nome"), 
                        resultSet.getString("telefone"),
                        resultSet.getString("nif"), 
                        resultSet.getString("tipo"), 
                        resultSet.getString("endereco") 
                    );
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

        try{
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
                    System.out.printf("%d \t %-25s \t %s \t %d\n", 
                        resultSet.getInt("id"), 
                        resultSet.getString("nome"), 
                        resultSet.getString("nivel"),
                        resultSet.getInt("qtd")
                    );
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
                SELECT i.id, d.data_instalacao, d.tipo FROM dispositivo AS d JOIN instalacao AS i
                ON d.instalacao_id = i.id WHERE i.id = ? AND d.data_instalacao BETWEEN ? AND ?;
            """;
            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setInt(1, id_instalacao);
            preparedStatement.setDate(2, Date.valueOf(d_inicio));
            preparedStatement.setDate(3, Date.valueOf(d_fim));   
            resultSet = preparedStatement.executeQuery();

            if(!resultSet.isBeforeFirst()){
                System.out.printf("Nenhum dispositivo com id %d instalado nesse intervalo (%s - %s)\n", 
                    id_instalacao,
                    String.valueOf(d_inicio),
                    String.valueOf(d_fim)
                );
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

    public static void requisito_funcional7(Connection conn, int cliente_id, LocalDate d_inicio, LocalDate d_fim, boolean estado){
        String sql;
        PreparedStatement preparedStatement;
        ResultSet resultSet;

        try{
            sql = """
                SELECT c.nome, AVG(f.preco) AS media FROM cliente AS c JOIN instalacao AS i 
                ON c.id = i.cliente_id JOIN contrato AS ct
                ON i.contrato_id = ct.id  JOIN faturacao AS f
                ON f.contrato_id = ct.id 
                WHERE c.id = ? AND f.estado = ?
                AND ct.data_inicio BETWEEN ? AND ?;
            """;

            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setInt(1, cliente_id);
            preparedStatement.setBoolean(2, estado);
            preparedStatement.setDate(3, Date.valueOf(d_inicio));
            preparedStatement.setDate(4, Date.valueOf(d_fim));
            resultSet = preparedStatement.executeQuery();

            if(!resultSet.isBeforeFirst()){
                System.out.println("Faturação não encontrado nesse intervalo");
            }
            else{
                linha(30, '-');
                System.out.printf("média \t %20s\n", "nome");
                linha(30, '-');
                while(resultSet.next()){
                    System.out.printf("%.2f \t %20s\n", 
                        resultSet.getFloat("media"), 
                        resultSet.getString("nome")
                    );
                }
                linha(30, '-');
            }
        }
        catch(SQLException e){
            e.printStackTrace();
        }
    }
    
    public static void requisito_funcional9(Connection conn, int id_instalacao){
        String sql;
        PreparedStatement preparedStatement;
        ResultSet resultSet;

        try{
            sql = """
                SELECT d.instalacao_id, d.id, d.tipo, d.data_instalacao 
                FROM instalacao AS i JOIN dispositivo AS d
                ON i.id = d.instalacao_id
                WHERE d.instalacao_id = ?;
            """;

            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setInt(1, id_instalacao);
            resultSet = preparedStatement.executeQuery();

            if(!resultSet.isBeforeFirst()){
                System.out.println("Nada encontrado nesse período ou instalação não existe");
            }
            else{
                linha(45, '-');
                System.out.printf("Inst. \t Disp. \t Tipo \t\t Data Inst.\n");
                linha(45, '-');
                while(resultSet.next()){
                    System.out.printf("%d \t %d \t %s \t %s\n",
                        resultSet.getInt("instalacao_id"),
                        resultSet.getInt("id"),
                        resultSet.getString("tipo"),
                        resultSet.getDate("data_instalacao").toString()
                    );
                }
                linha(45, '-');
            }
        }
        catch(SQLException e){
            e.printStackTrace();
        }
    }

    /* Top n clientes com mais instalações */
    public static void requisito_funcional10(Connection conn, int limite){
        String sql;
        PreparedStatement preparedStatement;
        ResultSet resultSet;

        try{
            sql = "SELECT * FROM top_clientes LIMIT ?;";

            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setInt(1, limite);
            resultSet = preparedStatement.executeQuery();

            if(!resultSet.isBeforeFirst()){
                System.out.println("Não foi encontrado cliente com instalação");
            }
            else{
                linha(43, '-');
                System.out.printf("Id \t %-20s \t Nr Inst.\n", "Nome Cliente");
                linha(43, '-');
                while(resultSet.next()){
                    System.out.printf("%d \t %-20s \t %d\n",
                    resultSet.getInt("id"),
                    resultSet.getString("nome"),
                    resultSet.getInt("nr_instalacao")
                    );
                }
                linha(43, '-');
            }
        }
        catch(SQLException e){
            e.printStackTrace();
        }
    }
    
    /* Número de serviço de um determinado tipo */
    public static void requisito_funcional11(Connection conn, String tipo_servico){
        String sql;
        PreparedStatement preparedStatement;
        ResultSet resultSet;

        try{
            sql = """
                SELECT COUNT(*) AS "nr_servico", s.nivel FROM cliente as c join instalacao as i 
                ON c.id = i.cliente_id JOIN contrato AS ct
                ON i.contrato_id = ct.id JOIN contrato_servico as cs
                ON ct.id = cs.contrato_id JOIN servico AS s
                ON cs.servico_id = s.id
                WHERE s.nivel = ?;     
            """;

            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setString(1, tipo_servico);
            resultSet = preparedStatement.executeQuery();

            if(!resultSet.isBeforeFirst()){
                System.err.println("Nenhum serviço com esse tipo foi achado: " + tipo_servico);
            }
            else{
                linha(22, '-');
                System.out.println("Total \t Tipo Serviço");
                linha(22, '-');
                while(resultSet.next()){
                    System.out.printf("%d \t %s\n", 
                    resultSet.getInt("nr_servico"),
                    resultSet.getString("nivel")
                    );
                }
                linha(22, '-');
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