import java.util.*;

public class relogio
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int h = in.nextInt(), m = in.nextInt(), s = in.nextInt(), t = in.nextInt();
		s += t;
		
		m += s/60;
		s = s % 60;
		
		h += m/60;
		m = m % 60;
		
		h = h%24;
		
		System.out.println(h);
		System.out.println(m);
		System.out.println(s);
	}
}