// OBI2021 - Fase 2
// Recorde

import java.util.Scanner;

public class recorde {

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int r, m, l;

    r = in.nextInt();
    m = in.nextInt();
    l = in.nextInt();

    if (r < m)
	System.out.println("RM");
    else
	System.out.println("*");

    if (r < l)
	System.out.println("RO");
    else
	System.out.println("*");
  }
}
