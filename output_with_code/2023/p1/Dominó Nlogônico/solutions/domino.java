import java.util.*;
public class domino
{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
    
		int n = in.nextInt();
		int[] x = new int[n];
		int[] h = new int[n];
		int[] resp = new int[n];
		int[] pilha = new int[n];
		
		for(int i = 0; i < n; i++)
		  x[i] = in.nextInt();
		for(int i = 0; i < n; i++)
		  h[i] = in.nextInt();
		
		resp[n - 1] = 1;
		int topo = 0;
    pilha[topo] = (n - 1);
    for(int i = n - 2; i >= 0; i--) {
      resp[i] = 1;
      int idTopo = topo;
      while((idTopo != -1) && ((x[i] + h[i]) >= x[pilha[idTopo]])) {
        resp[i] += resp[pilha[idTopo]];
        topo--;
        idTopo--;
      }
      topo++;
      pilha[topo] = i;
    }
    
    for(int i = 0; i < n; i++)
      if(i == (n - 1))
        System.out.println(resp[i]);
      else
        System.out.print(resp[i] + " ");
	}
}
