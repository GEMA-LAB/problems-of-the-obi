import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int n = input.nextInt();

        long[] a = new long[n + 1]; 
        long[] f = new long[n];
        long[] ans = new long[n];

        for (int i = 0; i < n; i++) a[i] = input.nextLong();
        a[n] = 1_000_000_000L;
        for (int i = 0; i < n; i++) f[i] = input.nextLong();

        ArrayList<Long> psum = new ArrayList<>();
        ArrayList<Long> last = new ArrayList<>();
        ArrayList<Long> sum = new ArrayList<>();

        psum.add(0L);
        last.add(1_000_000_000L);
        sum.add(0L);

        for (int i = n - 1; i >= 0; i--) {
            int sz = psum.size();
            int p = sz - (int) f[i] - 1;

            if (sz - 1 < f[i])  ans[i] = -1;
            else {
                long psumLast = psum.get(sz - 1);
                long sumLast = sum.get(sz - 1);
                ans[i] = psumLast - psum.get(p) - (long) p * (sumLast - sum.get(p));
            }

            while (a[i] >= last.get(last.size() - 1)) {
                psum.remove(psum.size() - 1);
                last.remove(last.size() - 1);
                sum.remove(sum.size() - 1);
            }

            sz = psum.size();
            psum.add(psum.get(sz - 1) + (long) sz * a[i]);
            last.add(a[i]);
            sum.add(a[i] + sum.get(sz - 1));
        }

        for (int i = 0; i < n; i++) {
            System.out.print(ans[i] + " ");
        }
        System.out.println();
    }
}
