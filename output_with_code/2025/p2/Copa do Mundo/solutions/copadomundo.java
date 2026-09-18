import java.util.Scanner;
import java.util.Arrays;

public class copadomundo {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();

        if (N == 1958 || N == 1962 || N == 1970 || N == 1994 || N == 2002) {
            System.out.println("S");
        } else {
            System.out.println("N");
        }
    }
}