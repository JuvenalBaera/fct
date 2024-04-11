package dados;
import java.sql.*;
import interacao.Leitura;

/*
 * 
 * import interacao.Leitura;
import interacao.Menu;
import interacao.Utilitario;
 */

public class Inserir {

    public static int inserirCliente(Connection conn){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        String nome, endereco, nif, telefone, sql;
        int return_id = 0;

        System.out.println("DIGITE OS SEGUINTES DADOS (CLIENTE)");
        nome     = Leitura.lerString("\tNome....: ");
        endereco = Leitura.lerString("\tEndereço: ");
        nif      = Leitura.lerString("\tNIF.....: ");
        telefone = Leitura.lerString("\tTelefone: ");

        try{
            sql = """
                INSERT INTO cliente (nome, endereco, nif, telefone)
                VALUES (?, ?, ?, ?);
            """;

            preparedStatement = conn.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, nome);
            preparedStatement.setString(2, endereco);
            preparedStatement.setString(3, nif);
            preparedStatement.setString(4, telefone);

            return_id = preparedStatement.executeUpdate();

            if(return_id > 0){
                resultSet = preparedStatement.getGeneratedKeys();
                if(resultSet.next()){
                    return_id = resultSet.getInt(1);
                }
            }
        }
        catch(SQLException e){
            e.printStackTrace();
        }
        return return_id;
    }

    public static int inserirInstalacao(Connection conn){
        
    }
}
