import java.util.Scanner;
public class mania {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int m = in.nextInt();
		int[][] g = new int[n][m];
		int primeiroPar = 0, primeiroImpar = 0;
		for(int i = 0; i < n; i++) {
		    for(int j = 0; j < m; j++) {
		        g[i][j] = in.nextInt();
		        if((i + j)%2 == 0) {
		            if(g[i][j] % 2 != 0) primeiroPar++;
		            if(g[i][j] % 2 != 1) primeiroImpar++;
		        } else {
		            if(g[i][j] % 2 != 1) primeiroPar++;
		            if(g[i][j] % 2 != 0) primeiroImpar++;
		        }
		    }
		}
		if(primeiroPar < primeiroImpar) {
		    System.out.println(primeiroPar);  
		    for(int i = 0; i < n; i++) {
		        for(int j = 0; j < m; j++) {
		            if(((i + j) % 2) != (g[i][j] % 2))
		                System.out.print((g[i][j] + 1) + " "); 
		            else 
		                System.out.print(g[i][j] + " ");
		        }
		        System.out.println(); 
		    }
		} else {
		    System.out.println(primeiroImpar);  
		    for(int i = 0; i < n; i++) {
		        for(int j = 0; j < m; j++) {
		            if(((i + j) % 2) != (g[i][j] % 2))
		                System.out.print(g[i][j] + " ");
		            else 
		                System.out.print((g[i][j] + 1) + " ");
		        }
		        System.out.println(); 
		    }
		}
	}
}
