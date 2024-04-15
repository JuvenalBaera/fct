package dados;
import java.sql.*;
import java.time.LocalDate;
import java.util.HashMap;
import java.util.Random;

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
        String[] tipo_instalacao = {"apartamento", "casa", "escritório", "loja"};

        do{
            System.out.println("Escolha tipo de instalação: ");
            for(String inst : tipo_instalacao){
                System.out.printf("%c \t-\t %s\n", inst.charAt(0), inst);
            }

            tipo = Leitura.opcao_usuario();

            switch(tipo.charAt(0)){
                case 'a': tipo = tipo_instalacao[0]; break;
                case 'c': tipo = tipo_instalacao[1]; break;
                case 'e': tipo = tipo_instalacao[2]; break;
                case 'l': tipo = tipo_instalacao[3]; break;
                default: tipo = "0";
            }
        }while(tipo.equals("0"));

        endereco = Leitura.lerString("Endereço: ");

        try{
            sql = "INSERT INTO instalacao (tipo, endereco) VALUES (?, ?)";
            preparedStatement = conn.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, tipo);
            preparedStatement.setString(2, endereco);

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

        try{
            sql = "INSERT INTO dispositivo (modelo, tipo, data_instalacao, estado, especificacao) VALUES (?, ?, ?, 0, ?)";
            preparedStatement = conn.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, modelo);
            preparedStatement.setString(2, tipo);
            preparedStatement.setDate(3, Date.valueOf(data));
            preparedStatement.setString(4, especificacao);

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
        String[] niveis = {"Lowcost", "Normal", "Profissional"};
        String sql, nivel;
        LocalDate d_inicio, d_fim;
        boolean sair = false;
        int return_id = 0, nivel_id=0;

        do{
            System.out.println("------ Dados do contrato--------");
            d_inicio = Leitura.lerData("Data inicio [aaaa-mm-dd]: ");
            d_fim    = Leitura.lerData("Data fim    [aaaa-mm-dd]: ");

            if(d_fim.compareTo(d_inicio) > 0){
                sair = true;
            }
            else{
                System.out.println("Data inicial deve ser menor que final\n");
            }
        }while(!sair);
        
        do{
            System.out.println("\nEscolha nível do serviço: ");
            for(String n : niveis){
                System.out.printf("%c \t-\t %s\n", n.charAt(0), n);
            }

            nivel = Leitura.opcao_usuario();
            switch(nivel.charAt(0)){
                case 'l': nivel_id = 1; break;
                case 'n': nivel_id = 2; break;
                case 'p': nivel_id = 3; break;
                default: nivel = "0";
            }
        }while(nivel.equals("0"));

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
                    inserirContratoServico(conn, return_id, nivel_id);
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
        float preco;

        id_contrato = Leitura.lerInteiro("Id do contrato: ");
        if(!Verificar.existeId(conn, "contrato", id_contrato)){
            System.out.println("Contrato inexistente");
            return 0;
        }

        preco = Leitura.lerFloat("Valor da fatura: ");

        try{
            sql = "INSERT INTO faturacao (contrato_id, preco) VALUES (?, ?)";
            preparedStatement = conn.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
            preparedStatement.setInt(1, id_contrato);
            preparedStatement.setFloat(2, preco);

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
    
    private static void inserirContratoServico(Connection conn, int id_contrato, int id_servico){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        String sql;

        try{
            sql = "INSERT INTO contrato_servico (contrato_id, servico_id) VALUES (?, ?)";
            preparedStatement = conn.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
            preparedStatement.setInt(1, id_contrato);
            preparedStatement.setInt(2, id_servico);
            preparedStatement.executeUpdate();
        }
        catch(SQLException e){
            e.printStackTrace();
        }
    }
    
    private static void faturaAutomatico(Connection conn, int id_contrato, float preco){

        LocalDate data_atual = LocalDate.now();
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        String sql;

        try{
            sql = "INSERT INTO faturacao (contrato_id, preco) VALUES (?, ?)";
            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setInt(1, id_contrato);
            preparedStatement.setFloat(2, preco);

            if(preparedStatement.executeUpdate() == 0)
                System.out.println("Erro ao criar fatura");
            else
                System.out.println("Fatura criada");
        }
        catch(SQLException e){
            e.printStackTrace();
        }
    }

    public static void gerarFatura(Connection conn){
        LocalDate data_atual = LocalDate.now();
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        String sql;
        int contrato_id;
        float preco;
        Random random = new Random();

        if(data_atual.getDayOfMonth() == 2){
            try{
                sql = "SELECT * FROM contrato";
                preparedStatement = conn.prepareStatement(sql);
                resultSet = preparedStatement.executeQuery();

                while(resultSet.next()){
                    contrato_id = resultSet.getInt("id");
                    preco = Math.abs(20 + (random.nextInt() % (200 - 20)));
                    faturaAutomatico(conn, contrato_id, preco);
                }
            }
            catch(SQLException e){
                e.printStackTrace();
            }
        }
    }

    /*
    public static int inserirServico(Connection conn){
        PreparedStatement preparedStatement;
        ResultSet resultSet;
        int return_id = 0, nivel_id, id_contrato;
        String[] niveis = {"Lowcost", "Normal", "Profissional"};
        String nivel, sql;

        System.out.print("Digite id do contrato: ");
        id_contrato = Leitura.lerInteiro("Digite id do contrato: ");

        System.out.println("Escolha o nível do serviço: ");
        for(String n : niveis){
            System.out.printf("%c \t-\t %s\n", n.charAt(0), n);
        }

        do{
            nivel = Leitura.opcao_usuario();
            switch(nivel.charAt(0)){
                case 'l': nivel_id = 1; break;
                case 'n': nivel_id = 2; break;
                case 'p': nivel_id = 3; break;
                default: nivel = "0";
            }
        }while(nivel.equals("0"));

        try{
            sql = "INSERT INTO contrato_servico (contrato_id, servico_id) VALUES (?, ?)";
            preparedStatement = conn.prepareStatement(sql);
            preparedStatement.setString(1, id_contrato);
            preparedStatement.setString(2, nivel_id);
            return_id = preparedStatement.executeUpdate();
            return 1;
        }
        catch(SQLException e){
            e.printStackTrace();
        }
        return 0;
    }
    */
}
