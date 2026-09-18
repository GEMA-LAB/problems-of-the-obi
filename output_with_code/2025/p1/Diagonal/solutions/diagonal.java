import java.util.Scanner;
public class diagonal {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] a = new int[n + 1];
		int[] qtd = new int[n + 1];
		for(int i = 1; i <= n; i++) {
			a[i] = in.nextInt();
			if(a[i] > 0) {
                qtd[i]++;
                if(i + a[i] <= n) qtd[i + a[i]]--;
            }
		}
		long resp = 0;
		for(int i = 1; i <= n; i++) {
			qtd[i] += qtd[i - 1];
            resp = Math.max(resp, qtd[i]);
		}
		System.out.println(resp);
	}
}