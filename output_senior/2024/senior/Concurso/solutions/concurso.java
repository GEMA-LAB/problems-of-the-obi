import java.util.*;

public class concurso
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), k = in.nextInt();
		int[] a = new int[n];
		for(int i = 0; i < n; i++) a[i] = in.nextInt();
		Arrays.sort(a);
		System.out.println(a[n - k]);
	}
}