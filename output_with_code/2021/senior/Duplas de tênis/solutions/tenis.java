import java.util.Scanner;

/**
 * @author marcio oshiro
 */
public class tenis {
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int a = sc.nextInt();
		int b = sc.nextInt();
		int c = sc.nextInt();
		int d = sc.nextInt();
		
		int resp = Math.abs((a + b) - (c + d));
		resp = Math.min(resp, Math.abs((a + c) - (b + d)));
		resp = Math.min(resp, Math.abs((a + d) - (b + c)));
		
		System.out.println(resp);
	}
}
