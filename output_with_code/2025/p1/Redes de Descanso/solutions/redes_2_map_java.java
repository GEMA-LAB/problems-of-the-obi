import java.util.Scanner;
import java.util.TreeMap;

public class redes_2_map_java {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    TreeMap<Integer, Integer> freq = new TreeMap<>();

    int n = in.nextInt();
    for (int i = 0; i < n; i++) {
        int alt = in.nextInt();
        if (!freq.containsKey(alt)) {
          freq.put(alt, 1);
        } else {
          freq.put(alt, freq.get(alt) + 1);
        }
    }

    int resp = 0;
    for (int i = 1; i <= 100000; i++) {
      if (freq.containsKey(i)) {
        resp += freq.get(i) / 2;
      }
    }
    System.out.println(resp);
  }
}
