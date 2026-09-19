import java.util.Scanner;

public class pinguins {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String e = sc.nextLine();
        char eA = e.charAt(0);
        char eB = e.charAt(2);
        float tA = sc.nextFloat();
        float tB = sc.nextFloat();

        if (eA == 'F') {
            tA = (tA - 32) * 5 / 9;
        }

        if (eB == 'F') {
            tB = (tB - 32) * 5 / 9;
        }

        if (tA < tB) {
            System.out.println("A");
        }
        else {
            System.out.println("B");
        }
    }
}
