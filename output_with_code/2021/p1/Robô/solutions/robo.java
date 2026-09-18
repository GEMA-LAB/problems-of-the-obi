import java.util.Scanner;

public class robo {

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int n = in.nextInt();
    int c = in.nextInt();
    int p = in.nextInt();

    int pos = 1, res = 0;

    for (int i = 0; i < c; ++i) {
      if (pos == p) {
        res++;
      }

      pos += in.nextInt();

      if (pos > n) {
        pos = 1;
      } else if (pos == 0) {
        pos = n;
      }
    }

    if (pos == p) {
      res++;
    }

    System.out.println(res);
  }
}
