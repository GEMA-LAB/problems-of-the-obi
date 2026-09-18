import java.util.*;
public class distintos {
  static int[] v = new int[100010];
  static int[] f = new int[100010];
  static int[] prox = new int[100010];
  
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		for(int i = 0; i < n; i++) {
		  v[i] = in.nextInt();
		  prox[v[i]] = n;
		}
		f[n - 1] = n - 1;
    prox[v[n - 1]] = n - 1;
    int resp = 1;
    for(int i = n - 2; i >= 0; i--) {
      f[i] = Math.min(f[i + 1], prox[v[i]] - 1);
      prox[v[i]] = i;
      resp = Math.max(resp, f[i] - i + 1);
    }
		System.out.println(resp);
	}
}
