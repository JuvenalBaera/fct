package dados;
import java.sql.*;
import java.time.LocalDate;

import interacao.Leitura;
import interacao.Utilitario;

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

    // public static int inserirInstalacao(Connection conn){}
    // public static int inserirDispositivo(Connection conn){}
    public static int inserirContrato(Connection conn){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        String sql;
        LocalDate d_inicio, d_fim;
        boolean sair = false;
        int return_id = 0;

        do{
            d_inicio = Leitura.lerData("Data inicio [aaaa-mm-dd]: ");
            d_fim    = Leitura.lerData("Data fim    [aaaa-mm-dd]: ");

            if(d_fim.compareTo(d_inicio) > 0){
                sair = true;
            }
            else{
                System.out.println("Data inicial deve ser menor que final\n");
            }
        }while(!sair);

        try{
            sql = "INSERT INTO contrato (data_inicio, data_fim) VALUES (?, ?)";
            preparedStatement = conn.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
            preparedStatement.setDate(1, Date.valueOf(d_inicio));
            preparedStatement.setDate(2, Date.valueOf(d_fim));
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

    public static int inserirFaturacao(Connection conn){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        String sql;

        int return_id = 0, id_contrato;
        LocalDate data;
        float preco;

        data = Leitura.lerData("Data limite da fatura: ");
        id_contrato = Leitura.lerInteiro("Id do contrato: ");
        preco = Leitura.lerFloat("Valor da fatura: ");


        try{
            sql = "INSERT INTO faturacao (data, estado, contrato_id, preco) VALUES (?, 0, ?, ?)";
            preparedStatement = conn.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
            preparedStatement.setDate(1, Date.valueOf(data));
            preparedStatement.setInt(2, id_contrato);
            preparedStatement.setFloat(3, preco);

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
    
    public static int inserirContratoServico(Connection conn){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        String sql;
        int return_id = 0, id_contrato, id_servico;

        id_contrato = Leitura.lerInteiro("Digite id do contrato: ");
        id_servico = Leitura.lerInteiro("Digite id do serviço: ");

        try{
            sql = "INSERT INTO contrato_servico (contrato_id, servico_id) VALUES (?, ?)";
            preparedStatement = conn.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
            preparedStatement.setInt(1, id_contrato);
            preparedStatement.setInt(2, id_servico);

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

    public static int inserirServico(Connection conn){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        int return_id = 0;
        String[] niveis = {"Lowcost", "Normal", "Profissional"};
        String nivel, sql;

        System.out.println("Escolha o nível do serviço: ");
        for(String n : niveis){
            System.out.printf("%c \t-\t %s\n", n.charAt(0), n);
        }

        do{
            nivel = Leitura.opcao_usuario();
            switch(nivel.charAt(0)){
                case 'l': nivel = niveis[0]; break;
                case 'n': nivel = niveis[1]; break;
                case 'p': nivel = niveis[2]; break;
                default: nivel = "0";
            }
        }while(nivel.equals("0"));

        try{
            sql = "INSERT INTO servico (nivel) VALUES (?)";
            preparedStatement = conn.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, nivel);
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
}
