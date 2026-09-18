import java.util.*;

public class alfabeto
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), m = in.nextInt();
		String alfabeto = in.next(), palavra = in.next();
		boolean answer = true;
		for(int j = 0; j < m; j++) {
		  boolean found = false;
		  for(int i = 0; i < n; i++) {
		    if(alfabeto.substring(i, i + 1).equals(palavra.substring(j, j + 1)))
		      found = true;
		  }
		  if(!found) answer = false;
		}
		if(answer) System.out.println("S");
		else System.out.println("N");
	}
}
