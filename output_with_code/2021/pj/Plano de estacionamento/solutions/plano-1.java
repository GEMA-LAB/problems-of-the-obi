// OBI2021 - Fase 3
// Plano de ação

import java.util.Scanner;

public class plano {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	
	int n = in.nextInt();
	int m = in.nextInt();

	int vagas[] = new int[n+1];

	for (int i=0; i<=n; i++)
	    vagas[i] = 0;

	boolean ok = true;
	int total = 0;
	for (int i=0; i<m && ok; i++) {

	    int plano = in.nextInt();

	    while (plano > 0 && vagas[plano] > 0) {
		int t = vagas[plano];
		vagas[plano]++;
		plano -=  t;
	    }
	    if (plano <= 0)
		ok = false;
	    else {
		vagas[plano] = 1;
		total++;
	    }
	}
	
	System.out.printf("%d\n", total);
    }
}
