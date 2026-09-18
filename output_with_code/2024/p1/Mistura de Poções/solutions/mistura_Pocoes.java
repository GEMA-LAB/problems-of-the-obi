import java.util.Scanner;

public class Pocoes {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(), k = sc.nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; ++i) {
            a[i] = sc.nextInt();
        }
        sc.close();

        int[] f = new int[n + 1];
        for (int i = 1; i <= n; ++i) f[i] = 0;

        long ans = 0;

        int p = 0, d = 0;
        for (int i = 0; i < n; ++i) {
            if (f[a[i]] == 0) ++d;
            ++f[a[i]];
            while (d >= k) {
                --f[a[p]];
                if (f[a[p]] == 0) --d;
                ++p;
            }
            ans += p;
        }

        System.out.println(ans);
    }
}
