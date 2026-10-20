import java.util.*;

public class frutasBrute {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    final int MAXN = 101;
    final int MAXT = 101;
    boolean[] comprei = new boolean[MAXT];  // Se já comprei fruta desse tipo
    int[] tipo = new int[MAXN];
    int[] preco = new int[MAXN];
    
    int dinheiro = scanner.nextInt();
    int numFrutas = scanner.nextInt();
    
    for (int i = 0; i < numFrutas; i++) {
      tipo[i] = scanner.nextInt();
      preco[i] = scanner.nextInt();
    }
    scanner.close();
    
    int resp = 0;

    while (true) {
      // Procuro a melhor fruta pra comprar
      int maisBarata = -1;
      for (int i = 0; i < numFrutas; i++) {
        if (comprei[tipo[i]]) {
          // Comprar tipo repetido é inútil
          continue;
        }
        if (maisBarata == -1 || preco[i] < preco[maisBarata]) {
          maisBarata = i;
        }
      }

      // Vejo se já acabou o dinheiro
      if (maisBarata == -1 || preco[maisBarata] > dinheiro) {
        break;
      }

      // Compro a fruta
      resp++;
      dinheiro -= preco[maisBarata];
      comprei[tipo[maisBarata]] = true;
    }
    
    System.out.println(resp);
  }
}