import java.util.*;
public class cabo
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int[] v = new int[6];
		int s = 0;
		for(int i = 0; i < 6; i++) {
		  v[i] = in.nextInt();
		  s += v[i];
		}
		
		boolean impasse = false;
  
    for(int i = 0; i < 6; i++)
      for(int j = i + 1; j < 6; j++)
        for(int k = j + 1; k < 6; k++)
          if(v[i] + v[j] + v[k] == (s/2))
            impasse = true;
    if(s % 2 == 1) impasse = false;
    
    if(impasse) System.out.print("S");
    else System.out.print("N");
	}
}
