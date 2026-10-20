import java.util.Scanner;
public class fotos {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		long[] a = new long[n + 1];
		long[] esq = new long[n + 1];
		long[] dir = new long[n + 1];
		int last = 0;
		for(int i = 1; i <= n; i++) {
			a[i] = in.nextInt();
			esq[i] = last;
			if(a[i] == 1) last = i;
		}
		last = n + 1;
		for(int i = n; i >= 1; i--) {
			dir[i] = last;
			if(a[i] == 1) last = i;
		}
		long resp = 0;
		for(int i = 1; i <= n; i++)
			if(a[i] == 1)
                resp += (i - esq[i]) * (dir[i] - 1 - i + 1);
		System.out.println(resp);
	}
}