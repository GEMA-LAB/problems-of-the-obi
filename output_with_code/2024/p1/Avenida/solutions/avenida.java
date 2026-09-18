import java.util.*;

public class avenida
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int d = in.nextInt();
		int resp = Math.min(d % 400, 400 - (d % 400));
		System.out.println(resp);
	}
}
