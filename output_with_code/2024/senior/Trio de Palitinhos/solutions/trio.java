import java.util.*;

public class trio
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

    for (int i = 0; i < n; i++) {
      int l = 0;
      for (int r = i - 1; r >= 1; r--) {
        while (l < r && v[l] + v[r] <= v[i]) {
          l++;
        }
        if (l < r) {
          resp += (r - l);
        }
      }
    }

    System.out.println(resp);
  }
}
