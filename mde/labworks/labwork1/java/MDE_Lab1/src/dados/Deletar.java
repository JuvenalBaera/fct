package dados;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.SQLIntegrityConstraintViolationException;

import interacao.Leitura;

public class Deletar {
    public static boolean deletar(Connection conn, String tabela){
        PreparedStatement preparedStatement;
        int id;

        id = Leitura.lerInteiro("Digite o id " + tabela + ": ");
        String sql = "DELETE FROM " + tabela + " WHERE id = ?";
        try{
            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setInt(1, id);
            preparedStatement.executeUpdate();
            return true;
        }
        catch(SQLIntegrityConstraintViolationException e){
            System.out.println("ESSE ID ESTÁ SENDO USADO NOUTRA TABELA");
        }
        catch(SQLException e){
            e.printStackTrace();
        }
        return false;
    }
}
