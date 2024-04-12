package interacao;
import java.time.LocalDate;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Leitura {
    static Scanner scanner = new Scanner(System.in);
    
    // User
    public static int lerInteiro(String prompt){
        int num;
        System.out.print(prompt);
        num = scanner.nextInt();
        if(scanner.hasNextLine())
            scanner.nextLine();
        return num;
    }

    public static float lerFloat(String prompt){
        float num;
        System.out.print(prompt);
        num = scanner.nextFloat();
        return num;
    }

    public static String lerString(String prompt){
        String str;
        System.out.print(prompt);
        str = scanner.nextLine();
        return str;
    }

    public static LocalDate lerData(String prompt){
        String str = lerString(prompt);
        LocalDate data = LocalDate.parse(str);
        return data;
    }

    
    public static String opcao_usuario(){
        System.out.println("s \t-\t Sair\n");
        String opcao = lerString("Escolhe uma opçao: ");
        opcao = opcao.toLowerCase();
        System.out.println();
        return opcao;
    }
}
