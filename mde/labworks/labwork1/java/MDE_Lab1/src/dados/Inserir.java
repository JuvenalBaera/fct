package dados;
import java.sql.*;
import java.time.LocalDate;
import java.util.HashMap;

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

    public static int inserirInstalacao(Connection conn){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        String sql, tipo, endereco;
        int id_cliente, id_contrato, return_id=0;

        tipo = Leitura.lerString("Tipo da instalação: ");
        endereco = Leitura.lerString("Endereço: ");
        id_cliente = Leitura.lerInteiro("Id do cliente: ");
        id_contrato = Leitura.lerInteiro("Id do contrato: ");

        try{
            sql = "INSERT INTO instalacao (tipo, endereco, cliente_id, contrato_id) VALUES (?, ?, ?, ?)";
            preparedStatement = conn.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, tipo);
            preparedStatement.setString(2, endereco);
            preparedStatement.setInt(3, id_cliente);
            preparedStatement.setInt(4, id_contrato);

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

    public static int inserirDispositivo(Connection conn){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        String sql, modelo, tipo, especificacao;
        int id_instalacao, return_id=0;
        LocalDate data;
        HashMap<String, String> disp = new HashMap<>();
        disp.put("a", "16DC5E");
        disp.put("f", "16A631");
        disp.put("p", "6F3275");
        disp.put("t", "MQ9");
        disp.put("g", "DS18B20");
        
        do{
            System.out.println("A \t-\t Aquecedor");
            System.out.println("F \t-\t Frigorífico");
            System.out.println("P \t-\t Passadeira");
            System.out.println("T \t-\t Temperatura");
            System.out.println("G \t-\t GAS");

            tipo = Leitura.opcao_usuario();
            switch(tipo.charAt(0)){
                case 'a': tipo = disp.get("a"); break;
                case 'f': tipo = disp.get("f"); break;
                case 'p': tipo = disp.get("p"); break;
                case 't': tipo = disp.get("t"); break;
                case 'g': tipo = disp.get("g"); break;
                default: tipo = "0";
            }
        }while(tipo.equals("0"));

        modelo = Leitura.lerString("Modelo: ");
        especificacao = Leitura.lerString("especificacao: ");
        data = Leitura.lerData("Data da instalação: ");
        id_instalacao = Leitura.lerInteiro("Id da instalação: ");

        try{
            sql = "INSERT INTO dispositivo (modelo, tipo, data_instalacao, estado, especificacao, instalacao_id) VALUES (?, ?, ?, 0, ?, ?)";
            preparedStatement = conn.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, modelo);
            preparedStatement.setString(2, tipo);
            preparedStatement.setDate(3, Date.valueOf(data));
            preparedStatement.setString(4, especificacao);
            preparedStatement.setInt(5, id_instalacao);

            return_id = preparedStatement.executeUpdate();

            if(return_id != 0){
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
