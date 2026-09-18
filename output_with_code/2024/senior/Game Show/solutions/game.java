import java.util.Scanner;

public class game {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int n = scanner.nextInt();
    String instrucoes = scanner.next();
    scanner.close();
    
    int sala = 1;

    // Passa pelas instruções em ordem, atualizando a sala a cada passo
    for (int i = 0; i < instrucoes.length(); i++) {
      char instrucao = instrucoes.charAt(i);
      if (instrucao == 'E') {
        sala = 2 * sala;
      } else {
        sala = 2 * sala + 1;
      }
    }
    
    System.out.println(sala);
  }
}
