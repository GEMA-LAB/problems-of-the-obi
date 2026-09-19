import java.util.*;

public class frutas {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int dinheiro = scanner.nextInt();
    int numFrutas = scanner.nextInt();
    
    // Guarda as frutas em uma lista
    List<int[]> frutas = new ArrayList<>();
    for (int i = 0; i < numFrutas; i++) {
      int tipo = scanner.nextInt();
      int preco = scanner.nextInt();
      frutas.add(new int[]{preco, tipo});
    }
    scanner.close();
    
    // Ordena por preço
    frutas.sort(Comparator.comparingInt(a -> a[0]));
    
    // Se já comprei fruta desse tipo
    boolean[] comprei = new boolean[101];
    int resp = 0;
    
    for (int[] fruta : frutas) {
      int preco = fruta[0];
      int tipo = fruta[1];
      if (comprei[tipo]) {
        // Comprar tipo repetido é inútil
        continue;
      }
      if (preco > dinheiro) {
        // Todos daqui pra frente vão ser mais caros do que meu dinheiro
        break;
      }
      // Compro a fruta
      resp++;
      dinheiro -= preco;
      comprei[tipo] = true;
    }
    
    System.out.println(resp);
  }
}
