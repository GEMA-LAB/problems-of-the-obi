import java.util.Scanner;

public class estante {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long x = sc.nextLong();
        long y = sc.nextLong();
        long z = sc.nextLong();
        long n = sc.nextLong();

        System.out.println((x + y + z) % n);
    }
}
