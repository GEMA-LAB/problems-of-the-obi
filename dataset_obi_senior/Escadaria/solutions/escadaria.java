import java.util.Scanner;
public class escadaria {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] a = new int[n + 1];
		int[] esq = new int[n + 1];
		int[] dir = new int[n + 1];
		int last = -1;
		for(int i = 1; i <= n; i++) {
			a[i] = in.nextInt();
			esq[i] = last;
			if(a[i] != -1) last = i;
		}
		last = -1;
		for(int i = n; i >= 1; i--) {
			dir[i] = last;
			if(a[i] != -1) last = i;
		}
		for(int i = 1; i <= n; i++) {
			if(a[i] != -1) {
				System.out.print(a[i]);

				if(i != n) System.out.print(" ");
				else System.out.println();

				continue;
			}

			if(esq[i] == -1)
				System.out.print(a[dir[i]] + (dir[i] - i));
			else if(dir[i] == -1)
				System.out.print(a[esq[i]] + (i - esq[i]));
			else
				System.out.print(Math.min(a[esq[i]] + (i - esq[i]), a[dir[i]] + (dir[i] - i)));

			if(i != n) System.out.print(" ");
			else System.out.println();
		}
	}
}