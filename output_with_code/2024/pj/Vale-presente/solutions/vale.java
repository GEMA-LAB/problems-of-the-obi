import java.util.Scanner;
import java.math.BigDecimal;
import java.math.RoundingMode;

public class vale {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        if (n < 100) {
            System.out.println(n);
        } else {
            // double resultado = n * 0.15;

            // BigDecimal bd = new BigDecimal(resultado).setScale(2, RoundingMode.HALF_UP);
            System.out.println(n + 15);
        }
        sc.close();

    }
}
