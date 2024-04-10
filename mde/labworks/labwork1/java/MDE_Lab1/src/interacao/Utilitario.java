package interacao;
public class Utilitario {
    public static void linha(int tamanho, char ch){
        for(int i = 0; i < tamanho; i++)
            System.out.printf("%c", ch);
        System.out.println();
    }

    public static void mensagem_erro(){
        System.out.println("ERROOOOOOOOOOOOOOO");
    }
    
}
