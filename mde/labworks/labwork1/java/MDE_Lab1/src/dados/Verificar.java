package dados;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import interacao.Leitura;


public class Verificar {
    
    public static boolean existeId(Connection conn, String tabela, int id){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        String sql = "SELECT id FROM  " + tabela + " WHERE id = ?";

        try{
            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setInt(1, id);
            resultSet = preparedStatement.executeQuery();
            if(resultSet.next())
                return true;
        }
        catch(SQLException e){
            e.printStackTrace();
        }
        return false;
    }

    public static boolean instalacaoOcupada(Connection conn, int id_instalacao){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        String sql;

        try{
            sql = "SELECT * FROM instalacao WHERE id = ?";
            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setInt(1, id_instalacao);
            resultSet = preparedStatement.executeQuery();
            
            if(resultSet.next()){
                if(resultSet.getInt("cliente_id") != 0)
                    return true;
            }
        }
        catch(SQLException e){
            e.printStackTrace();
        }
        return false;
    }

    public static boolean faturaPaga(Connection conn, int id_fatura){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        String sql;

        try{
            sql = "SELECT * FROM faturacao WHERE id = ?";
            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setInt(1, id_fatura);
            resultSet = preparedStatement.executeQuery();
            
            if(resultSet.next()){
                if(resultSet.getInt("estado") == 1)
                    return true;
            }
        }
        catch(SQLException e){
            e.printStackTrace();
        }
        return false;
    }
}
