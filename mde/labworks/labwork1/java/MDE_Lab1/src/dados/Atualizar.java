package dados;

import java.sql.*;

import interacao.Leitura;


public class Atualizar {

    public static boolean pagarFactura(Connection conn){
        PreparedStatement preparedStatement;
        String sql;
        int id_factura;

        id_factura = Leitura.lerInteiro("Id da fatura: ");

        if(!Verificar.existeId(conn, "faturacao", id_factura)){
            System.out.println("Fatura inexistente");
            return false;
        }

        if(Verificar.faturaPaga(conn, id_factura)){
            System.out.println("Esta fatura já foi pago antes");
            return false;
        }

        try{
            sql = "UPDATE faturacao SET estado = 1 WHERE id = ?";
            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setInt(1, id_factura);
            preparedStatement.executeUpdate();
            return true;
        }
        catch(SQLException e){
            e.printStackTrace();
        }
        return false;
    }

    public static int alugarInstalacao(Connection conn){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        int id_cliente, id_contrato, id_instalacao;
        String sql;

        id_cliente = Leitura.lerInteiro("Digite id do cliente: ");
        if(!Verificar.existeId(conn, "cliente", id_cliente)){
            System.out.println("Cliente inexistente");
            return 0;
        }

        id_instalacao = Leitura.lerInteiro("Digite id da instalação: ");
        if(!Verificar.existeId(conn, "instalacao", id_instalacao)){
            System.out.println("Instalação inexistente");
            return 0;
        }

        if(Verificar.instalacaoOcupada(conn, id_instalacao)){
            System.out.println("Instalção já alugada");
            return 0;
        }

        id_contrato = Inserir.inserirContrato(conn);
        if(id_contrato != 0){
            try{
                sql = "UPDATE instalacao SET cliente_id=?, contrato_id=? WHERE id=?";
                preparedStatement = conn.prepareStatement(sql);
                preparedStatement.setInt(1, id_cliente);
                preparedStatement.setInt(2, id_contrato);
                preparedStatement.setInt(3, id_instalacao);

                preparedStatement.executeUpdate();
                return id_contrato;
            }
            catch(SQLException e){
                e.printStackTrace();
            }
        }
        System.out.println("Erro ao inserir contrato");
        return 0;
    }

    public static int dispositoNaInstalacao(Connection conn){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        int id_cliente, id_contrato, id_instalacao;
        String sql;

        id_cliente = Leitura.lerInteiro("Digite id do cliente: ");
        if(!Verificar.existeId(conn, "cliente", id_cliente)){
            System.out.println("Cliente inexistente");
            return 0;
        }
    }
}
