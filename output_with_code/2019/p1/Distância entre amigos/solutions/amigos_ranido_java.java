// R. Anido
// Amigos - OBI2019
// (diametro de arvore)
import java.util.Scanner;

public class ranido_java {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int n = in.nextInt();
	int[] p = new int[n];
	
	for (int i=0; i<n; i++)
	    p[i] = in.nextInt();
	    
	// predio que tem o andar mais distante do ultimo andar do predio 0
	
	int dist0 = 0;
	int k = -1;
	for (int i = 1; i<n; i++) {
	    int d0i = p[0] + i + p[i];
	    if (d0i > dist0) {
		dist0 = d0i;
		k = i;
	    }
	}
	
	// amigo mais distante do ultimo andar do predio k
	
	int maxdist = 0;
	for (int i = 0; i<n; i++) 
	    if (i != k) 
		maxdist = Math.max(maxdist, p[k]+(Math.abs(k-i))+p[i]);
	
	System.out.println(maxdist);
    }
}
