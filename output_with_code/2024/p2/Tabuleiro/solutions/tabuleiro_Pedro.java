import java.util.Scanner;

public class Pedro {    
    public static void main(String[] args) {
        final int M = 1000 * 1000 * 1000 + 7;

        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        sc.close();

        long a = 0, b = 0, c = 1;
        for (int i = 0; i < n; ++i) {
            long x = c + 2 * (a + b);
            while (x >= M) x -= M;
            a = b;
            b = c;
            c = x;
        }

        System.out.println(c);
    }
}