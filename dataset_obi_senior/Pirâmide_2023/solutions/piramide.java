import java.util.*;
public class piramide
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int[] p = new int[6];
		int s = 0;
		for(int i = 0; i < 6; i++) {
		  p[i] = in.nextInt();
		  s += p[i];
		}
		Arrays.sort(p);
		
		boolean cond0 = (s%3 == 0);
    boolean cond1 = (p[5] == (s/3));
    boolean cond2 = false;
    for(int i = 0; i < 5; i++)
      for(int j = i + 1; j < 5; j++)
        if(p[i] + p[j] == p[5])
          cond2 = true;
    
    if(cond0 && cond1 && cond2) System.out.print("S");
    else System.out.print("N");
	}
}
