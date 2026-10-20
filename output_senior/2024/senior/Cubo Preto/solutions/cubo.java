import java.util.*;

public class cubo
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int zero = (n - 2) * (n - 2) * (n - 2);
		int um = (n - 2) * (n - 2) * 6;
		int dois = ((n - 2) * 4 * 6) / 2;
		int tres = 8;
		System.out.println(zero);
		System.out.println(um);
		System.out.println(dois);
		System.out.println(tres);
	}
}
