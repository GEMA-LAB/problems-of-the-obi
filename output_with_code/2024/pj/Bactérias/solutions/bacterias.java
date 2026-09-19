import java.util.*;

public class bacterias
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), p = in.nextInt();
		int pot = 1;
		int resp = 0;
		while(pot * p <= n) {
		  pot *= p;
		  resp++;
		}
		System.out.println(resp);
	}
}
