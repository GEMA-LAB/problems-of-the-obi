// OBI2020 - Fase 3
// celular

import java.util.Scanner;
import java.util.ArrayList;

public class solucao {
    public static final int MAX = 10010;
    public static int[] X;
    public static int[] Y;
    public static int[] distancia;
    public static boolean[] marcado;
    public static ArrayList<ArrayList<Integer>> adj;

    public static long quadrado(int x) {
	return x * x;
    }

    public static void dfs(int idx) {
	if (marcado[idx])
	    return;
	marcado[idx] = true;
	//System.out.printf("marcado idx=%d\n",idx);
	//for (int i=0; i<3; i++)
	//    System.out.println(marcado[i]);
	for (int i = 0; i < adj.get(idx).size(); i++)
	   dfs(adj.get(idx).get(i));
    }
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int N = in.nextInt();
	X = new int[N];
	Y = new int[N];
	distancia = new int[N];
	marcado = new boolean[N];
	// for (int i=0; i<N; i++)
	//     System.out.println(marcado[i]);

	for (int i=0; i<N; i++) {
	    X[i] = in.nextInt();
	    Y[i] = in.nextInt();
	}
	adj = new ArrayList<ArrayList<Integer>>();
	for (int i=0; i<N; i++) {
	    ArrayList<Integer> tmp = new ArrayList<Integer>();
	    adj.add(tmp);
	}

	int D = in.nextInt();
	D *= D;
	for (int i = 0; i < N; i++) {
	    for (int j = i+1; j < N; j++) {
		if (quadrado(X[i]-X[j])+quadrado(Y[i]-Y[j]) <= D) {
		    // System.out.printf("before add %d to %d, ",j,i, adj.get(i).size());
		    adj.get(i).add(j);
		    // System.out.printf("after %d\n",adj.get(i).size());
		    // System.out.printf("before add %d to %d, ",i,j, adj.get(j).size());
		    adj.get(j).add(i);
		    // System.out.printf("after %d\n",adj.get(j).size());
		    // System.out.println();
		}
	    }
	}
	// System.out.println(adj.size());
	// for (int i = 0; i < N; i++) {
	//     System.out.printf("adj %d\n  size = %d", i, adj.get(i).size());
	//     for (int j = 0; j < adj.get(i).size(); j++) {
	//  	System.out.println("  " + adj.get(i).get(j));
	//     }
	// }

	    
	dfs(0);
	boolean ok = true;
	for (int i = 0; i < N && ok; i++)
	    ok &= marcado[i];
	if (ok)
	    System.out.println("S");
	else
	    System.out.println("N");
    }
}
