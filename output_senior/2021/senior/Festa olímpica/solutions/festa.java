// OBI2021 - Fase 3
// Festa olímpica

import java.util.Scanner;

public class festa {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int maxn = 10100;
	
	int n = in.nextInt();
	int m = in.nextInt();

	int ans[] = new int[n];
	int v[] = new int[m];


	for (int i=0; i<Math.min(n,maxn); i++)
	    ans[i] = i;
	
	for (int i=0; i<m; i++)
	    v[i] = in.nextInt();
	
	 for(int i=m-1;i>=0;i--)
	     for(int j=0;j<Math.min(n,maxn) && ans[j] < n;j++)
	  	ans[j] += Math.floor(ans[j] / (v[i]-1));

	// imprime o resultado
	for (int i=0; i<Math.min(n,10000) && ans[i] < n;i++)
	    System.out.printf("%d\n",ans[i]+1);
	
    }
}
