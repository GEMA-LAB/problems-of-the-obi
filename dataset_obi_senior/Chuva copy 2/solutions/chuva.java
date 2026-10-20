// OBI2022
// Tarefa Chuva

import java.util.Scanner;

public class chuva {

    public static void main(String[] args) {
	final int MAX = 1000000;

	Scanner in = new Scanner(System.in);
	
	int n = in.nextInt();
	int s = in.nextInt();
	
	long resp = 0; 
	int[] somas = new int[MAX];
	int soma = 0;
	somas[0] = 1;
	
	for(int i = 0; i < n; i++) {
	    int v = in.nextInt();
	    soma += v;
	    if (soma - s >= 0)
		resp += somas[soma - s];
	    somas[soma]++;
	}
	System.out.println(resp);
	
    }
}
