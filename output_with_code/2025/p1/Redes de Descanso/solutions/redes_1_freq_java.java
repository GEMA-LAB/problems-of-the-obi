import java.util.Scanner;

public class redes_1_freq_java {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int maxa = 100000;

    int n = in.nextInt();
    int[] freq = new int[maxa + 1];
    for (int i = 0; i < n; i++) {
        int alt = in.nextInt();
        freq[alt]++;
    }

    int resp = 0;
    for (int i = 1; i <= maxa; i++) {
        resp += freq[i] / 2;
    }
    System.out.println(resp);
  }
}
