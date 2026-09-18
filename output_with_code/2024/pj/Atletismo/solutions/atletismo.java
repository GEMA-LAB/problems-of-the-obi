import java.util.*;

public class atletismo
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] pos = new int[n + 1];
		for(int i = 1; i <= n; i++) {
		  int atleta = in.nextInt();
		  pos[atleta] = i;
		}
		for(int atleta = 1; atleta <= n; atleta++) {
		  System.out.println(pos[atleta]);
		}
	}
}