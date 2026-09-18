import java.util.Scanner;
import java.util.Arrays;

public class altura {
    public static int solve(int X) {
        if (X == 1) return 1;
        else if (X == 2) return 2;
        else if (X == 3) return 4;
        else if (X == 4) return 5;
        else if (X == 5) return 7;
        else {
            int ans = 13;
            while (X > 6) {
                ans += 6;
                X -= 1;
            }
            return ans;
        }
    }
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        int X = sc.nextInt();

        System.out.println(solve(X));
    }
}