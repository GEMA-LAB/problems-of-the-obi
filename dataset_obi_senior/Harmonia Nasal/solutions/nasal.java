import java.util.*;
public class nasal {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int k = in.nextInt();
		int[] a = new int[n];
		int[] b = new int[n];
		for(int i = 0; i < n; i++) a[i] = in.nextInt();
		long resp = 0;
		ArrayList<Integer> melhores = new ArrayList<Integer>();
		for(int i = 1; i <= k + 1; i++) melhores.add(0);
		for(int i = 0; i < n; i++) {
		    b[i] = in.nextInt();
		    if(a[i] >= b[i]) {
                resp += a[i]-b[i];
                melhores.add(b[i]);
            }
            else {
                melhores.add(a[i]);
            }
		}
		Collections.sort(melhores);
		for(int i = melhores.size() - 1, j = 0; j < k + 1; j++, i--) {
		    resp += melhores.get(i);
		}
		System.out.println(resp);
	}
}