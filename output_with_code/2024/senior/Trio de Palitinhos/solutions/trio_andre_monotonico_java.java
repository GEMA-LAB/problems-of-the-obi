import java.util.*;

public class andre_monotonico_java
{
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int n = scanner.nextInt();
    int[] v = new int[n];

    for (int i = 0; i < n; i++) {
      v[i] = scanner.nextInt();
    }

    Arrays.sort(v);

    long resp = 0;

    for (int i = 0; i <= n - 3; i++) {
      int k = i + 2;
      for (int j = i + 1; j <= n - 2; j++) {
        k = Math.max(k, j + 1);
        while (k < n && v[i] + v[j] > v[k]) {
          k++;
        }
        resp += (k - 1) - j;
      }
    }

    System.out.println(resp);
  }
}
