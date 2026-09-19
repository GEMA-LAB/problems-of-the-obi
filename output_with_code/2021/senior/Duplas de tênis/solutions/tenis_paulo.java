import java.util.Scanner;
import java.lang.Math;

public class paulo {

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int a = in.nextInt();
    int b = in.nextInt();
    int c = in.nextInt();
    int d = in.nextInt();

    System.out.println(Math.abs(a+d-b-c));
  }
}
