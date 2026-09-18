import java.util.*;

public class empregos {
    static final int N = 100010;
    static long[] a = new long[N];
    static long[] b = new long[N];
    static long[] suf = new long[N + 2];

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int k = sc.nextInt();

        PriorityQueue<Long> pq = new PriorityQueue<>();

        long ans = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = sc.nextLong();
        }
        for (int i = 1; i <= n; i++) {
            b[i] = sc.nextLong();
            ans += Math.max(a[i], b[i]);
        }

        for (int i = n; i >= 1; i--) {
            suf[i] = suf[i + 1] + Math.max(a[i], 2 * b[i]);
        }

        long sum = 0, sumans = 0;
        if (k == 0) {
            System.out.println(suf[1]);
            sc.close();
            return;
        }

        for (int i = 1; i <= n; i++) {
            long diff = b[i] - a[i];
            pq.add(diff);
            sum += diff;
            sumans += a[i];

            if (pq.size() > k) {
                long val = pq.poll();
                sum -= val;
            }

            if (pq.size() == k) {
                ans = Math.max(ans, sumans + sum + suf[i + 1]);
            }
        }

        System.out.println(ans);
        sc.close();
    }
}
