// OBI2021
// Lista palíndroma

import java.util.Scanner;
import java.util.ArrayList;

public class lista {
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	int n = in.nextInt();
	int sol = 0, p_esq = 0, p_dir = n-1;
	int[] lista =new int[n];
	
	for (int i=0; i<n; i++){
	    lista[i] = in.nextInt();	    
	}

	while (p_esq < p_dir) {
	    if (lista[p_esq] == lista[p_dir]) {
		++p_esq; --p_dir;
		continue;
	    }
	    if (lista[p_esq] < lista[p_dir]) {
		lista[p_esq + 1] += lista[p_esq];
		++p_esq;
	    } else {
		lista[p_dir - 1] += lista[p_dir];
		--p_dir;
	    }
	    ++sol;
	}
	
	System.out.printf("%d\n", sol);
    }
}
